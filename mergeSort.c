#include<stdio.h>
#include<stdlib.h>

void merge(int a[], int p, int q, int r){

    int i = p, j = q+1, k = 0, nb = r-p+1, *b;
    b = (int*)malloc(nb * sizeof(int));

    while((i <= q) && (j <= r)){
        if(a[i] < a[j]){
            b[k++] = a[i++];
        }
        else{
            b[k++] = a[j++];
        }
    }
    while(i <= q){
        b[k++] = a[i++];
    }
    while(j <= r){
        b[k++] = a[j++];
    }
    for(i = p, k = 0; i <= r; i++, k++){
        a[i] = b[k];
    }
    free(b);
}

void mergeSort(int a[], int p, int r){  //initial p = 0, r = n - 1
    int q;
    if(p < r){
        q = (p + r) / 2;
        mergeSort(a , p, q);
        mergeSort(a, q+1, r);
        merge(a, p, q, r);
    }
}

int main(){

    int a[] = {8,7,6,5,4,3,2,1};
    mergeSort(a, 0, 7);
    
    for(int i = 0 ; i < 8 ; i++){
        printf("%d , ", a[i]);
    }

    return 0;
}