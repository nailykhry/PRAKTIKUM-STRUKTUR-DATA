//kembaran kembaran
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define MAX 200


typedef struct node {
    char data[MAX];
    struct node *next;
} node;

/* Struktur ADT Queue */

typedef struct queue {
    node   *front, 
           *rear;
    unsigned size;
} Queue;


typedef struct DataType
{
    int nilai;
    Queue nama;
}DataType;

typedef struct bstnode_t 
{
    DataType key;
    struct bstnode_t 
        *left, *right;
} BSTNode;

typedef struct bst_t 
{
    BSTNode *_root;
    unsigned int _size;
} BST;


void queue_init(Queue *queue);
bool queue_isEmpty(Queue *queue);
void queue_push(Queue *queue, char value[]);
void queue_pop(Queue *queue);
char*  queue_front(Queue *queue);


BSTNode* __bst__createNode(DataType value); 
BSTNode* __bst__insert(BSTNode *root, int value, char nama[]); 
BSTNode* __bst__search(BSTNode *root, int value);
void __bst__inorder(BSTNode *root);


//primary
void bst_init(BST *bst);
bool bst_isEmpty(BST *bst);
bool bst_find(BST *bst, int value, char nama[]);
void bst_insert(BST *bst, int value, char nama[]);
void bst_inorder(BST *bst); 



int main()
{
    BST bst;
    bst_init(&bst);
    
    char daftarNama[100000];
    char tmp[MAX];
    gets(daftarNama);
    
    int len = strlen(daftarNama);
    int i, idx=0, sum=0;
    //olah dan masukkan
    for(i=0; i<len; i++)
    {
        if(i==len-1 && daftarNama[i]!= ' ')
        {
            tmp[idx] = daftarNama[i];
            sum += daftarNama[i];
            idx++;
        }
        if(daftarNama[i]==' ' || i==len-1)
        {
            if(idx) bst_insert(&bst, sum, tmp);
            memset(tmp, 0, strlen(tmp));
            idx = 0;
            sum = 0;
        }
        else
        {
            sum += daftarNama[i];
            tmp[idx] = daftarNama[i];
            idx++;
        }
    }
    bst_inorder(&bst);
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


//BST

BSTNode* __bst__createNode(DataType value) 
{
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, int value, char nama[]) 
{
    if (root == NULL)
    {
        Queue pq;
        queue_init(&pq);
        queue_push(&pq, nama);
        DataType tmp;
        tmp.nilai = value;
        tmp.nama = pq;
        return __bst__createNode(tmp);
    }
        
    
    if (value < root->key.nilai)
        root->left = __bst__insert(root->left, value, nama);
    else if (value > root->key.nilai)
        root->right = __bst__insert(root->right, value, nama);
    
    return root;
}

BSTNode* __bst__search(BSTNode *root, int value) 
{
    while (root != NULL) 
    {
        if (value < root->key.nilai)
            root = root->left;
        else if (value > root->key.nilai)
            root = root->right;
        else
            return root;
    }
    return root;
}


void __bst__inorder(BSTNode *root) 
{
    if (root) 
    {
        __bst__inorder(root->left);
        
        
        printf("Keturunan : %d | ", root->key.nilai);
        printf("Nama : %s", queue_front(&root->key.nama));
        queue_pop(&root->key.nama);
        
        //kalo ga kosong
        if(!queue_isEmpty(&root->key.nama))
        {
            printf(" | Kembaran : ");
            while(!queue_isEmpty(&root->key.nama))
            {
                 printf("%s ", queue_front(&root->key.nama));
                 queue_pop(&root->key.nama);
            }
        }
        
        printf("\n");
        
         
        __bst__inorder(root->right);
    }
}


/*
 * PRIMARY FUNCTION
 */

void bst_init(BST *bst) 
{
    bst->_root = NULL;
    bst->_size = 0u;
}

bool bst_isEmpty(BST *bst) 
{
    return bst->_root == NULL;
}

bool bst_find(BST *bst, int value, char nama[]) 
{
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->key.nilai == value)
    {
        queue_push(&temp->key.nama, nama);
        return true;
    }
    else
        return false;
}

void bst_insert(BST *bst, int value, char nama[]) 
{
    if (!bst_find(bst, value, nama)) 
    {
        bst->_root = __bst__insert(bst->_root, value, nama);
        bst->_size++;
    }
}


/*
 * Binary search tree traversal
 */

void bst_inorder(BST *bst) 
{
    __bst__inorder(bst->_root);
}
