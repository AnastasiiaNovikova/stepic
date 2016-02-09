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

#define MAX_MTEXT 1024

struct mbuf {
    long mtype;
    char mtext[MAX_MTEXT];
};

int main() {
    char * pathname = "/tmp/somepath.txt";
    int fd = creat(pathname, O_CREAT);
    close(fd);

    key_t id = ftok(pathname, 1);
    if(id == -1) {
        perror("Error calling ftok");
        exit(-1);
    }

    int msgid = msgget(id, IPC_CREAT | S_IRUSR | S_IWUSR);
    
    if(msgid == -1) {
        perror("Error creating message queue.");
        exit(-1);
    }

    if(!fork()) {
        struct mbuf msg;
        msg.mtype = 1;
        char* message = "SOME_TEXT";
        int msgLen = strlen(message)+1;
        memcpy(msg.mtext, message, msgLen);

        if(msgsnd(msgid, &msg, msgLen, 0 ) == -1)
        {
            perror("msgsnd");
        }
    } else {
        struct mbuf msg;
        int msgLen = msgrcv(msgid, &msg, MAX_MTEXT, 0, 0);
        
        if(msgLen > 0) {
            msg.mtext[msgLen] = '\0';
            printf("Recieved: %s\n", msg.mtext);
        }

        if(msgctl(msgid, IPC_RMID, NULL) != 0) {
            perror("Error closing message queue.");
        }
        unlink(pathname);
    }
}
