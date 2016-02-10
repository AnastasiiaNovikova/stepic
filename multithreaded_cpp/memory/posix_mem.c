#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/mman.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MEM_SIZE 1*1024*1024

int main() {
    char *pathname = "/test.shm";

    int fd = shm_open(pathname, O_CREAT | O_RDWR, 0777);
    if(fd == -1) {
        perror("shm_open");
        return -1;
    }

    if(ftruncate(fd, MEM_SIZE) == -1) {
        perror("ftruncate");
        return -1;
    }
    
    void *addr = mmap(NULL, MEM_SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
    if(addr == MAP_FAILED) {
        perror("mmap");
        return -1;
    }
    memset(addr,13,MEM_SIZE);

    pause();

    return 0;
}
