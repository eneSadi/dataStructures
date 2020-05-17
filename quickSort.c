#include<stdio.h>

int partition (int arr[],int low,int high){
    // pivot (Element to be placed at right position)
    int pivot = arr[high];  
 
    int i = (low - 1);  // Index of smaller element

    for(int j = low; j <= high - 1; j++){
        // If current element is smaller than the pivot
        if (arr[j] < pivot){
            i++;    // increment index of smaller element
            
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
    int tmp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = tmp;
    
    return (i + 1);
}

void quickSort(int arr[],int low,int high){
    int pi;
    
    if (low < high){

        pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main(){

    int arr[] = {10,5,4,15,2,1,8,69,4,1};  
    
    quickSort(arr, 0, 9);

    for(int i = 0 ; i < 10 ; i++){
        printf("%d -- ", arr[i]);
    }

    return 0;
}



