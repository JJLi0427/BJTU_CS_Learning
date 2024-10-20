#include <stdio.h>
#include <mpi.h>
int main(){
    MPI_Status status;
    char string[]="xxxxx";
    int myid;
    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    if(myid==2)
        MPI_Send("HELLO",5,MPI_CHAR,7,1234,MPI_COMM_WORLD);
    if(myid==7){
        MPI_Recv(string,5,MPI_CHAR,2,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
        printf("Got %s from P%d, tag %d\n",string,status.MPI_SOURCE,status.MPI_TAG);
        fflush(stdout);
    }
    MPI_Finalize();
}