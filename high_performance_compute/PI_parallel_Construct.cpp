#include "omp.h"
#include <stdio.h>
static long num_steps =100000; 
double step;
#define NUM_THREADS 2 
int main(){
    int i, id;
    double x, pi, sum;
    step = 1.0/(double)num_steps; 
    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel private(x, i, id) reduction(+: sum)
    {
        id = omp_get_thread_num ();
        for (i=id+1; i<=num_steps; i=i+NUM_THREADS){
            x = (i - 0.5)*step ;
            sum = sum + 4.0/(1.0+ x * x);
        }
    }
    pi = sum * step;
    printf("pi = %f\n", pi);
}
