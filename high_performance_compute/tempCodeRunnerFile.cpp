#include <stdio.h>
#include <mpi.h>
int main(){
    int size,rank,namelength;
    char name[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Get_processor_name(name, &namelength);
    printf("size=%d rank=%d name=%s len=%d\n",size,rank,name,namelength);
    fflush(stdout);
    MPI_Finalize();
    return 0;
}