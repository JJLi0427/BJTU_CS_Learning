#include <omp.h>
#include <stdio.h>
main(int argc, char **argv){
    int x;
    x = 0;
    omp_set_num_threads(4);
    #pragma omp parallel shared(x)
    {
        #pragma omp atomic
        x = x + 1;
    }
    printf("x = %d\n", x);
}