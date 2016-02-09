#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>

#define SEM_COUNT 16

union semun {
    int val;
    struct semi_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

int main()
{
    union semun arg;
    int semid;

    key_t key = ftok("/tmp/sem.temp", 1);

    semid = semget(key, SEM_COUNT, IPC_CREAT | 0777 );

    if(semid == -1) {
        perror("Error creating semaphore");
        exit(-1);
    }

    for(int i=0; i<SEM_COUNT;++i) {
        arg.val = i;
        semctl(semid, i, SETVAL, arg);
    }

    pause();
}
