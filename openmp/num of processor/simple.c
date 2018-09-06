#include "omp.h"
#include<stdio.h>

int main()
{
	int tid;
	#pragma omp parallel
	{
	tid = omp_get_num_threads();
	}
	
	printf("\nTotal number of cores-%d\n",tid);

	#pragma omp parallel
	{
	
	int id=omp_get_thread_num();
	printf("%d\n",id);
	}

	
return 0;
}
