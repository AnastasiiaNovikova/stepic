#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char**argv)
{
    char message[80];
    int i, rank, size, type = 99;
    struct MPI_Status status;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank == 0) {
        strcpy(message,"Hello, world!");
        for(i=1;i<size;++i) {
            MPI_Send(message, 14, MPI_CHAR, i, type, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(message,80,MPI_CHAR,0,type,MPI_COMM_WORLD,&status);
        printf("%s\n",message);
    }

    MPI_Finalize();

    return 0;
}
