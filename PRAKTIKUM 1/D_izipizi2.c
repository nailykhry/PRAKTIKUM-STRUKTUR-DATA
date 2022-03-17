//langkah langkah jual kambing

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


typedef struct snode_t {
    int data;
    struct snode_t *next;
} SListNode;


typedef struct slist_t {
    unsigned size;
    SListNode *head;
} SinglyList;

/* DAFTAR FUNGSI YANG TERSEDIA */

void slist_init(SinglyList *list);
bool slist_isEmpty(SinglyList *list);
void slist_popFront(SinglyList *list);
void slist_pushBack(SinglyList *list, int value);
int  slist_getAt(SinglyList *list, int index);
void pil1(SinglyList *list);
void pil2(SinglyList *list);
void pil3(SinglyList *list);


int main()
{
    //inisialisasi
    SinglyList kambingKu;
    slist_init(&kambingKu);
    //memulai
    while(1)
    {
        //memilih pilihan
        int pilihan;
        scanf("%d", &pilihan);
        //aksi sesuai pilihan
        switch(pilihan)
        {
            case 1 :
                pil1(&kambingKu);
                break;
                
            case 2 :
                pil2(&kambingKu);
                break;
                
            case 3 :
                pil3(&kambingKu);
                break ;
                
            case 4 :
                printf("Keluar!\n");
                return 0;
                break;
                
            default :
                printf("Menu tidak tersedia!\n");
                break;
        }
    }
    return 0;
}

void slist_init(SinglyList *list) 
{
    list->head = NULL;
    list->size = 0;
}

//cek kosong
bool slist_isEmpty(SinglyList *list) 
{
    return (list->head == NULL);
}

//hapus depan
void slist_popFront(SinglyList *list)
{
    if (!slist_isEmpty(list)) {
        SListNode *temp = list->head;
        list->head = list->head->next;
        free(temp);
        list->size--;
    }
}

//masuk belakang
void slist_pushBack(SinglyList *list, int value)
{
    SListNode *newNode = (SListNode*) malloc(sizeof(SListNode));
    if (newNode) 
    {
        list->size++;
        newNode->data = value;
        newNode->next = NULL;
        
        if (slist_isEmpty(list)) 
            list->head = newNode;
        else {
            SListNode *temp = list->head;
            while (temp->next != NULL) 
                temp = temp->next;
            temp->next = newNode;
        }
    }
}

//ambil pada idx tertentu
int slist_getAt(SinglyList *list, int index)
{
    if (!slist_isEmpty(list)) 
    {
        SListNode *temp = list->head;
        int i = 0;
        while (temp->next != NULL && i < index) {
            temp = temp->next;
            i++;
        }
        return temp->data;
    }
    return 0;
}


void pil1(SinglyList *list)
{
    //masuk nihh
    int element;
    scanf("%d", &element);
    
    if(!element) //element 0
        printf("Tidak Masok!\n");
    else
    {
        slist_pushBack(list, element);
        printf("Masok!\n");
    }
}

void pil2(SinglyList *list)
{
    //jual atau hapus element pertama
    //cek ada ga
    if(slist_isEmpty(list))
        printf("Data belum ada!\n");
    else
    {
        slist_popFront(list);
        printf("Deleted!\n");
    }
}

void pil3(SinglyList *list)
{
    //cek duit 
    //kalo ga kosong hitung bulan*12 = tahun
    if(slist_isEmpty(list))
        printf("Data kosong!\n");
    else
    {
        //inisialisasi
        int sum = 0;
        int len = list->size;
        int i;
        //cek nilai satu2
        for(i=0; i<len; i++)
        {
            printf("%d ", slist_getAt(list, i));
            sum += slist_getAt(list, i);
        }
        //tampilkan
        printf("%d\n", sum*12*5000);
    }
}
