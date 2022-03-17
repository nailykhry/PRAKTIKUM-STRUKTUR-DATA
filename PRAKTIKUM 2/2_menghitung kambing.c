//hitung 5 kemungkinan 3 terdekat yg jumlah sama
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct bstnode_t 
{
    int key;
    struct bstnode_t 
        *left, *right;
} BSTNode;

typedef struct bst_t 
{
    BSTNode *_root;
    unsigned int _size;
} BST;


BSTNode* __bst__createNode(int value); 
BSTNode* __bst__insert(BSTNode *root, int value); 
BSTNode* __bst__search(BSTNode *root, int value);
BSTNode* __bst__findMinNode(BSTNode *node);
BSTNode* __bst__remove(BSTNode *root, int value);

//primary
void bst_init(BST *bst);
bool bst_isEmpty(BST *bst);
bool bst_find(BST *bst, int value);
void bst_insert(BST *bst, int value);
void bst_remove(BST *bst, int value); 
void masuk(BST *bst, int);
void cari(BSTNode *root, int);

int tanda = 0;

int main()
{
	//inisialisasi
    BST kelompok;
    bst_init(&kelompok);
    
    //masukkan
    int jumlahKelompok;
    scanf("%d", &jumlahKelompok);
    masuk(&kelompok, jumlahKelompok);
    
    //untuk cek
    int cek;
    scanf("%d", &cek);
    cari(kelompok._root, cek);
    if(!tanda) printf("HAiiyyaAhh SalAhh\n");
    return 0;
}


//memasukka
void masuk(BST *bst, int n)
{
    int kambing;
    while(n--)
    {
        scanf("%d", &kambing);
        bst_insert(bst, kambing);
    }
}

//cek kalo adaa yg jumlah sama
void cari(BSTNode *root, int cek)
{
	//jumlahan maks 3
    int tmp = 0;
    
    if(root != NULL)
    {
        //printf("1");
        tmp = 0;
        //segitiga
        tmp += root->key;
        if(root->left != NULL) tmp += root->left->key;
        if(root->right != NULL) tmp += root->right->key;
        
        if(cek==tmp)
        {
            tanda = 1;
            printf("ManTap\n");
            return;
        }
        
        //printf("2");
        tmp = 0;
        //kiri kiri
        tmp += root->key;
        if(root->left != NULL) tmp += root->left->key;
        if(root->left != NULL && root->left->left != NULL) tmp += root->left->left->key;
        
        if(cek==tmp)
        {
            tanda = 1;
            printf("ManTap\n");
            return;
        }
        
        
        //printf("3");
        tmp = 0;
        //kiri kanan
        tmp += root->key;
        if(root->left != NULL) tmp += root->left->key;
        if(root->left !=NULL && root->left->right != NULL) tmp += root->left->right->key;
        
        if(cek==tmp)
        {
            tanda = 1;
            printf("ManTap\n");
            return;
        }
        
        
        //printf("4");
        tmp = 0;
        //kanan kiri
        tmp += root->key;
        if(root->right != NULL) tmp += root->right->key;
        if(root->right != NULL && root->right->left != NULL) tmp += root->right->left->key;
        
        if(cek==tmp)
        {
            tanda = 1;
            printf("ManTap\n");
            return;
        }
        
        //printf("5");
        tmp = 0;
        //kanan kanan
        tmp += root->key;
        if(root->right != NULL) tmp += root->right->key;
        if(root->right != NULL && root->right->right != NULL) tmp += root->right->right->key;
        
        if(cek==tmp)
        {
            tanda = 1;
            printf("ManTap\n");
            return;
        }
        
    }
    
    if(root->left != NULL) cari(root->left, cek);
    if(root->right != NULL) cari(root->right, cek);
    
}

//fungsi fungsi template

BSTNode* __bst__createNode(int value) 
{
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, int value) 
{
    if (root == NULL)
    { 
        return __bst__createNode(value);
    }

    if (value < root->key)
    {
        root->left = __bst__insert(root->left, value);
    }
    else if (value > root->key)
    {
        root->right = __bst__insert(root->right, value);
    }
    return root;
}

BSTNode* __bst__search(BSTNode *root, int value) 
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

BSTNode* __bst__findMinNode(BSTNode *node) 
{
    BSTNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    
    return currNode;
}

BSTNode* __bst__remove(BSTNode *root, int value) 
{
    if (root == NULL) return NULL;

    if (value > root->key) 
        root->right = __bst__remove(root->right, value);
    else if (value < root->key) 
        root->left = __bst__remove(root->left, value);
    else 
    {
        
        if (root->left == NULL) 
        {
            BSTNode *rightChild = root->right;
            free(root);
            return rightChild;
        }
        else if (root->right == NULL) 
        {
            BSTNode *leftChild = root->left;
            free(root);
            return leftChild;
        }

        BSTNode *temp = __bst__findMinNode(root->right);
        root->key     = temp->key;
        root->right   = __bst__remove(root->right, temp->key);
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

bool bst_find(BST *bst, int value) 
{
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->key == value)
        return true;
    else
        return false;
}

void bst_insert(BST *bst, int value) 
{
    if (!bst_find(bst, value)) 
    {
        bst->_root = __bst__insert(bst->_root, value);
        bst->_size++;
    }
}

void bst_remove(BST *bst, int value) 
{
    if (bst_find(bst, value)) 
    {
        bst->_root = __bst__remove(bst->_root, value);
        bst->_size--;
    }
}
