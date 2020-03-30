#include<stdio.h>
#include<stdlib.h>

#define COUNT 10 //Ağaç satır satır yazdırılırken arada bırakılacak boşluk sayısını tanımlar

struct node{        //Struct yapımız
    char harf;       
    int frekans;
    struct node *next, *right, *left;
};
typedef struct node NODE;

NODE* varMi(NODE *head, char tmp){ //Listede o harfin olup olmadığına bakar
    NODE *current = head;          //Var ise o elemanı, yok ise NULL döndürür

    while(current->next && current->harf != tmp){
        current = current->next;
    }
    if(current->harf == tmp){
        return current;
    }
    else{
        return NULL;
    }
}

NODE* basaEkle(NODE *head, NODE* node, char tmp){

    node = (NODE*)malloc(sizeof(NODE));
    node->frekans = 1;          //Verilen elemana yer açıp, frekansını ilklendirir
    node->harf = tmp;           //ve o elemanı başa ekler.

    node->next = head;
    head = node;
    return head;
}

NODE* createList(NODE *head){
    
    FILE *fp = fopen("input.txt","r");      //Dosyadan paragrafı harf harf okuyarak
    char tmp;                               //varMi fonksiyonu kontrolü ile birlikte listeyi oluşturur
    if(head == NULL){
        head = (NODE*)malloc(sizeof(NODE)); //Eleman listenin ilk elemanı ise ona göre ilklendirme yapılır.
        head->harf = fgetc(fp);
        head->frekans = 1;
        head->next = NULL;
    }

    tmp = fgetc(fp);    //Karakter karakter okuma yapıp 
    while(!feof(fp)){   //dosya sonuna kadar listeyi adım adım oluşturur.
        NODE *node = varMi(head, tmp);
        if(node){
            node->frekans++;
        }
        else{
            NODE *node;
            head = basaEkle(head, node, tmp);
        }
        tmp = fgetc(fp);
        if(tmp =='\n'){   //Dosya sonundaki \n karakterini almaması için kontrol koyduğum bir kontrol.
            break;
        }
    }
    return head;
}

void yazdir(NODE *head){    //Linkli listeyi bastırmak için
    NODE *current = head;   //kullanılan fonksiyon.
    while(current->next){
        printf("(%d , %c) ->",current->frekans, current->harf);
        current = current->next;
    }
    printf("(%d , %c)\n",current->frekans, current->harf);
}

//Sırasız listemizdeki elemanları tek tek bu fonksiyona gönderip sıralı olarak
//yeni bir diziye yerleştirme (insert) işleminin yapıldığı fonksiyondur.
NODE* insertSorted(NODE* head, int frekans, char harf){  
   
    //Yeni node oluşturulur ve ilklendirmeler yapılır.
    NODE *current = head;
    NODE *node = (NODE*)malloc(sizeof(NODE)); 
    node->frekans = frekans;    
    node->harf = harf;
    node->next = NULL;
    
    if(head == NULL){   //Liste boş ise ilk eleman ataması yapılır.
        head = node;
        return head;
    }
    if(head->frekans > node->frekans){  //Eğer ekleme ilk elemana yapılacaksa
        node->next = head;              //gerekli işlemler yapılır.
        head = node;
        return head;
    }

    //Bir önceki elemanı tutarak insert edilecek konuma gelindiğinde
    //prev pointerı da kullanılarak node doğru konuma yerleştirilir.
    NODE *prev = current;   
    while(current->next && (node->frekans >= current->frekans)){
        prev = current;
        current = current->next;
    }
    if(node->frekans < current->frekans){
        prev->next = node;
        node->next = current;   //Araya eklenecek ise yapılacak işlemler
    }
    else{
        current->next = node;   //Sona eklenecek ise yapılacak işlemler
        node->next = NULL;
    }
    return head;
}

