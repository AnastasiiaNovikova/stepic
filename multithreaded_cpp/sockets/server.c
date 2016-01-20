#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

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

    if(bind(sock,(struct sockaddr*)&sa,sizeof(sa)) < 0) {
        perror("Error binding socket\n");
        exit(1);
    }

    listen(sock, SOMAXCONN);

    int s1;
    while(s1 = accept(sock,0,0)) {
        printf("Connected!\n");
    }

}
