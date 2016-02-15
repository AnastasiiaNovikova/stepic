#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

pthread_mutex_t m1;
pthread_cond_t cond;
pthread_barrier_t barrier;

void *func1(void *) {
    pthread_cond_wait(&cond, &m1);
    std::cout << "Hello from func1" << std::endl;
    pthread_barrier_wait(&barrier);
    return NULL;
}

void *func2(void *) {
    pthread_barrier_wait(&barrier);
    std::cout << "Hello from func2" << std::endl;
    return NULL;
}

int main(int argc, char** argv) {
    pthread_t thread[4];
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

    pthread_mutex_init(&m1,NULL);
    pthread_cond_init(&cond, NULL);
    pthread_barrier_init(&barrier, NULL, 2);

    if( pthread_create(&thread[0], NULL, func1, NULL) != 0) {
        std::cerr << "Error creating thread\n";
    }
    if( pthread_create(&thread[1], NULL, func2, NULL) != 0) {
        std::cerr << "Error creating thread\n";
    }
    
    int x;
    std::cin >> x;

    pthread_cond_signal(&cond);

    if( pthread_join(thread[0], &res) != 0 ) {
        std::cerr << "Error joining thread\n";
    }
    if( pthread_join(thread[1], &res) != 0 ) {
        std::cerr << "Error joining thread\n";
    }

    pthread_mutex_destroy(&m1);
    pthread_cond_destroy(&cond);
    pthread_barrier_destroy(&barrier);

    std::cout << "End" << std::endl;

    return 0;
}
