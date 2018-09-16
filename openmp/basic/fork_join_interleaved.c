//concepts
// 1)opmp parallel directive----- at start---- fork ---- get number of threads(set by omp_set_num_threads/default number)
// at last of omp parallel --- join
// 2)interleaved stmt 1 2 3
#include<stdio.h>
#include<omp.h>

void main()
{
    omp_set_num_threads(4);
    #pragma omp parallel
    {
    int id =omp_get_thread_num();
    printf("statement1 by thread (%d)\n",id);
    printf("statement2 by thread (%d)\n",id);
    printf("statement3 by thread (%d)\n",id);
    }
}