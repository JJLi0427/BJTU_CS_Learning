#include "mpi.h"
#include <stdio.h>
int main(int argc, char **argv){
    int numtasks, rank, dest, source, tag=1234;
    char inmsg[]="xxxxx", outmsg[]="HELLO";
    MPI_Status stats[2];
    MPI_Request reqs[2];
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if(rank == 0){
        dest = 1;
        MPI_Isend(&outmsg, 5, MPI_CHAR, dest, tag, MPI_COMM_WORLD, &reqs[0]);
        printf("Task %d: Send %s while inmsg=%s\n", rank, outmsg, inmsg);
        fflush(stdout);
        MPI_Wait(&reqs[0],&stats[0]);
        printf("Task %d: Send %s while inmsg=%s reqs[0]= %d\n", rank, outmsg, inmsg, reqs[0]);
        fflush(stdout);
    }
    else if(rank == 1){
        source = 0;
        MPI_Irecv(&inmsg, 5,MPI_CHAR, source, tag, MPI_COMM_WORLD, &reqs[1]);
        printf("Task %d: Receive %s\n", rank, inmsg);
        fflush(stdout);
        MPI_Wait(&reqs[1], &stats[1]);
        printf("Task %d: Received %s reqs[1]=%d\n", rank, inmsg, reqs[1]);
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;
}