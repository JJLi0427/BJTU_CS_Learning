#include <stdio.h> 
#include <omp.h>
int main() { 
#pragma omp parallel sections
{ 
    #pragma omp section
	for (int i = 0; i < 3; ++i) { 
	    printf("section i : iteration %d by thread no. %d\n", i, omp_get_thread_num());
	} 
    #pragma omp section
	for (int j = 0; j < 5; ++j) { 
	    printf("section j : iteration %d by thread no. %d\n", j, omp_get_thread_num()); 
	} 
} 
return 0; 
} 
