#include<stdio.h>
#include<stdlib.h>

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
        while(current2->next && (araNode->frekans >= current2->frekans)){
            prev = current2;                 //Başa eklenemeyeceği için direkt araya yerleştirme için
            current2 = current2->next;       //doğru yer gerekli kontroller ile bulunur.
        }
        if(araNode->frekans < current2->frekans){
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

//Kuyruk yapısını yalnızca ağaç şeklinde yazdırma işleminde kullandım.
//Kuyruk yapısı için önceki haftalarda yazdığımız kodlar
struct QNode{
    NODE *node; //Kuyruk yapısında value olarak NODE tipinde değişken tutulur
    struct QNode *next;
};

struct Queue{
    struct QNode *front, *rare; //Kuyruk yapısının başını ve sonunu tutacak pointerları
};                              //tutan struct yapısı

struct Queue *createQueue(){
    //Kuyruğun oluşturulduğu fonksiyon
    struct Queue *q;
    q = (struct Queue*)malloc(sizeof(struct Queue));
    if(q == NULL){
        exit(0);
    }//Gerekli ilklendirmeler ve NULL atamaları yapılır
    else{
        q->front = q->rare = NULL;
        return q;
    }
}
//Kuyruğa yeni eleman eklemek için kullandığımız fonksiyon
void enqueue(struct Queue *q, NODE *node){

    struct QNode *tmp;
    tmp = (struct QNode*)malloc(sizeof(struct QNode));
    if(tmp == NULL){
        exit(0);
    }
    tmp->node = node;
    tmp->next = NULL;
    if(q->front == NULL){
        q->front = q->rare = tmp;
    }
    else{
        q->rare->next = tmp;
        q->rare = tmp;
    }
}
//Kuyruktan eleman çıkartmak için kullandığımız fonksiyon
NODE* dequeue(struct Queue *q){

    NODE *node;
    if(q->front == NULL){
        printf("Queue is empty!\n");
        return NULL;
    }
    else{
        node = q->front->node;
        struct QNode *tmp;
        tmp = q->front;
        q->front = tmp->next;
        
        if(q->front == NULL){
            q->rare = NULL;
        }
        free(tmp);
        
        return node;
    }
}
//Ağacın her levelini ayrı bir satıra bastıran fonksiyon
void printLevelbyLevel(struct Queue *q, NODE *head){
    
    NODE *nullNode = (NODE*)malloc(sizeof(NODE));
    nullNode->frekans = 0;      //Bu kısımda child'ı olmayan nodeların
    nullNode->harf = '-';       //alt satırda karışıklık yaratmaması amacıyla
    nullNode->right = NULL;     //olmayan çocukların yerine ' - ' sembolünün
    nullNode->left = NULL;      //harf olarak atandığı bir node oluşturulur.

    NODE *current = head; 
    while(current->next){       //Ağacın kökü Huffman dizisinin son elemanı
       current = current->next; //olduğundan, son elemana gelinir.
    }

    enqueue(q, current);        //Burada gerçekleştirilen algoritma;
    enqueue(q, NULL);           //Öncelikle ağacın kökü ve bir NULL değer kuyruğa atılır.
    current = dequeue(q);       //Sonrasında ilk atanan değer kuyruktan çekilir (yani root değeri)
    while(current){                      //Yukarıda yapılanlardan sonra girilen while döngüsünde her tur
        if(current->left){               //Current node'unun left ve right child'ları varsa kuyruğa atılır
            enqueue(q, current->left);      
        }
        else if(current->harf != '-'){   //Yoksa nullNode kuyruğa atılır
            enqueue(q, nullNode);
        }
        if(current->right){              //left için yapılanlar right için tekrarlanır
            enqueue(q, current->right);
        }
        else if(current->harf != '-'){
            enqueue(q, nullNode);
        }
        if(current->harf =='-'){        //Yazdırırken eğer nullNode ise sadece ' - ' yazdırılır
            printf(" - ");
        }
        else{
            printf("(%2d,%c) ",current->frekans,current->harf);
        }                                //Değil ise current değişkeni ekrana yazdırılır
        current = dequeue(q);            //Tekrar kuyruktan bir eleman alınır,
        if(current == NULL){             //Eğer alınan değer NULL ise
            enqueue(q, NULL);            //tekrar kuyruğun sonuna NULL değer atanır
            printf("\n");                //Bir satır alta inilir
            current = dequeue(q);        //ve kuyruktan bir eleman daha alınır
        }                                //Bu şekilde current node NULL olana kadar yani kuyrukta eleman
    }                                    //kalmayana kadar döngüye devam edilir.
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
    struct Queue *q;                //Yazdırma işleminde kullanılacak olan kuyruğun oluşturulması
    q = createQueue();              
    printLevelbyLevel(q,head);      //Satır satır yazdırma fonksiyonu

    return 0;
}