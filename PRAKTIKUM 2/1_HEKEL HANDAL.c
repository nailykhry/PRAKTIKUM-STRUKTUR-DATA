//jumlah perlevel
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


typedef struct darray
{
    unsigned long long *arr;
    unsigned size, capacity;
}DynamicArray;

typedef struct DataType
{
    unsigned long long data;
    unsigned long long level;
}DataType;



typedef struct bstnode_t 
{
    unsigned long long key;
    struct bstnode_t 
        *left, *right;
} BSTNode;

typedef struct bst_t 
{
    BSTNode *_root;
    unsigned long long _size;
} BST;


void dArray_init(DynamicArray*);
bool dArray_isEmpty(DynamicArray*);
void dArray_pushBack(DynamicArray*, unsigned long long);
void dArray_setAt(DynamicArray*, unsigned, unsigned long long);
unsigned long long  dArray_getAt(DynamicArray*, unsigned);

BSTNode* __bst__createNode(unsigned long long value,  DynamicArray* darray); 
BSTNode* __bst__insert(BSTNode *root, unsigned long long value, DynamicArray*); 
BSTNode* __bst__search(BSTNode *root, unsigned long long value);


//primary
void bst_init(BST *bst);
bool bst_isEmpty(BST *bst);
bool bst_find(BST *bst, unsigned long long value);
void bst_insert(BST *bst, unsigned long long value, DynamicArray*);


unsigned long long lvl;
unsigned long long maxLevel ;

int main()
{
    unsigned long long query, format;
    unsigned long long angka;
    //inisialisasi
    BST bst;
    bst_init(&bst);
    
    DynamicArray darray;
    dArray_init(&darray);
    
    scanf("%llu", &query);
    while(query--)
    {
        scanf("%llu %llu", &format, &angka);
        //masukkan
        if(format==1)
        {
            lvl = 0;
            bst_insert(&bst, angka, &darray);
        }
        //cari jumlah di level
        else
        {
        	//kalo lebih
            if(maxLevel < angka)
            {
                printf("GG EZ\n");
            }
            else
            {
                unsigned long long sum = dArray_getAt(&darray, angka);
                printf("Level %llu: %llu\n", angka, sum);
            }
        }
    }
    
    return 0;
}


//inisialisasi
void dArray_init(DynamicArray *darray)
{
    darray->capacity = 2u;
    darray->size = 0u;
    darray->arr = (unsigned long long*) malloc (sizeof(unsigned long long)*2);
}

//cek kosong
bool dArray_isEmpty(DynamicArray *darray)
{
    return (darray->size == 0);
}

//pushback
void dArray_pushBack(DynamicArray *darray, unsigned long long value)
{
    //apabila melebihi kapasitas
    if(darray->size + 1 > darray->capacity)
    {
        unsigned i;
        //menambah kapasitas 2 kali lipat
        darray->capacity *= 2;
        unsigned long long *newArr = (unsigned long long*) malloc(sizeof(unsigned long long)*darray->capacity);
        
        //memindahkan ke array baru
        for(i=0; i<darray->size; i++)
        {
            newArr[i] = darray->arr[i];
        }
        
        //menghapus array lama
        unsigned long long *oldArray = darray->arr;
        darray->arr = newArr;
        free(oldArray);
    }
    //push back
    darray->arr[darray->size++] = value;
}


//ambil index ke - x
unsigned long long dArray_getAt(DynamicArray *darray, unsigned index)
{
    //gaboleh kosong
    if (!dArray_isEmpty(darray)) 
    {    
        //index lebih ambil yang terbelakang
        if (index >= darray->size)
            return darray->arr[darray->size-1];
        //ambil indexnya sendiri
        else
            return darray->arr[index];
    }
    else return 0;
}

//replace
void dArray_setAt(
    DynamicArray *darray, unsigned index, unsigned long long value)
{
    //kalo ga kosong
    if (!dArray_isEmpty(darray)) 
    {
        //index lebih dari sama dengan size
        if (index >= darray->size)
            darray->arr[darray->size-1] = value;
            
        //index kurang dari size
        else
            darray->arr[index] = value;
    }
}


BSTNode* __bst__createNode(unsigned long long value,  DynamicArray* darray) 
{

    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    
    //masih kosong/ belum ada
    if(lvl > maxLevel || dArray_isEmpty(darray))
    {
        maxLevel  = lvl;
        dArray_pushBack(darray, value);
    }
    else
    {
        unsigned long long tmp = dArray_getAt(darray, lvl);
        dArray_setAt(darray, lvl, tmp+value);
    }
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, unsigned long long value, DynamicArray* darray) 
{
    if (root == NULL) 
    {
        return __bst__createNode(value, darray);
    }

    if (value < root->key)
    {
        lvl++;
        root->left = __bst__insert(root->left, value, darray);
    }
    else if (value > root->key)
    {
        lvl++;
        root->right = __bst__insert(root->right, value, darray);
    }
    
    return root;
}

BSTNode* __bst__search(BSTNode *root, unsigned long long value) 
{
    while (root != NULL) 
    {
        if (value < root->key)
            root = root->left;
        else if (value > root->key)
            root = root->right;
        else
            return root;
    }
    return root;
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

bool bst_find(BST *bst, unsigned long long value) 
{
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->key == value)
        return true;
    else
        return false;
}

void bst_insert(BST *bst, unsigned long long value, DynamicArray *darray) 
{
    if (!bst_find(bst, value)) 
    {
        bst->_root = __bst__insert(bst->_root, value, darray);
        bst->_size++;
    }
}
