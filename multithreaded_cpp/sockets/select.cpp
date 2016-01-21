#include <iostream>
#include <algorithm>
#include <set>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

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

    while(true) {
        fd_set Set;
        FD_ZERO(&Set);
        FD_SET(msock, &Set);
        for(auto it = sockets.begin();
                it != sockets.end();
                ++it) {
            FD_SET(*it, &Set);
        }

        int Max = std::max(msock, *std::max_element(sockets.begin(),sockets.end()));

        select(Max+1, &Set, NULL, NULL, NULL);

        for(auto it = sockets.begin();
                it != sockets.end();
                ++it) {
            if(FD_ISSET(*it, &Set)) {
                static char buffer[1024];
                int recvSize = recv(*it, buffer, 1024, MSG_NOSIGNAL);
                if ((recvSize == 0) && (errno != EAGAIN)) {
                    shutdown(*it,SHUT_RDWR);
                    close(*it);
                    sockets.erase(it);
                } else if (recvSize != 0) {
                    send(*it, buffer, recvSize, MSG_NOSIGNAL);
                }
            }
        }

        if(FD_ISSET(msock, &Set)) {
            int sock = accept(msock, 0, 0);
            set_nonblock(sock);
            sockets.insert(sock);
        }
    }


    return 0;
}
