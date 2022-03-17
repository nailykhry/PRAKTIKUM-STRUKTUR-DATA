//ambil maks jagung yg bisa dimakan
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include  <stdbool.h>

typedef struct darray
{
    int *arr;
    unsigned size, capacity;
}DynamicArray;

void dArray_init(DynamicArray*);
bool dArray_isEmpty(DynamicArray*);
void dArray_pushBack(DynamicArray*, int);
int  dArray_back(DynamicArray*);
int  dArray_front(DynamicArray*);


int maksJagung(DynamicArray *, DynamicArray *, int);
int max(int, int);

int main()
{
    
    int kueri;
    scanf("%d", &kueri);
    while(kueri--)
    {
        int kapasitas, jA, jB, biji, tmp;
        DynamicArray jagungA, jagungB, ganjil, genap;
        dArray_init(&jagungA);
        dArray_init(&jagungB);
        dArray_init(&genap);
        dArray_init(&ganjil);
    
        //banyak biji &kapasitas
        scanf("%d %d %d", &kapasitas, &jA, &jB);
    
        //masuk data
        tmp=0;
        dArray_pushBack(&jagungA, tmp);
        while(jA--)
         {
            scanf("%d", &biji);
            if(biji%2==0) dArray_pushBack(&genap, biji);
            tmp += biji;
            if(tmp<=kapasitas) dArray_pushBack(&jagungA, tmp);
        }
      
        tmp=0; 
        dArray_pushBack(&jagungB, tmp); 
        while(jB--)
        {
            scanf("%d", &biji);
            if(biji%2==1) dArray_pushBack(&ganjil, biji);
            tmp += biji;
            if(tmp<=kapasitas) dArray_pushBack(&jagungB, tmp);
        }
        
        int output = maksJagung(&jagungA, &jagungB, kapasitas);
        
        //output
        printf("%d Jahong\n", output);
        if(output) // kalau selain 0
        {
            if(output%2==0 && dArray_isEmpty(&genap)) //genap tp kosong
            {
                printf("Gak ada nih!\n");
            }
            else
            if(output%2==1 && dArray_isEmpty(&ganjil)) //ganjil kosong
            {
                printf("Gak ada nih!\n");
            }
            else
            if(output%2==0)                                //genap
            {
                printf("NUM =>");
                int i;
                int lenGenap = genap.size;
                for(i=0; i<lenGenap; i++)
                {
                    printf("%d ", genap.arr[i]);
                }
                printf("\n");
            }
            else                                        //ganjil
            {
                printf("NUM =>");
                int i;
                int lenGanjil = ganjil.size;
                for(i=0; i<lenGanjil; i++)
                {
                    printf("%d ", ganjil.arr[i]);
                }
                printf("\n");
            }
        }
        else printf("Keciaaan :<\n"); //jehongnya 0 
    }  
    
    return 0;
}

//inisialisasi
void dArray_init(DynamicArray *darray)
{
    darray->capacity = 2u;
    darray->size = 0u;
    darray->arr = (int*) malloc (sizeof(int)*2);
}

//cek kosong
bool dArray_isEmpty(DynamicArray *darray)
{
    return (darray->size == 0);
}

//pushback
void dArray_pushBack(DynamicArray *darray, int value)
{
    //apabila melebihi kapasitas
    if(darray->size + 1 > darray->capacity)
    {
        unsigned i;
        //menambah kapasitas 2 kali lipat
        darray->capacity *= 2;
        int *newArr = (int*) malloc(sizeof(int)*darray->capacity);
        
        //memindahkan ke array baru
        for(i=0; i<darray->size; i++)
        {
            newArr[i] = darray->arr[i];
        }
        
        //menghapus array lama
        int *oldArray = darray->arr;
        darray->arr = newArr;
        free(oldArray);
    }
    //push back
    darray->arr[darray->size++] = value;
}


//lihat belakang
int dArray_back(DynamicArray *darray)
{
    //kalo ga kosong bisa diambil
    if (!dArray_isEmpty(darray))
        return darray->arr[darray->size-1];
    //kalo kosong return 0
    else return 0;
}

//lihat depan
int dArray_front(DynamicArray *darray)
{
    //kalo ga kosong
    if (!dArray_isEmpty(darray))
        return darray->arr[0];
    //kalo kosong
    else return 0;
}


int max(int a, int b)
{
    if(a>=b) return a;
    return b;
}


int maksJagung(DynamicArray *A, DynamicArray *B, int kapasitas)
{
    int i, j;
    int output = 0;
    int lenA = A->size;
    int lenB = B->size;
    
    //bf
    for(i=lenA-1; i>=0; i--)
    {
        for(j=lenB-1; j>=0; j--)
        {
            if(A->arr[i]+B->arr[j] <= kapasitas)
            {
                output = max(output, i+j);
            }
        }
    }
    
    return output;
}
