
#include<iostream>
#include<omp.h>
double total_time_serial,total_time_parallel;
using namespace std;
int main()  
{
    int n = 100000000;
    int * arr = new int[n];
    int max_serial,max_parallel;
    double start, end;
    int num_thread;

    
        for(int i=0;i<n;i++)
        {
            arr[i] = rand();
        }
        
    start = omp_get_wtime(); 

    max_serial = arr[0];
    for(int i=0;i<n;i++)
    {
        if(max_serial<arr[i])
        {
            max_serial = arr[i];
        }
    }

     end = omp_get_wtime();

     total_time_serial = end-start;

    cout<<"total_time_serial- "<<total_time_serial<<endl;

    for(int k=1;k<=4;k++)
    {
            omp_set_num_threads(k);

            max_parallel= -99999999;

            start = omp_get_wtime();
            #pragma omp parallel 
            {
                #pragma omp single
                {
                    num_thread = omp_get_num_threads();
                }
                
                int private_max = -99999999;
                #pragma omp for
                for(int i=0;i<n;i++)
                {
                    if(private_max<arr[i])
                    {
                        private_max = arr[i];
                    }
                }

                if(private_max > max_parallel)
                {
                    #pragma omp critical
                    {
                        max_parallel = private_max;
                    }
                }

            }

            end = omp_get_wtime();
            total_time_parallel = end-start;
            cout<<"Serial max- "<<max_serial<<" Parallel max- "<<max_parallel<<endl;
            cout<<"total_time_parallel with threads("<<num_thread<<")- "<<total_time_parallel<<endl;
     }


     return 0;

}