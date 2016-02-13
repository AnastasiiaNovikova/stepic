#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void *func(void *) {
    std::cout << "Hello from thread" << std::endl;

    while(1);

    return NULL;
}

int main(int argc, char** argv) {
    pthread_t thread;
    void * res;
    int s;

    pid_t pid = getpid();

    if(argc < 2)
        return -1;

    int fd = creat(argv[1],0666);
    char buf[50];
    sprintf(buf, "%d", pid);
    write(fd,buf,strlen(buf)+1);
    close(fd);

    if( pthread_create(&thread, NULL, func, NULL) != 0) {
        std::cerr << "Error creating thread\n";
    }
    if( pthread_join(thread, &res) != 0 ) {
        std::cerr << "Error joining thread\n";
    }

    return 0;
}
