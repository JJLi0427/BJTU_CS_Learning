#include <stdio.h>
#include "omp.h"

int main()
{
    int id, numb;
    omp_set_num_threads(3);
    #pragma omp parallel private(id, numb) 
    {
        id = omp_get_thread_num();
        numb = omp_get_num_threads();
        printf("I am thread %d out of %d \n", id, numb);
    }
}