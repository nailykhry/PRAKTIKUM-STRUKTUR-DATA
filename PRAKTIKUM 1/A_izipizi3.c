//tata titi
//ambil nama

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include  <stdbool.h>
#define MAX 25

typedef struct node {
    char data[MAX];
    struct node *next;
} node;


typedef struct queue {
    node   *front, 
           *rear;
    unsigned size;
} Queue;

typedef struct darray
{
    Queue *arr;
    unsigned size, capacity;
}DynamicArray;

void dArray_init(DynamicArray*);
bool dArray_isEmpty(DynamicArray*);
void dArray_pushBack(DynamicArray*, Queue);
void dArray_popBack(DynamicArray*);
Queue  dArray_back(DynamicArray*);
Queue  dArray_front(DynamicArray*);


void queue_init(Queue *queue);
bool queue_isEmpty(Queue *queue);
void queue_push(Queue *queue, char value[]);
void queue_pop(Queue *queue);
char*  queue_front(Queue *queue);
int  queue_size(Queue *queue);

void pil1(DynamicArray*);
void pil2(DynamicArray *);



int main()
{
    DynamicArray listnya;
    dArray_init(&listnya);
    
    int kueri, pilihan;
    scanf("%d", &kueri);
    
    while(kueri--)
    {
        scanf("%d", &pilihan);
        switch(pilihan)
        {
            case 1 :
                pil1(&listnya); //masukkan
                break;
            case 2 : 
                pil2(&listnya);	//ambil
                break;
            default :
                printf("Hadeh\n");
        }
    }
    return 0;
}




void queue_init(Queue *queue)
{
    queue->size = 0;
    queue->front = NULL;
    queue->rear = NULL;
}

//cek kosong 
bool queue_isEmpty(Queue *queue) 
{
    return (queue->front == NULL && queue->rear == NULL);
}

//masuk dari belakang
void queue_push(Queue *queue, char value[])
{
    node *newNode = (node*) malloc(sizeof(node));
    if (newNode) 
    {
        //size ditambah
        queue->size++;
        
        //ganti
        //newNode->data = value;
        strcpy(newNode->data, value);
        newNode->next = NULL;
        
        //kalau kosong maka depan dan rear sama dengan newNode
        if (queue_isEmpty(queue))                 
            queue->front = queue->rear = newNode;
        //kalau ga kosong 
        else 
        {
            queue->rear->next = newNode;
            queue->rear = newNode;
        }
    }
}

//hapus depan
void queue_pop(Queue *queue)
{
    //gabole kosong
    if (!queue_isEmpty(queue)) 
    {
        //yang depan akan dihapus. terus depannya jadi elemen selanjutnya
        node *temp = queue->front;
        queue->front = queue->front->next;
        free(temp);
        
        //hapus
        if (queue->front == NULL)
            queue->rear = NULL;
        queue->size--;
    }
}

//akses depan
char* queue_front(Queue *queue)
{
    if (!queue_isEmpty(queue)) {
        return (queue->front->data);
    }
    return "NULL";
}

int queue_size(Queue *queue) {
    return queue->size;
}

//inisialisasi
void dArray_init(DynamicArray *darray)
{
    darray->capacity = 2u;
    darray->size = 0u;
    darray->arr = (Queue*) malloc (sizeof(Queue)*2);
}

//cek kosong
bool dArray_isEmpty(DynamicArray *darray)
{
    return (darray->size == 0);
}

//pushback
void dArray_pushBack(DynamicArray *darray, Queue value)
{
    //apabila melebihi kapasitas
    if(darray->size + 1 > darray->capacity)
    {
        unsigned i;
        //menambah kapasitas 2 kali lipat
        darray->capacity *= 2;
        Queue *newArr = (Queue*) malloc(sizeof(Queue)*darray->capacity);
        
        //memindahkan ke array baru
        for(i=0; i<darray->size; i++)
        {
            newArr[i] = darray->arr[i];
        }
        
        //menghapus array lama
        Queue *oldArray = darray->arr;
        darray->arr = newArr;
        free(oldArray);
    }
    //push back
    darray->arr[darray->size++] = value;
}

//hapus belakang
void dArray_popBack(DynamicArray *darray) 
{
    //kalo tidak kosong bisa di kurangi saja sizenya
    if(!dArray_isEmpty(darray))
        darray->size--;
    //kalo kosong skip
    else return;
}

//lihat belakang
Queue dArray_back(DynamicArray *darray)
{
    Queue nol;
    queue_init(&nol);
    //kalo ga kosong bisa diambil
    if (!dArray_isEmpty(darray))
        return darray->arr[darray->size-1];
    //kalo kosong return 0
    else return nol;
}

//lihat depan
Queue dArray_front(DynamicArray *darray)
{
    Queue nol;
    queue_init(&nol);
    //kalo ga kosong
    if (!dArray_isEmpty(darray))
        return darray->arr[0];
    //kalo kosong
    else return nol;
}


//masukkan
void pil1(DynamicArray *darray)
{
    int banyak;
    Queue iniQueue;
    queue_init(&iniQueue);
    
    char kata[25];
    scanf("%d", &banyak);
    while(banyak--)
    {
        scanf("%s", &kata);
        queue_push(&iniQueue, kata);
    }
    dArray_pushBack(darray, iniQueue);
}

//ambil
void pil2(DynamicArray *darray)
{
    Queue iniQueue;
    queue_init(&iniQueue);
    
    int idList, idQue;
    scanf("%d %d", &idList, &idQue);
    
    if(idList > darray->size)
    {
        printf("Hadeh\n");
    }
    else
    {
        int len = darray->arr[idList-1].size;
        if(idQue > len)
        {
            printf("Hadeh\n");
        }
        else
        {
            int i;
            for(i=0; i<len; i++)
            {
                if(i+1 == idQue)
                {
                    printf("%s\n", darray->arr[idList-1].front->data);
                    queue_pop(&darray->arr[idList-1]);
                }
                else
                {
                    queue_push(&iniQueue, darray->arr[idList-1].front->data);
                    queue_pop(&darray->arr[idList-1]);
                }
            }
            while(!queue_isEmpty(&iniQueue))
            {
                queue_push(&darray->arr[idList-1], queue_front(&iniQueue));
                queue_pop(&iniQueue);
            }
        }
    }
}
