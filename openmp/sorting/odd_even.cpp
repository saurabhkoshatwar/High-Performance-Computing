
#include<iostream>
#include<omp.h>
double bbs_total_time_serial,oes_total_time_serial,total_time_parallel;
using namespace std;


void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int main()  
{
    int n = 10000;
    int * arr = new int[n];
	int * arr2 = new int[n];
	int * arr3 = new int[n];
    double start, end;
    int num_thread;
    
        for(int i=0;i<n;i++)
        {
            arr[i] = rand(); 
	    	arr2[i] = arr[i];
	    	arr3[i] = arr[i];    
        }
        
	start = omp_get_wtime(); 
     	
	//Bubble sort
	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(arr[j] > arr[j+1])
			{		
			swap(arr[j],arr[j+1]);
			}		
		}
	}

	end = omp_get_wtime();

    bbs_total_time_serial = end-start;
    
	cout<<"Bubble Sort total_time_serial- "<<bbs_total_time_serial<<endl;

	start = omp_get_wtime(); 
     	
	//Odd Even Sort
	bool isSorted = false; // Initially array is unsorted
 
    while (!isSorted)
    {
        isSorted = true;
 
        // Perform Bubble sort on odd indexed element
        for (int i=1; i<=n-2; i=i+2)
        {
            if (arr2[i] > arr2[i+1])
             {
                swap(arr2[i], arr2[i+1]);
                isSorted = false;
              }
        }
 
        // Perform Bubble sort on even indexed element
        for (int i=0; i<=n-2; i=i+2)
        {
            if (arr2[i] > arr2[i+1])
            {
                swap(arr2[i], arr2[i+1]);
                isSorted = false;
            }
        }
    }

	end = omp_get_wtime();

    oes_total_time_serial = end-start;
    
	cout<<"Odd even Sort total_time_serial- "<<oes_total_time_serial<<endl;

    for(int k=1;k<=4;k++)
    {
            omp_set_num_threads(k);

            start = omp_get_wtime();
		
            #pragma omp parallel 
            {
                num_thread = omp_get_num_threads();
			}

		bool isSorted = false;
		while (!isSorted)
   		{
        	isSorted = true;
            #pragma omp parallel 
            {
                
                #pragma omp for
                for (int i=1; i<=n-2; i=i+2)
       			 {
				     if (arr3[i] > arr3[i+1])
				     {
				        swap(arr3[i], arr3[i+1]);
						#pragma omp critical
				        isSorted = false;
				     }
        		 }
				//#pragma omp for nowait    // odd even parallel (wrong way/correct ans/more loops)
				#pragma omp for 
				for (int i=0; i<=n-2; i=i+2)
				{
				    if (arr3[i] > arr3[i+1])
				    {
				        swap(arr3[i], arr3[i+1]);
						#pragma omp critical
				        isSorted = false;
				    }
				}
            }
		}

            end = omp_get_wtime();
            total_time_parallel = end-start;
            cout<<"total_time_parallel with threads("<<num_thread<<")- "<<total_time_parallel<<endl;
    }

	
	//cout<<"Bubble sort serial\t"<<"Odd Even Sort Serial\t"<<"Odd Even Sort Parallel"<<endl;	 
	bool flag=true;	
	for(int i=0;i<n;i++)
     {
         //cout<<arr[i]<<"\t\t"<<arr2[i]<<"\t\t"<<arr3[i]<<endl;
		 if(arr[i]!=arr2[i] && arr3[i]!=arr2[i])
		 flag=false;	
     }

	if(flag)
	cout<<"\ncorrect\n";
	else
	cout<<"\nIncorrect\n";

     return 0;

}
