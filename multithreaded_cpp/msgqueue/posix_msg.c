#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <mqueue.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    mqd_t mq = mq_open("/test.mq", O_CREAT | O_RDONLY);
    
    if(mq == -1) {
        perror("Cannot open mq");
        exit(-1);
    }

    void *buffer;
    struct mq_attr attr;
    ssize_t msgLen;
    unsigned int prio;

    if(mq_getattr(mq, &attr) == -1) {
        perror("cannot get attr");
        exit(-1);
    }

    buffer = malloc(attr.mq_msgsize);
    
    msgLen = mq_receive(mq, buffer, attr.mq_msgsize, &prio);
    
    int fd = creat("/home/box/message.txt", O_WRONLY);
    write(fd, buffer, msgLen);
    close(fd);

    mq_close(mq);
}
