#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int argc, char** argv) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Error opeming socket\n");
        exit(1);
    }

    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = INADDR_ANY;
    sa.sin_port = htons(6666);

    if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,&(int){1}, sizeof(int)) < 0) {
        perror("Error setting SO_REUSEADDR\n");
        exit(1);
    }

    if(bind(sock,(struct sockaddr*)&sa,sizeof(sa)) < 0) {
        perror("Error binding socket\n");
        exit(1);
    }

    listen(sock, SOMAXCONN);

    int clientsock;
    while(clientsock = accept(sock,0,0)) {
        if (clientsock < 0) {
            printf("Error on accept");
            exit(0);
        }
        pid_t pid = fork();
        if(pid < 0) {
            printf("Error on fork");
            exit(0);
        }
        if(pid == 0) {
            close(sock);
            
            char buffer[1024];
            ssize_t count = recv(clientsock, buffer, 1023, MSG_NOSIGNAL);
            buffer[count] = '\0';
            printf("%s\n", buffer);
            send(clientsock,buffer,count,MSG_NOSIGNAL);

            shutdown(clientsock, SHUT_RDWR);
            close(clientsock);
            exit(0);
        } else {
            close(clientsock);
        }
    }

}
