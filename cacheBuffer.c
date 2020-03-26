#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
    char site[30];          //Struct yapısı oluşturuldu.
    int counter;
    struct node *next;
    struct node *prev;
};

struct node* siteVarMi(char* site, struct node*head){    //Sitenin bufferda olup olmadığı kontrolünün ardından
                                                        //Varsa o node'un pointerını yoksa NULL değeri döndürerek işini yapar.
    struct node *current = head;
    while(current->next != NULL  &&  strcmp(current->site, site) != 0){
        current = current->next;
    }
    if(!strcmp(current->site, site)){
        return current;
    }
    else{
        return NULL;
    }
}

struct node* sondanSil(struct node *head){           //Linkli listenin sonuna ulaşıp sondaki elemanı
                                                    //Free ederek siler.
    struct node *current = head;
    while(current->next){
        current = current->next;
    }
    current->prev->next = NULL;
    free(current);
    
    return head;
}

struct node* basaEkle(struct node *head, struct node *node, int *counter){
    
    (*counter)++;
    node->counter = 0;    //Başa eleman ekler ve linkli listedeki eleman sayısını tutan counter değişkenini bir artırır.
    node->prev = NULL;
    node->next = head;
    head->prev = node;
    
    return node;
}

struct node* temizle(struct node* head){
    
    struct node *tmp = head;  //tmp değişkeni yardımı ile head'den başlayarak liste sonuna kadar bütün elemanları free eder.
    while(head){
        tmp = head;
        head = head->next;
        free(tmp);
    }
    return NULL;
}

struct node* doublyLinkedListOlustur(int T, int L, struct node *head,int *counter,char *site){  //Asıl algoritmanın çalıştığı kısım.
   
    if(head == NULL){                                           //Başlangıçta veya temizledikten sonra head NULL olacağından
        head = (struct node*)malloc(sizeof(struct node));       //Head'i ilklendirme işi bu if bloğunun içinde yapılır.
        head->prev = NULL;
        head->next = NULL;
        head->counter = 1;
        strcpy(head->site,site);
    }
    else{
        struct node *tmp = siteVarMi(site, head);          //Sitenin listede olup olmadığını kontrol eden fonksiondan dönen değere göre
        if(tmp != NULL){                                   //NULL değil ise yani listede var ise counter'ını bir artırır.
            (tmp->counter)++;
            if(tmp->counter > T && tmp->prev != NULL && tmp->next != NULL){   //Counter'ı eşik değerini aşan elemanların başa alınması işlemleri 
                head->prev = tmp;                                             //gelecek 3 if bloğunda yapılmaktadır.
                tmp->prev->next = tmp->next;            //Başa alınacak eleman ortada ise ona uygun pointer işlemleri yapılır.
                tmp->next->prev = tmp->prev;
                tmp->next = head;
                tmp->prev = NULL;
                head = tmp;
            }
            else if(tmp->next == NULL && tmp->prev == NULL){
                //Zaten başta ve tek başına ise pointerlar ile işlem yapılmaz.
            }
            else if(tmp->counter > T && tmp->next == NULL){     //Eleman sonda ise duruma uygun pointer işlemleri uygulanır.
                head->prev = tmp;
                tmp->prev->next = NULL;
                tmp->next = head;
                tmp->prev = NULL;
                head = tmp;
            }

        }
        else{                                                  //Sitenin listede olmadığı durumda girilen else durumunda
            struct node *node;                                 //Yeni bir node için yer açılır, node başa eklenir ve ilklendirilir.
            node =(struct node*)malloc(sizeof(struct node));
            node->counter = 1;
            head =basaEkle(head,node,counter);

            if(*counter > L){
                head = sondanSil(head);             //Yeni eklenen eleman sonucu liste boyu verilen değeri aştı ise sondan eleman silinir.
            }   

            head->counter += 1;
            strcpy(head->site,site);
        }
    }
    return head;
}

void yazdir(struct node *head){           //Linkli listelerde kullanılar klasik yazdırma işlemi uygulanmıştır.
                                                
    struct node *current = head;
    while(current->next){
        printf(" (%s,%d) <-->",current->site,current->counter);
        current = current->next;
    }
    printf(" (%s,%d)",current->site,current->counter);
}


