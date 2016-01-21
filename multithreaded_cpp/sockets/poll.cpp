#include <iostream>
#include <algorithm>
#include <set>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>

#define POLL_SIZE 2048

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

    struct pollfd Set[POLL_SIZE];
    Set[0].fd = msock;
    Set[0].events = POLLIN;

    while(true) {
        unsigned int Index = 1;
        for(auto it = sockets.begin();
                it != sockets.end();
                ++it) {
            Set[Index].fd = *it;
            Set[Index].events = POLLIN;
            Index++;
        }

        unsigned int SetSize = 1 + sockets.size();

        poll(Set,SetSize,-1);

        for(unsigned int i = 0; i< SetSize; i++) {
            if(Set[i].revents & POLLIN) {
                if(i) {
                    static char buffer[1024];
                    int recvSize = recv(Set[i].fd,
                        buffer,
                        1024,
                        MSG_NOSIGNAL);
                    if((recvSize == 0) &&
                            (errno != EAGAIN)) {
                        shutdown(Set[i].fd, SHUT_RDWR);
                        close(Set[i].fd);
                        sockets.erase(Set[i].fd);
                    } else if (recvSize > 0) {
                        send(Set[i].fd, buffer, recvSize, MSG_NOSIGNAL);
                    }
                } else {
                    int sock = accept(msock, 0, 0);
                    set_nonblock(sock);
                    sockets.insert(sock);
                }
            }
        }
    }


    return 0;
}
