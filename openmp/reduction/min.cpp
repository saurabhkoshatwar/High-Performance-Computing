
#include<iostream>
#include<omp.h>
double total_time_serial,total_time_parallel;
using namespace std;
int main()  
{
    int n = 100000000;
    int * arr = new int[n];
    int min_serial,min_parallel;
    double start, end;
    int num_thread;

    
        for(int i=0;i<n;i++)
        {
            arr[i] = rand();
        }
        
    start = omp_get_wtime(); 

    min_serial = arr[0];
    for(int i=0;i<n;i++)
    {
        if(min_serial>arr[i])
        {
            min_serial = arr[i];
        }
    }

     end = omp_get_wtime();

     total_time_serial = end-start;

    cout<<"total_time_serial- "<<total_time_serial<<endl;

    for(int k=1;k<=4;k++)
    {
            omp_set_num_threads(k);

            min_parallel= 99999999;

            start = omp_get_wtime();
            #pragma omp parallel 
            {
                #pragma omp single
                {
                    num_thread = omp_get_num_threads();
                }
                
                int private_min = 99999999;
                #pragma omp for
                for(int i=0;i<n;i++)
                {
                    if(private_min>arr[i])
                    {
                        private_min = arr[i];
                    }
                }

                if(private_min<min_parallel)
                {
                    #pragma omp critical
                    {
                        min_parallel = private_min;
                    }
                }

            }

            end = omp_get_wtime();
            total_time_parallel = end-start;
            cout<<"Serial Min- "<<min_serial<<" Parallel Min- "<<min_parallel<<endl;
            cout<<"total_time_parallel with threads("<<num_thread<<")- "<<total_time_parallel<<endl;
     }


     return 0;

}