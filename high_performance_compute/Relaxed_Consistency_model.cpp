#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
	int x=0;
	#pragma omp parallel shared(x)
	{	
		for(int i=0;i<2;i++) 
			printf("i=%d MyID is %d \n",i,omp_get_thread_num());
		#pragma omp critical
		{
			x=x+1;
			printf("x=%d by threadID%d\n",x,omp_get_thread_num());
			printf("x=%d by threadID%d\n",x,omp_get_thread_num());
		}
		for(int j=0;j<2;j++) 
			printf("j=%d MyID is %d\n",j,omp_get_thread_num());
		printf("\n");
	}
	printf("x=%d\n",x);
	return 0;
}
