
#include<iostream>
#include<omp.h>
double total_time_serial,total_time_parallel;
using namespace std;
int main()  
{
    int n = 40000;
    int * vec = new int[n];
    int ** mat = new int*[n];
        for(int i=0;i<n;i++)
        {
            mat[i] = new int[n];
        }
    int * sum_serial = new int[n];
    int * sum_parallel = new int[n];
    double start, end;
    int num_thread;

        for(int i=0;i<n;i++)
        {
            vec[i] = rand();
            sum_parallel[i]=0;
            sum_serial[i]=0;        

            for(int j=0;j<n;j++)
            {
                mat[i][j] = rand();
            }     
        }
        
    start = omp_get_wtime(); 
    
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
        sum_serial[i] += vec[j]*mat[i][j];
        }
    }

     end = omp_get_wtime();

     //total_time_serial = ((double) (end - start));
     total_time_serial = end-start;

    cout<<"total_time_serial- "<<total_time_serial<<endl;

    for(int k=1;k<=4;k++)
    {
            omp_set_num_threads(k);

            start = omp_get_wtime();
            #pragma omp parallel 
            {
                #pragma omp single
                {
                    num_thread = omp_get_num_threads();
                }
                
                #pragma omp for collapse(2)
                for(int i=0;i<n;i++)
                {
                    for(int j=0;j<n;j++)
                    {
                    sum_parallel[i] += vec[j]*mat[i][j];
                    }
                }

                // int * private_sum = new int[n];

                // #pragma omp for collapse(2)
                // for(int i=0;i<n;i++)
                // {
                //     for(int j=0;j<n;j++)
                //     {
                //     private_sum[i] += vec[j]*mat[i][j];
                //     }
                // }

                // #pragma omp critical
                // for (int q = 0; q<n; q++)
                // {
                //     sum_parallel[q] += private_sum[q];
                // }
            }

            end = omp_get_wtime();
            total_time_parallel = end-start;
            
            // for(int i=0;i<n;i++)
            // {
            //     cout<<sum_serial[i]<<" "<<sum_parallel[i]<<endl;
            // }

            cout<<"total_time_parallel with threads("<<num_thread<<")- "<<total_time_parallel<<endl;
 
       }        

     return 0;

}