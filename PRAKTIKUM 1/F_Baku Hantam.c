//baku hantam
//langkah langkah
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//buat node
typedef struct node {
    int data;
    struct node *next;
} node;

//buat queuenya sendiri
typedef struct queue {
    node   *front, 
           *rear;
    unsigned size;
} Queue;

//fungsi prototipe
void queue_init(Queue *queue);
bool queue_isEmpty(Queue *queue);
void queue_push(Queue *queue, int nilai);
void queue_pop(Queue *queue);
int  queue_front(Queue *queue);
void pil1(Queue *queue);
void pil2(Queue *queue);
void pil3(Queue *queue);


//main
int main()
{
    //inisialisasi
    Queue antrian;
    queue_init(&antrian);
    int banyakKueri, tipe;
    
    //masukkan banyk query
    scanf("%d", &banyakKueri);
    while(banyakKueri--)
    {
        //masukkan tipe
        scanf("%d", &tipe);
        switch(tipe)
        {
            case 1 :
                pil1(&antrian);
                break;
            case 2 :
                pil2(&antrian);
                break;
            case 3 :
                pil3(&antrian);
                break;
            default :
                return 0;
        }
    }
    return 0;
}


//inisialisasi
void queue_init(Queue *queue)
{
    queue->size = 0;
    queue->front = NULL;
    queue->rear = NULL;
}

//cek kosong 
bool queue_isEmpty(Queue *queue) 
{
    //kosong kalau depan dan belakangnya sama2 null
    return (queue->front == NULL && queue->rear == NULL);
}

//masuk dari belakang
void queue_push(Queue *queue, int nilai)
{
    node *newNode = (node*) malloc(sizeof(node));
    if (newNode) 
    {
        //size ditambah
        queue->size++;
        
        //ganti
        newNode->data = nilai;
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
        
        //karena dikurangi sizenya turun
        queue->size--;
    }
}

//akses depan
int queue_front(Queue *queue)
{
    if (!queue_isEmpty(queue)) {
        return (queue->front->data);
    }
    return 0;
}

void pil1(Queue *queue)
{
    //masukkan element yg akan dimasukkan
    int element;
    scanf("%d", &element);
    queue_push(queue, element);
}
void pil2(Queue *queue)
{
    //hapus terdepan
    queue_pop(queue);
}
void pil3(Queue *queue)
{
    //cetak terdepan
    printf("%d\n", queue_front(queue));
}
