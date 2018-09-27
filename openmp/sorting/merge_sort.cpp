#include<iostream>
#include<omp.h>
double total_time_serial,total_time_parallel;
using namespace std;

void merge(int arr[],int l,int m,int r)
{
	//SIZE
	int size1 = m - l +1; // m - (l-1) ---removing prev part upto (l-1)	
	int size2 = r - m;    // 2nd array from m+1 to r --- removing prev part upto m
	int i,j,k;            // ptrs
	
	//Get Part
	int L[size1],R[size2];
	for(i=0;i<size1;i++)
		L[i] = arr[l+i];  // get arr part from l to size1
	for(j=0;j<size2;j++)
		R[j] = arr[m + 1 + j]; // get arr part from m+1 to size2

	//COMBINE
	i=0;   //ptr to L[]
	j=0;   //ptr to R[]
	k=l;

			//combine L[] and R[] into arr in place l to r with sort
	while( i<size1 && j<size2)
	{
		if(L[i]<=R[j])	
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there 
       are any */
    while (i < size1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < size2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 		
		 
}


void mergesort(int arr[],int l,int r)
{
	if(l < r)
	{	
		// Same as (l+r)/2, but avoids overflow for 
        // large l and r
		int m = l + (r-l)/2;
		
		mergesort(arr,l,m);
		mergesort(arr,m+1,r);

		merge(arr,l,m,r); 
	}	
}

void mergesort_parallel(int arr[],int l,int r)
{
	if(l < r)
	{	
		// Same as (l+r)/2, but avoids overflow for 
        // large l and r
		int m = l + (r-l)/2;
		
		#pragma omp task firstprivate (arr,l,r)
		mergesort(arr,l,m);
		
		#pragma omp task firstprivate (arr,l,r)
		mergesort(arr,m+1,r);

        #pragma omp taskwait
		merge(arr,l,m,r); 
	}	
}
int main()  
{
    int n = 2000;
    int * arr = new int[n];
	int * arr2 = new int[n];
    double start, end;
    int num_thread;
    
        for(int i=0;i<n;i++)
        {
            arr[i] = rand(); 
	    	arr2[i] = arr[i];   
        }
        
	start = omp_get_wtime(); 
     	
	//Serial Merge Sort
	
	mergesort(arr,0,n-1);
	        
	end = omp_get_wtime();

    total_time_serial = end-start;
    
	cout<<"Merge Sort total_time_serial- "<<total_time_serial<<endl;


     	
    //for(int k=4;k<=4;k++)
   // {
            //omp_set_num_threads(k);

            start = omp_get_wtime();
		
           /* #pragma omp parallel 
            {
                num_thread = omp_get_num_threads();
			}*/

               #pragma omp parallel
               {
                  #pragma omp single
                  mergesort_parallel(arr2, 0, n-1);
               }
            
            
            end = omp_get_wtime();
            total_time_parallel = end-start;
            cout<<"total_time_parallel"<<total_time_parallel<<endl;
    //}

	
	cout<<"MergeSort serial\t"<<"MergeSort Parallel"<<endl;	 
	bool flag=true;	
	for(int i=0;i<n;i++)
     {
                
         cout<<arr[i]<<"\t\t"<<arr2[i]<<endl;
		if(arr[i]!=arr2[i])
		 flag=false;	
     }

	if(flag)
	cout<<"\ncorrect\n";
	else
	cout<<"\nIncorrect\n";

     return 0;

}
