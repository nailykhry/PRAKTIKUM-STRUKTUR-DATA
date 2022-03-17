#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include  <stdbool.h>

/* Struktur Node */

typedef struct node 
{
    int data;
    struct node *next;
} StackNode;

/* Struktur ADT Stack */

typedef struct stack_t 
{
    StackNode *top;
    unsigned size;
} Stack;

//fungsi prototype

void stack_init(Stack *);
bool stack_isEmpty(Stack *);
void stack_push(Stack *, int );
void stack_pop(Stack *);
int stack_top(Stack *);
int cek_ketinggian(Stack *, Stack *, Stack *);
int min(int, int);

int main()
{
    //iniasialiasi & deklarasi
    int arr1[100005], arr2[100005], arr3[100005];
    int n1, n2, n3, i;
    int ketebalanBuku;
    Stack buku1, buku2, buku3;
    stack_init(&buku1);
    stack_init(&buku2);
    stack_init(&buku3);
    
    //banyak buku
    scanf("%d %d %d", &n1, &n2, &n3);
    
    //ketebalan buku satu satu pertama 
    for(i=0; i<n1; i++)
    {
        scanf("%d", &ketebalanBuku);
        arr1[i] = ketebalanBuku;
    }
    
    //ketebalan buku satu satu pertama 
    for(i=0; i<n2; i++)
    {
        scanf("%d", &ketebalanBuku);
        arr2[i] = ketebalanBuku;
    }
    
    //ketebalan buku satu satu pertama
    for(i=0; i<n3; i++)
    {
        scanf("%d", &ketebalanBuku);
        arr3[i] = ketebalanBuku;
    }
    
    //panggil terbalik untuk nge push
    int tmp = 0;
    for(i=n1-1; i>=0; i--)
    {
        tmp += arr1[i];
        stack_push(&buku1, tmp);
    }
    
    //dua
    tmp = 0;
    for(i=n2-1; i>=0; i--)
    {
        tmp += arr2[i];
        stack_push(&buku2, tmp);
    }
    
    //tiga
    tmp = 0;
    for(i=n3-1; i>=0; i--)
    {
        tmp += arr3[i];
        stack_push(&buku3, tmp);
    }
    
    //panggil dan keluarkan
    int output = cek_ketinggian(&buku1, &buku2, &buku3);
    printf("%d\n", output);
    
    return 0;
}
//inisialisasi
void stack_init(Stack *stack) 
{
    stack->size = 0;
    stack->top = NULL;
}

//cek kosong
bool stack_isEmpty(Stack *stack) 
{
    //cek paling atas
    return (stack->top == NULL);
}

//nambahin elemen
void stack_push(Stack *stack, int nilai) 
{
    //buat node baru
    StackNode *newNode = (StackNode*) malloc(sizeof(StackNode));
    if (newNode) 
    {
        //ukurannya ditambahin
        stack->size++;
        //simpan sementara
        newNode->data = nilai;
        
        //kalau kosong maka selanjutnya masih null
        if (stack_isEmpty(stack)) newNode->next = NULL;
        //kalau tidak ubah top jadi next dan ynag baru jadi top
        else newNode->next = stack->top;

        stack->top = newNode;
    }
}

//hapus top
void stack_pop(Stack *stack) 
{
    //gabole kosong
    if (!stack_isEmpty(stack)) 
    {
        //buat top menjadi elemen selanjutnya dan hapus top
        StackNode *temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
        stack->size--;
    }
}

//akses top
int stack_top(Stack *stack) 
{
    //!kosong return top. koosng return 0
    if (!stack_isEmpty(stack)) 
        return stack->top->data;
    return 0;
}


int cek_ketinggian(Stack *s1, Stack *s2, Stack *s3)
{
    //disini intinya akan cek selama tinggi belum sama semua
    //selama belum sama nanti akan yg min. kalau belum sampai ke min bakal di pop
    int min_tmp;
    int top1 = stack_top(s1);
    int top2 = stack_top(s2);
    int top3 = stack_top(s3);
    while(!(top1==top2 && top2==top3 &&top1==top3))
    {
        min_tmp = min(top1, min(top2, top3));
        while(top1 > min_tmp)
        {
            stack_pop(s1);
            top1 = stack_top(s1);
        }
        while(top2 > min_tmp)
        {
            stack_pop(s2);
            top2 = stack_top(s2);
        }
        while(top3 > min_tmp)
        {
            stack_pop(s3);
            top3 = stack_top(s3);
        }
    }
    return top1;
}

int min(int a, int b)
{
    if(a < b) return a;
    return b;
}
