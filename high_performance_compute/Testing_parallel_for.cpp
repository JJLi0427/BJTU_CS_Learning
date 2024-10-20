#include <stdio.h> 
#include <omp.h>
int main() { 
	#pragma omp parallel for 
	for(int i = 0; i < 10; ++i) { 
	    printf(" No. %d iteration by thread %d\n",i,omp_get_thread_num() );
	} 
	return 0; 
}
