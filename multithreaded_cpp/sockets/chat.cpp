#include <iostream>
#include <algorithm>
#include <set>
#include <cstring>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <netdb.h>

#define MAX_EVENTS 32

int set_nonblock(int fd) {
    int flags;
#if defined(O_NONBLOCK)
    if(-1 == (flags = fcntl(fd, F_GETFL, 0)))
        flags = 0;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#else
    flags = 1;
    return ioctl(fd, FIOBIO, &flags);
#endif
}

void print_usage() {
    std::cout << "Usage: chat [--server] [-a address] [-p port] nickname" << std::endl;
    exit(0);
}

void print_error(std::string str) {
    perror(str.c_str());
    exit(1);
}

void server(const std::string& address, const uint16_t port, const std::string& nickname) {
    int msock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(msock < 0)
        print_error("Error opening socket\n");
        
    std::set<int> sockets;
    struct hostent *host = gethostbyname(address.c_str());
    if (host == NULL)
        print_error("Cannot find host\n");
    
    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    memcpy((char*)&sa.sin_addr.s_addr, (char*)host->h_addr, host->h_length);
    
    int param = 1;
    if(setsockopt(msock, SOL_SOCKET, SO_REUSEADDR, &param, sizeof(int)) < 0)
        print_error("Error setting SO_REUSEADDR\n");
        
    if(bind(msock, (struct sockaddr*)&sa, sizeof(sa)) < 0)
        print_error("Error binding socket\n");
    
    set_nonblock(msock);
    listen(msock, SOMAXCONN);
    
    int epoll = epoll_create1(0);
    struct epoll_event event;
    
    event.data.fd = msock;
    event.events = EPOLLIN;
    epoll_ctl(epoll, EPOLL_CTL_ADD, msock, &event);
    
    event.data.fd = STDIN_FILENO;
    event.events = EPOLLIN;
    epoll_ctl(epoll, EPOLL_CTL_ADD, STDIN_FILENO, &event);
    
    while(true) {
        struct epoll_event events[MAX_EVENTS];
        int N = epoll_wait(epoll, events, MAX_EVENTS, -1);
        
        for(unsigned int i = 0; i<N; ++i) {
            if(events[i].data.fd == msock) {
                int sock = accept(msock, 0, 0);
                set_nonblock(sock);
                struct epoll_event event;
                event.data.fd = sock;
                event.events = EPOLLIN;
                epoll_ctl(epoll, EPOLL_CTL_ADD, sock, &event);
            } else if(events[i].data.fd == STDIN_FILENO) {
                std::string message;
                std::getline(std::cin, message);
                if (message.size() > 0) {
                    message = nickname + ": " + message;
                    for(auto it = sockets.begin(); it != sockets.end(); ++it) {
                        send(*it, message.c_str(), message.size(), MSG_NOSIGNAL);
                    }
                }
            } else {
                static char buffer[1024];
                int recvSize = recv(events[i].data.fd,
                                    buffer, 1023, MSG_NOSIGNAL);
                if((recvSize == 0) && (errno != EAGAIN)) {
                    shutdown(events[i].data.fd, SHUT_RDWR);
                    close(events[i].data.fd);
                    //epoll_ctl(epoll, EPOLL_CTL_DEL, events[i].data.fd, NULL);
                } else if(recvSize > 0) {
                    buffer[recvSize] = '\0';
                    std::cout << buffer << std::endl;
                    for(auto it = sockets.begin(); it != sockets.end(); ++it) {
                        if(*it != events[i].data.fd)
                            send(*it, buffer, recvSize, MSG_NOSIGNAL);
                    }
                }
            }
        }
    }
}


void client(const std::string& address, const uint16_t port, const std::string& nickname) {
    int msock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(msock < 0)
        print_error("Error opening socket\n");
        
    struct hostent *host = gethostbyname(address.c_str());
    if (host == NULL)
        print_error("Cannot find host\n");
    
    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    memcpy((char*)&sa.sin_addr.s_addr, (char*)host->h_addr, host->h_length);
        
    if(connect(msock, (struct sockaddr*)&sa, sizeof(sa)) < 0)
        print_error("Error connecting to host\n");
    
    set_nonblock(msock);
    
    int epoll = epoll_create1(0);
    struct epoll_event event;
    
    event.data.fd = msock;
    event.events = EPOLLIN;
    epoll_ctl(epoll, EPOLL_CTL_ADD, msock, &event);
    
    event.data.fd = STDIN_FILENO;
    event.events = EPOLLIN;
    epoll_ctl(epoll, EPOLL_CTL_ADD, STDIN_FILENO, &event);
    
    while(true) {
        struct epoll_event events[MAX_EVENTS];
        int N = epoll_wait(epoll, events, MAX_EVENTS, -1);
        
        for(unsigned int i = 0; i<N; ++i) {
            if(events[i].data.fd == msock) {
                static char buffer[1024];
                int recvSize = recv(msock,
                                    buffer, 1023, MSG_NOSIGNAL);
                if((recvSize == 0) && (errno != EAGAIN)) {
                    shutdown(events[i].data.fd, SHUT_RDWR);
                    close(events[i].data.fd);
                    return;
                } else if(recvSize > 0) {
                    buffer[recvSize] = '\0';
                    std::cout << buffer << std::endl;
                }
            } else if(events[i].data.fd == STDIN_FILENO) {
                std::string message;
                std::getline(std::cin, message);
                if (message.size() > 0) {
                    message = nickname + ": " + message;
                    send(msock, message.c_str(), message.size(), MSG_NOSIGNAL);
                }
            } else {
                print_error("Unknown error!\n");
            }
        }
    }
}

int main(int argc, char**argv) {
    if(argc<2)
        print_usage();
    
    bool is_server = false;
    std::string address = "127.0.0.1";
    uint16_t port = 6666;
    std::string nickname = argv[argc-1];
    
    for(int i=1; i<argc-1;++i) {
        if(strncmp(argv[i],"--server",9) == 0) {
            is_server = true;
        } else if(strncmp(argv[i],"-a",3) == 0) {
            if(i+2<argc)
                address = std::string(argv[i++]);
            else
                print_usage();
        } else if(strncmp(argv[i],"-p",3) == 0) {
            if(i+2<argc)
                port = atoi(argv[i++]);
            else
                print_usage();
        } else {
            print_usage();
        }
    }
    
    if(is_server)
        server(address, port, nickname);
    else
        client(address, port, nickname);
}