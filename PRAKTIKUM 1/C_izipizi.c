//ambil kambing paling gemuk

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include  <stdbool.h>


typedef struct node {
    int data;
    struct node *next;
} PQueueNode;

typedef struct pqueue_t {
    PQueueNode *top;
    unsigned size;
} PriorityQueue;


void pq_init(PriorityQueue *pqueue);
bool pq_isEmpty(PriorityQueue *pqueue);
void pq_push(PriorityQueue *pqueue, int value);
int  pq_top(PriorityQueue *pqueue);

int main()
{
    //inisialisasi & deklarasi
    PriorityQueue pqKu;
    pq_init(&pqKu);
    int banyakKambing, beratKambing;
    
    //masukkan ke pq
    scanf("%d", &banyakKambing);
    while(banyakKambing--)
    {
        scanf("%d", &beratKambing);
        pq_push(&pqKu, beratKambing);
    }
    
    //tampilkan
    if(pq_isEmpty(&pqKu)) 
        printf("Oiya lupa gapunya kambing, hehe\n");
    else
        printf("%d\n", pq_top(&pqKu));
    return 0;
}

//inisialisasi
void pq_init(PriorityQueue *pqueue)
{
    pqueue->top = NULL;
    pqueue->size = 0;
}

//cek kosong
bool pq_isEmpty(PriorityQueue *pqueue) {
    return (pqueue->top == NULL);
}

//palingdepan
int pq_top(PriorityQueue *pqueue) {
    if (!pq_isEmpty(pqueue))
        return pqueue->top->data;
    else return 0;
}

void pq_push(PriorityQueue *pqueue, int value)
{
    PQueueNode *temp = pqueue->top;
    PQueueNode *newNode = (PQueueNode*) malloc (sizeof(PQueueNode));
    newNode->data = value;
    newNode->next = NULL;
    
    //kalo kosong langsung masuk
    if (pq_isEmpty(pqueue)) 
    {
        pqueue->top = newNode;
        return;
    }
    
    //kalo lebih bakal jadi didepan
    if (value > pqueue->top->data) 
    {
        newNode->next = pqueue->top;
        pqueue->top = newNode;
    }
    else 
    {
        while ( temp->next != NULL && temp->next->data > value)
            temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

