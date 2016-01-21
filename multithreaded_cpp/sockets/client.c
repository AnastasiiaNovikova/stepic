#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc < 4) {
        printf("Usage: client hostname port message\n");
        exit(0);
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Error opeming socket\n");
        exit(1);
    }

    struct hostent *host = gethostbyname(argv[1]);
    if(host == NULL) {
        printf("Cannot find host %s", argv[1]);
        exit(0);
    }
    int port = atoi(argv[2]);

    struct sockaddr_in sa;
    sa.sin_family = AF_INET;

    memcpy((char*)&sa.sin_addr.s_addr,(char*)host->h_addr,host->h_length);

    sa.sin_port = htons(port);

    if(connect(sock,(struct sockaddr *)&sa,sizeof(sa)) < 0) {
        perror("Error connecting to host.");
        exit(1);
    }

    char buffer[1024];
    send(sock, argv[3], strlen(argv[3]), MSG_NOSIGNAL);
    ssize_t count = recv(sock, buffer, sizeof(buffer), MSG_NOSIGNAL);

    buffer[count] = '\0';
    printf("%s\n", buffer);

    shutdown(sock, SHUT_RDWR);

    return 0;
}
