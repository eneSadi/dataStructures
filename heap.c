#include<stdio.h>

void siftUp(int item, int heap[], int n){
    
    int parent;
    int stop = 0;
    while((n > 0) && (!stop)){
        parent = (n-1)/2;
        if(heap[parent] < item){
            int tmp = heap[parent];
            heap[parent] = heap[n];
            heap[n] = tmp;
            n = parent;
        }
        else{
            stop = 1;
        }
    }
}

void insert(int item, int heap[], int n){
    heap[n] = item;
    siftUp(item, heap, n);
}

void printHeapArr(int heap[], int n){
    int i;
    for(i=0;i<n;i++){
        printf("%d ,",heap[i]);
    }
}

int findChild(int heap[], int parent, int n){

    int c1 = 2*parent + 1;
    int c2 = 2*parent + 2;

    if(c2 < n){
        if(heap[c1] < heap[c2]){
            return c2;
        }
        else{
            return c1;
        }
    }
    else if(c1 < n){
        return c1;
    }
    else{
        return -1;
    }
}

void siftDown(int heap[], int n){

    int parent = 0, child;
    int childIndex = findChild(heap, parent, n);
    while(childIndex != -1 && heap[childIndex] > heap[parent]){
        int tmp = heap[parent];
        heap[parent] = heap[childIndex];
        heap[childIndex] = tmp;
        
        parent = childIndex;
        childIndex = findChild(heap, parent, n);
    }
}

void pop(int heap[], int n){
    int max = heap[0];
    
    heap[0] = heap[n-1];

    siftDown(heap, n-1);
    heap[n-1] = max;
}

int main(){

    int heap[50];
    printf("Eleman sayisini giriniz: ");
    int n;
    scanf("%d",&n);
    
    int i, tmp;
    for(i = 0 ; i < n ; i++){
        printf("%d. elemani giriniz: ",i+1);
        scanf("%d",&tmp);
        insert(tmp, heap, i);
    }
    printf("\n\n----------Heap Array---------------\n");
    printHeapArr(heap, n);

    for(i = n ; i > 0 ; i--){
        pop(heap, i);
    }
    printf("\n\n---------After Heap Sort-----------\n\n");
    printHeapArr(heap, n);
    
    printf("\n\n-----------------------------------\n\n");
    
    return 0;
}
