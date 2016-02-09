#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_MSG 80

struct message {
    long mtype;
    char mtext[MAX_MSG];
};

int main() {
    char *pathname = "/tmp/msg.temp";

    key_t id = ftok(pathname, 1);
    if(id == -1) {
        perror("Error calling ftok");
        exit(-1);
    }

    int msgid = msgget(id, IPC_CREAT | S_IRUSR | S_IWUSR | S_IRGRP |
            S_IWGRP | S_IROTH | S_IWOTH);
    if(msgid == -1) {
        perror("Error creating message queue.");
        exit(-1);
    }

    struct message msg;
    int msgLen = msgrcv(msgid, &msg, MAX_MSG, 0, 0);

    int fd = creat("/home/box/message.txt", O_WRONLY);
    write(fd, msg.mtext, msgLen);
    close(fd);
}
