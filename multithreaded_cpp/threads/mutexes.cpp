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
pthread_spinlock_t spinlock;
pthread_rwlock_t rwlock;

void *func1(void *) {
    pthread_mutex_lock(&m1);
    std::cout << "Hello from func1" << std::endl;
    pthread_mutex_unlock(&m1);
    return NULL;
}

void *func2(void *) {
    pthread_spin_lock(&spinlock);
    std::cout << "Hello from func2" << std::endl;
    pthread_spin_unlock(&spinlock);
    return NULL;
}

void *func3(void *) {
    pthread_rwlock_rdlock(&rwlock);
    std::cout << "Hello from func3" << std::endl;
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

void *func4(void *) {
    pthread_rwlock_wrlock(&rwlock);
    std::cout << "Hello from func4" << std::endl;
    pthread_rwlock_unlock(&rwlock);
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
    pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);
    pthread_rwlock_init(&rwlock,NULL);

    pthread_mutex_lock(&m1);
    pthread_spin_lock(&spinlock);
    pthread_rwlock_wrlock(&rwlock);

    if( pthread_create(&thread[0], NULL, func1, NULL) != 0) {
        std::cerr << "Error creating thread\n";
    }
    if( pthread_create(&thread[1], NULL, func2, NULL) != 0) {
        std::cerr << "Error creating thread\n";
    }
    if( pthread_create(&thread[2], NULL, func3, NULL) != 0) {
        std::cerr << "Error creating thread\n";
    }
    if( pthread_create(&thread[3], NULL, func4, NULL) != 0) {
        std::cerr << "Error creating thread\n";
    }
    
    int x;
    std::cin >> x;

    pthread_mutex_unlock(&m1);
    pthread_spin_unlock(&spinlock);
    pthread_rwlock_unlock(&rwlock);

    if( pthread_join(thread[0], &res) != 0 ) {
        std::cerr << "Error joining thread\n";
    }
    if( pthread_join(thread[1], &res) != 0 ) {
        std::cerr << "Error joining thread\n";
    }
    if( pthread_join(thread[2], &res) != 0 ) {
        std::cerr << "Error joining thread\n";
    }
    if( pthread_join(thread[3], &res) != 0 ) {
        std::cerr << "Error joining thread\n";
    }

    pthread_mutex_destroy(&m1);
    pthread_spin_destroy(&spinlock);
    pthread_rwlock_destroy(&rwlock);

    std::cout << "End" << std::endl;

    return 0;
}
