#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char**argv) {
    if(argc < 3)
        return -1;
    mkfifo(argv[1], 0666);
    mkfifo(argv[2], 0666);

    while(1) {
        int fd_in = open(argv[1], O_RDONLY | O_NONBLOCK);
        if(fd_in<0) {
            perror("Cannot open in.fifo");
            return -1;
        }
        int fd_out = open(argv[2], O_WRONLY );
        if(fd_out<0) {
            perror("Cannot open out.fifo");
            return -1;
        }

        char buf[1024];
        ssize_t nread;
        while( (nread = read(fd_in, buf, 1024)) >= 0 ) {
            write(fd_out, buf, nread);
        }
    }

    return 0;
}
