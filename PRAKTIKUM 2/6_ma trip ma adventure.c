//shortest path ke leaf
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


typedef struct bstnode_t {
    unsigned long long key;
    unsigned long long weight;
    unsigned long long jalan;
    struct bstnode_t 
        *left, *right;
} BSTNode;

typedef struct bst_t {
    BSTNode *_root;
    unsigned int _size;
} BST;


BSTNode* __bst__createNode(unsigned long long value, unsigned long long berat); 
BSTNode* __bst__insert(BSTNode *root, unsigned long long value, unsigned long long berat); 
BSTNode* __bst__search(BSTNode *root, unsigned long long value);
void __bst__postorder(BSTNode *root);

//primary
void bst_init(BST *bst);
bool bst_isEmpty(BST *bst);
bool bst_find(BST *bst, unsigned long long value);
void bst_insert(BST *bst, unsigned long long value, unsigned long long berat);
void bst_postorder(BST *bst); 

unsigned long long min(unsigned long long, unsigned long long);
void output(BST *bst, unsigned long long cek);

int main()
{
    BST bst;
    bst_init(&bst);
    
    unsigned long long N, awal, nd, we;
    scanf("%llu %llu", &N, &awal);
    bst_insert(&bst, awal, 0);
    N = N-1;
    while(N--)
    {
        scanf("%llu %llu", &nd, &we);
        bst_insert(&bst, nd, we);
    }

    bst_postorder(&bst);
    unsigned long long kueri, cek;
    scanf("%llu", &kueri);
    while(kueri--)
    {
        scanf("%llu", &cek);
        output(&bst, cek);
    } 
    printf("\n");
    return 0;
}


void output(BST *bst, unsigned long long cek)
{
    bst_find(bst, cek);
}


BSTNode* __bst__createNode(unsigned long long value, unsigned long long berat) 
{
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->weight = berat;
    newNode->jalan = 10e18;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, unsigned long long value, unsigned long long berat) 
{
    if (root == NULL) 
        return __bst__createNode(value, berat);

    if (value < root->key)
        root->left = __bst__insert(root->left, value, berat);
    else if (value > root->key)
        root->right = __bst__insert(root->right, value, berat);
    
    return root;
}

BSTNode* __bst__search(BSTNode *root, unsigned long long value) 
{
    //unsigned long long ans = 10e18;
    while (root != NULL) 
    {
        if (value < root->key)
        {
            root = root->left;
        }
        else if (value > root->key)
        {
            root = root->right;
        }
        else
        {
            return root;
        }
    }
    return root;
}



void __bst__postorder(BSTNode *root) 
{
    if (root) 
    {
        __bst__postorder(root->left);
        __bst__postorder(root->right);
        
        //dia leaf
        if(root->left == NULL && root->right==NULL)
        {
            root->jalan = 0;
        }
        else
        {
            //node itu sendiri pake anaknya
            if(root->left != NULL)
            {
                root->jalan = min(root->jalan, root->left->weight + root->left->jalan);
            }
            if(root->right != NULL)
            {
                root->jalan = min(root->jalan, root->right->weight + root->right->jalan);
            }
            
            //pake parent 1
            if(root->left != NULL)
            {
                root->left->jalan = min(root->left->jalan, root->jalan + root->left->weight);
            }
            if(root->right != NULL)
            {
                root->right->jalan = min(root->right->jalan, root->jalan + root->right->weight);
            }
            
            //pake parent 2
            if(root->left != NULL)
            {
                if(root->left->left != NULL)
                {
                    root->left->left->jalan = min(root->left->left->jalan, 
                                            root->jalan + root->left->weight + root->left->left->weight);
                }
                if(root->left->right != NULL)
                {
                    root->left->right->jalan = min(root->left->right->jalan, 
                                            root->jalan + root->left->weight + root->left->right->weight);
                }
            }
            if(root->right != NULL)
            {
                if(root->right->left != NULL)
                {
                    root->right->left->jalan = min(root->right->left->jalan, 
                                            root->jalan + root->right->weight + root->right->left->weight);
                }
                if(root->right->right != NULL)
                {
                    root->right->right->jalan = min(root->right->right->jalan, 
                                            root->jalan + root->right->weight + root->right->right->weight);
                }
            }
        }
    }
}

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
    {
        printf("%llu ", temp->jalan);
        return true;
    }
    else
    {
        return false;
    }
}

void bst_insert(BST *bst, unsigned long long  value, unsigned long long berat) 
{
    if (!bst_find(bst, value)) {
        bst->_root = __bst__insert(bst->_root, value, berat);
        bst->_size++;
    }
}


/**
 * Binary search tree traversal
 * - Inorder
 * - Postorder
 * - Preorder
 */

void bst_postorder(BST *bst) 
{
    __bst__postorder(bst->_root);
}


unsigned long long min(unsigned long long a, unsigned long long b)
{
    if(a<b) return a;
    return b;
}
