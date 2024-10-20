#include <stdio.h>
#include <mpi.h>
#define N 100000
int main(){
    int myid, numprocs, i, n;
    double mypi, pi, h, sum, x;
    n = N;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    h = 1.0/N;
    sum = 0.0;
    for(i = myid+1; i<=N; i += numprocs){
        x = h*((double)i-0.5);
        sum += (4.0/(1.0+x*x));
    }
    mypi = h*sum;
    MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if(myid == 0){
        printf("pi is approximately %.16f\n", pi);
        fflush(stdout);
    }
    MPI_Finalize();
}