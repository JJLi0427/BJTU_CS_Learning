#include <omp.h>
#include <stdio.h>
main(int argc, char *argv[]){
    int x;
    x = 0;
    #pragma omp parallel shared(x)
    {
        #pragma omp critical
        x++;
    }
    printf("x = %d\n", x);
}