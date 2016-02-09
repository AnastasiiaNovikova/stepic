#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/shm.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MEM_SIZE 1*1024*1024

int main() {
    char *pathname = "/tmp/mem.temp";

    key_t id = ftok(pathname, 1);
    if(id == -1) {
        perror("Error calling ftok");
        exit(-1);
    }
    int shmid = shmget(id, MEM_SIZE, IPC_CREAT | 0777);
    if(shmid == -1) {
        perror("shmget");
        exit(-1);
    }

    void *addr = shmat(shmid, NULL, 0);
    memset(addr,42,MEM_SIZE);

    pause();

    return 0;
}
