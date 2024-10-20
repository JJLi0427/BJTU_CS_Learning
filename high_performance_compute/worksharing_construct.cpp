#include "omp.h"
#include <stdio.h>
int main(){
    omp_set_num_threads(3);
    #pragma omp parallel
    {  
        printf( " The number of threads: %d seen by thread %d\n",   omp_get_thread_num() , omp_get_num_threads());
        #pragma omp for
        for( int i = 1; i <= 5; ++i ){
            printf( " No. %d iteration by thread %d\n",i,omp_get_thread_num() );
        }
    }
}