//Ödev dokümanında anlatıldığı şekilde left ve right
//pointerları atamalarıyla huffman ağacının oluşturulduğu fonksiyon.
NODE* createHuffmanTree(NODE* head){
    NODE *current = head;

    current->left = NULL;
    current->right = NULL;

    while(current->next){
        
        NODE *araNode = (NODE*)malloc(sizeof(NODE));

        araNode->frekans = current->frekans + current->next->frekans;
        araNode->harf = '*';                //Ara (parent) düğümler 
        araNode->left = current;            //için node'lar oluşturulur.
        araNode->right = current->next;     //ve harf olarak '*' ataması yapılır.
        araNode->next = NULL;               //left ve right pointerlara ise algoritma gereği
                                            //sıradaki iki uç düğüm eklenir.
        if(current->harf != '*'){           
            current->left = NULL;           //Eğer ara node'un left pointer'ına eklenecek düğüm 
            current->right = NULL;          //uç düğüm ise sağ ve sol pointer'larına NULL atanır.
        }
        if(current->next->harf != '*'){     //Aynı şekilde ara node'un left pointer'ına eklenecek düğüm
            current->next->left = NULL;     //uç düğüm ise sağ ve sol pointerlarına NULL atanır.
            current->next->right = NULL;
        }

        NODE *current2 = current;            //Ara node'un gerekli left ve right pointer atamaları yapıldıktan sonra   
        NODE *prev = current2;               //doğru konuma yerleştirildiği kısım.
        while(current2->next && (araNode->frekans > current2->frekans)){
            prev = current2;                 //Başa eklenemeyeceği için direkt araya yerleştirme için
            current2 = current2->next;       //doğru yer gerekli kontroller ile bulunur.
        }
        if(araNode->frekans <= current2->frekans){
            prev->next = araNode;            //Araya eklenecek ise gerekli işlemler yapılır.
            araNode->next = current2;       
        }
        else{
            current2->next = araNode;        //Sona eklenecek ise gerekli işlemler yapılır.
            araNode->next = NULL;
        }
        
        current = current->next->next;       //Algoritma gereği her tur iki eleman ilerlenir.
    }
    return head;
}

void print2D(NODE *root, int space){ 
    //Recursive çağrıyı, uç düğüme gelindiği için, bitiren kontrol. 
    if (root == NULL) 
        return; 
  
    //Estetik görünüm için boşluk bırakılan kısım
    space += COUNT; 
  
    //Right pointer üzerinden ilerleyerek önce ağacın sağ kısmı bastırılır
    print2D(root->right, space);  
    printf("\n"); 
    for (int i = COUNT; i < space; i++){
        printf(" "); 
    }  
    printf("(%d,%c)\n", root->frekans,root->harf); 
  
    //Left pointer üzerinden ilerleyerek ağacın sol kısmı bastırılır
    print2D(root->left, space); 
} 
  
//Recursive olarak yazılan asıl yazdırma fonksiyonuna gönderilecek elemana ulaşılan
//ve o elemanı yazdırma fonksiyonuna gönderen çevreleyici (wrapper) fonksiyon.
void print2Dimension(NODE *root){ 
    NODE *current = root; 
    while(current->next){       //Ağacın root'u listenin son elemanı olacağından
       current = current->next; //ona ulaşılır ve fonksiyona gönderilir.
    } 
    print2D(current, 0); 
} 

int main(){

    NODE *head = NULL;
    
    printf("\n------------------Unsorted Frequency List-----------------------------\n");
    head = createList(head); //Listeyi metinden okuyarak listeyi oluşturur
    yazdir(head);
    
    printf("\n------------------Sorted Frequency List-------------------------------\n");
    NODE *tmp = head;
    NODE *newHead = NULL;       //Oluşturulan listedeki her elemanı tek tek sıralı yerleştirme
    while(tmp){                 //fonksiyonuna gönderdiğim kısım.
        newHead = insertSorted(newHead,tmp->frekans,tmp->harf);
        tmp = tmp->next;
    }
    head = newHead;
    yazdir(head);
    
    printf("\n-------------------Huffman List----------------------------------------\n");
    head = createHuffmanTree(head); //Sıralı liste kullanılarak ağacın oluşturulduğu fonksiyon.
    yazdir(head);
    
    printf("\n-----------------------TREE--------------------------------------------\n");
    print2Dimension(head);          //Ağacın seviye seviye ekrana bastırılması

    return 0;
}
