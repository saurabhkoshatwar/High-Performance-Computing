
#include<iostream>
#include<omp.h>
double total_time_serial,total_time_parallel;
using namespace std;
int main()  
{
    int n = 100000;
    int * vec = new int[n];
    int * mat = new int[n][n];
    int * sum_serial = new int[n];
    int * sum_parallel = new int[n];
    double start, end;
    int num_thread;

    
        for(int i=0;i<n;i++)
        {
            vec[i] = rand();

            for(int j=0;j<n;j++)
            {
                mat[i][j] = rand();
            }     
        }
        
    start = omp_get_wtime(); 
    
    for(int i=0;i<n;i++)
    {
        sum_serial[i]=0;
        for(int j=0;j<n;j++)
        {
        sum_serial[i] += vec[j]*mat[i][j];
        }
    }

     end = omp_get_wtime();

     //total_time_serial = ((double) (end - start));
     total_time_serial = end-start;

    cout<<"total_time_serial- "<<total_time_serial<<endl;

    for(int i=1;i<=4;i++)
    {
            omp_set_num_threads(i);

            start = omp_get_wtime();
            #pragma omp parallel 
            {
                #pragma omp single
                {
                    num_thread = omp_get_num_threads();
                }
                
                #pragma omp for
                for(int i=0;i<n;i++)
                {
                    sum_parallel[i] = vec1[i] + vec2[i];
                }
            }

            end = omp_get_wtime();
            total_time_parallel = end-start;
            cout<<"total_time_parallel with threads("<<num_thread<<")- "<<total_time_parallel<<endl;
    }
    // for(int i=0;i<n;i++)
    // {
    //     cout<<vec1[i]<<" "<<vec2[i]<<" "<<sum_serial[i]<<" "<<sum_parallel[i]<<endl;
    // }
     return 0;

}