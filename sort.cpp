#include<iostream>
#include<omp.h>
#include<bits/stdc++.h>
using namespace std;


void bubbleSort(int arr[],int n){
    for(int i = 0; i < n - 1; i ++){
        for(int j = 0; j < n - i - 1; j++){
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void parallelBubbleSort(int a[],int n){
    for(int i=0;i<n;i++) {       
    	int first = i % 2;      
	#pragma omp parallel for shared(a,first)
        for(int j=first; j<n-1; j+=2){       
            if(a[j]>a[j+1]){       
                 swap(a[j],a[j+1]);
            }        
        }        
    }

}


void merge(int array[],int low, int mid, int high,int size){
    int temp[size];
    int i = low;
    int j = mid + 1;
    int k = 0;
    while((i <= mid) && (j <= high)){
        if(array[i] >= array[j]){
            temp[k] = array[j];
            k++;
            j++;
        }
        else{
            temp[k] = array[i];
            k++;
            i++;
        }
    }
    while(i <= mid){
        temp[k] = array[i];
        k++;
        i++;
    }
    while(j <= high){
        temp[k] = array[j];
        k++;
        j++;
    }
    k = 0;
    for(int i = low;i <= high;i++){
        array[i] = temp[k];
        k++;
    }
}

void merge_sort(int array[],int low,int high,int size){
    if(low < high){
        int mid = (low + high) / 2;
         #pragma omp parallel sections
        {
		#pragma omp section
		{
			merge_sort(array,low,mid,size);
		}
		#pragma omp section
		{
			merge_sort(array,mid+1,high,size);
		}
	}
        merge(array,low,mid,high,size);
    }
}

void mergeSortSequential(int arr[],int size){
    merge_sort(arr,0,size-1,size);
    for(int i=0; i<size; i++) cout<<arr[i]<<" ";
    cout<<endl;
}


void ParallelMergeSort(int arr[],int size){
    
        #pragma omp single nowait
    	merge_sort(arr,0,size-1,size);
   
}




int main(int argc, char const *argv[])
{
    int SIZE;
    int MAX = 1000;
    cout << "Enter size of array: ";
    cin >> SIZE;
    int array[SIZE];
    for(int i = 0 ; i < SIZE; i ++){
        array[i] = rand() % MAX;
    }
    
    auto start = chrono::high_resolution_clock::now();
    bubbleSort(array,SIZE);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> sequential_duration = end - start;
    cout << "Sequential Bubble Sort took : " << sequential_duration.count() << " microseconds.\n";

    start = chrono::high_resolution_clock::now();
    parallelBubbleSort(array,SIZE);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> parallel_duration = end - start;
    cout << "Parallel Bubble Sort took : " << parallel_duration.count() << " microseconds.\n";
    cout<<"Speed up (Bubble sort) : "<<sequential_duration/parallel_duration<<endl;

    start = chrono::high_resolution_clock::now();
    mergeSortSequential(array,SIZE);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> sequential_duration2 = end - start;
    cout << "Sequential Merge Sort took : " << sequential_duration2.count() << " microseconds.\n";

    start = chrono::high_resolution_clock::now();
    ParallelMergeSort(array,SIZE);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> parallel_duration2 = end - start;
    cout << "Parallel Merge Sort took : " << parallel_duration2.count() << " microseconds.\n";
    cout<<"Speed up (merge sort) : "<<sequential_duration2/parallel_duration2<<endl;

    return 0;
}
