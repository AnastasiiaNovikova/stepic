#include <iostream>
#include <algorithm>
#include <set>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>

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

int main(int argc, char **argv) {
    int msock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    std::set<int> sockets;
    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(6666);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(msock,(struct sockaddr *)(&sa), sizeof(sa));
    set_nonblock(msock);
    listen(msock, SOMAXCONN);

    int epoll = epoll_create1(0);

    struct epoll_event event;
    event.data.fd = msock;
    event.events = EPOLLIN;
    epoll_ctl(epoll, EPOLL_CTL_ADD, msock, &event);

    while(true) {
        struct epoll_event events[MAX_EVENTS];
        int N = epoll_wait(epoll, events, MAX_EVENTS,-1);

        for(unsigned int i = 0; i<N; i++) {
            if(events[i].data.fd == msock) {
                int sock = accept(msock, 0, 0);
                set_nonblock(sock);
                struct epoll_event event;
                event.data.fd = sock;
                event.events = EPOLLIN;
                epoll_ctl(epoll, EPOLL_CTL_ADD, sock, &event);
            } else {
                static char buffer[1024];
                int recvSize = recv(events[i].data.fd,
                        buffer, 1024, MSG_NOSIGNAL);
                if ((recvSize == 0) && (errno != EAGAIN)) {
                    shutdown(events[i].data.fd, SHUT_RDWR);
                    close(events[i].data.fd);
                    epoll_ctl(epoll, EPOLL_CTL_DEL, events[i].data.fd, NULL);
                } else if (recvSize > 0) {
                    send(events[i].data.fd,
                            buffer,
                            recvSize,
                            MSG_NOSIGNAL);
                }
            }

        }
    }

    return 0;
}