int main(){

    struct node *head = NULL;
    printf("------------CACHE BUFFER-----------\n");
    printf("Veriler dosyadan okunacak ise 'F'\nVeriler tek tek girilecekse 'H' girisi yapiniz: ");
    
    char secim;
    scanf("%c",&secim);         //Seçim değişkeni dosya veya elle girdi seçeneklerini kullanıcıdan alır.
    
    int T,L;
    int nodeCounter = 1;
    char site[30];
    if(secim == 'h'){           //Elle girilir ise bu if bloğu çalışır.
        
        printf("\nEsik degerini giriniz: ");
        scanf("%d",&T);
        printf("\nBuffer uzunlugunu giriniz: ");
        scanf("%d",&L);
        printf("\n---------Giris yapmak icin G'ye basiniz--------------------\n---------Listeyi tmeizlemek icin C'ye basiniz--------------");
        printf("\n---------Girdi girisini sonladirmak icin Q'ya basiniz------");

        do{                         //girdi, temizleme ve çıkış seçenekleri kullanıcıya yine secim değişkeni yardımı ile sunulur.
            printf("\nSecim:");                 
            scanf(" %c",&secim);
            if(secim == 'g'){
                printf("\tSitenin adini giriniz:");
                scanf("%s",site);
                head = doublyLinkedListOlustur(T,L,head,&nodeCounter,site);     //bilgileri alınan site uygun biçimde listeye yerleştirilir
                yazdir(head);                                                   //ve yazdırılır.
            }
            else if(secim == 'c'){          
                head = temizle(head);                                           //temizleme fonksiyonu yardımıyla liste temizlenir
                nodeCounter = 1;                                                //ve listedeki node sayısı yeniden ilklendirilir.
                printf("~~~~~buffer temizlendi~~~~~~~~~");
            }
        }while(secim != 'q');   //Çıkış değeri olan q girilene kadar döngüde kalır.
    }
    else if(secim == 'f'){      //Dosyadan okunacak ise buradaki else if bloğu çalıştırılır.
        
        FILE *fp;
        char fileName[20];
        printf("\n\nDosyanin adini uzantisi ile birlikte giriniz: ");
        scanf("%s",fileName);           //dosya adı kullanıcıdan alınır ve adım adım okuma yapılır.
        fp = fopen(fileName,"r");

        fscanf(fp,"%d",&T);
        printf("\nEsik degeri: %d",T);
        fscanf(fp,"%d",&L);
        printf("\nBuffer uzunlugu: %d",L);
        printf("\n\n  ---------Adim adim dosya sonuna ilerlemek icin S'ye basiniz--------------------\n");
        printf("---------(Dosyadan okunan clear kelimesi ile cache buffer temizlenir)----------\n");
        
        fscanf(fp,"%s",site);
        do{                             //Her s girişinde bir site adı dosyadan okunur ve listeye uygun biçimde yerleştirilir.
            printf("\nSecim:");        
            scanf(" %c",&secim);
            if(!strcmp(site,"clear")){  //Eğer dosyadan okunan değer clear'a eşit ise buffer temizleme işlemi yapılır.
                head = temizle(head);   //ve node sayısı yeniden ilklendirilir.
                nodeCounter = 1;
                printf("~~~~~buffer temizlendi~~~~~~~~~");
            }
            else{
                head = doublyLinkedListOlustur(T,L,head,&nodeCounter,site);    
                yazdir(head);           //clear harici okunan site isimleri uygun biçimde listeye yerleştirilir.
            }
            fscanf(fp,"%s",site);
        }while(!feof(fp) && secim == 's');
        printf("\n\n----------Dosya okumasi tamamlandi---------------\n\n");

    }
    temizle(head);      //Bütün program sonlandığında ayrılan yerlerin hepsi free edilir.
    printf("\n\n~~~~~~~~~~~~~~~Buffer Free Edildi~~~~~~~~~~~~~~~~~~\n\n");
    return 0;
}
