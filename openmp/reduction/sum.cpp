
#include<iostream>
#include<omp.h>
double total_time_serial,total_time_parallel;
using namespace std;
int main()  
{
    int n = 1000000000;
    int * arr = new int[n];
    int sum_serial=0,sum_parallel;
    double start, end;
    int num_thread;

    
        for(int i=0;i<n;i++)
        {
            arr[i] = rand();
        }
        
        start = omp_get_wtime(); 

    
        for(int i=0;i<n;i++)
        {
            sum_serial += arr[i];   
        }

        end = omp_get_wtime();

        total_time_serial = end-start;

        cout<<"total_time_serial- "<<total_time_serial<<endl;

    for(int k=1;k<=4;k++)
    {
            sum_parallel=0;
            omp_set_num_threads(k);

            start = omp_get_wtime();
            #pragma omp parallel 
            {
                #pragma omp single
                {
                    num_thread = omp_get_num_threads();
                }
                
                //method1
                // int private_sum=0;
                // #pragma omp for
                // for(int i=0;i<n;i++)
                // {
                //     private_sum+=arr[i];
                // }

                // #pragma omp critical
                // {
                //     sum_parallel +=private_sum;
                // }

                //method2
                #pragma omp for reduction(+:sum_parallel)
                for(int i=0;i<n;i++)
                {
                    sum_parallel+=arr[i];
                }

            }

            end = omp_get_wtime();
            total_time_parallel = end-start;
            cout<<"Serial sum- "<<sum_serial<<" Parallel sum- "<<sum_parallel<<endl;
            cout<<"total_time_parallel with threads("<<num_thread<<")- "<<total_time_parallel<<endl;
    }


     return 0;

}