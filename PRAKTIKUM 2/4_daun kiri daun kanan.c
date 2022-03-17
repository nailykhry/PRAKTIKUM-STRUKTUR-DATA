//print bedain kiri kanan
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


typedef struct bstnode_t {
    int key;
    struct bstnode_t 
        *left, *right;
} BSTNode;

typedef struct bst_t {
    BSTNode *_root;
    unsigned int _size;
} BST;



BSTNode* __bst__createNode(int value) {
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, int value) {
    if (root == NULL) 
        return __bst__createNode(value);

    if (value < root->key)
        root->left = __bst__insert(root->left, value);
    else if (value > root->key)
        root->right = __bst__insert(root->right, value);
    
    return root;
}

BSTNode* __bst__search(BSTNode *root, int value) {
    while (root != NULL) {
        if (value < root->key)
            root = root->left;
        else if (value > root->key)
            root = root->right;
        else
            return root;
    }
    return root;
}

BSTNode* __bst__findMinNode(BSTNode *node) {
    BSTNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    
    return currNode;
}

BSTNode* __bst__remove(BSTNode *root, int value) {
    if (root == NULL) return NULL;

    if (value > root->key) 
        root->right = __bst__remove(root->right, value);
    else if (value < root->key) 
        root->left = __bst__remove(root->left, value);
    else {
        
        if (root->left == NULL) {
            BSTNode *rightChild = root->right;
            free(root);
            return rightChild;
        }
        else if (root->right == NULL) {
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

void __bst__inorder(BSTNode *root) {
    if (root) {
        __bst__inorder(root->left);
        printf("%d ", root->key);
        __bst__inorder(root->right);
    }
}

void __bst__postorder1(BSTNode *root) 
{
    if (root) 
    {
        __bst__postorder1(root->left);
        __bst__postorder1(root->right);
        printf("%d ", root->key);
    }
}

void __bst__postorder2(BSTNode *root) 
{
    if (root) 
    {
        __bst__postorder2(root->left);
        __bst__postorder2(root->right);
        printf("%d ", root->key);
    }
}

void __bst__preorder(BSTNode *root) {
    if (root) {
        printf("%d ", root->key);
        __bst__preorder(root->left);
        __bst__preorder(root->right);
    }
}

/**
 * PRIMARY FUNCTION
 * ---------------------------
 * Accessible and safe to use.
 */

void bst_init(BST *bst) {
    bst->_root = NULL;
    bst->_size = 0u;
}

bool bst_isEmpty(BST *bst) {
    return bst->_root == NULL;
}

bool bst_find(BST *bst, int value) {
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->key == value)
        return true;
    else
        return false;
}

void bst_insert(BST *bst, int value) {
    if (!bst_find(bst, value)) {
        bst->_root = __bst__insert(bst->_root, value);
        bst->_size++;
    }
}

void bst_remove(BST *bst, int value) {
    if (bst_find(bst, value)) {
        bst->_root = __bst__remove(bst->_root, value);
        bst->_size--;
    }
}

/**
 * Binary search tree traversal
 * - Inorder
 * - Postorder
 * - Preorder
 */

void bst_inorder(BST *bst) {
    __bst__inorder(bst->_root);
}


void bst_postorder(BST *bst) 
{
    
    
    if(bst->_root == NULL) 
        printf("Isi dulu dong @_@\n");
        
    else
    if(bst->_root->left == NULL && bst->_root->right == NULL) 
        printf("Belum tumbuh nih %dnya :(\n", bst->_root->key);
        
    else
    {
        //kiri
        printf("     left : ");
        if(bst->_root->left == NULL) 
            printf("Kok gk tumbuh yah :<\n");
        else 
        {
            __bst__postorder1(bst->_root->left);
            printf("\n");
        }
        
        
        //tengah
        printf("root: %d\n", bst->_root->key);
    
        
        //kanan    
        printf("     right: ");
        if(bst->_root->right == NULL) 
            printf("Kok gk tumbuh yah :<\n");
        else
        {
            __bst__postorder2(bst->_root->right);
            printf("\n");
        }
    }
}

void bst_preorder(BST *bst) {
    __bst__preorder(bst->_root);
}
 
int main()
{
    BST bst;
    bst_init(&bst);
    
    int n, isi, garis=0;
    char perintah[15];
    scanf("%d", &n);
    while(n--)
    {
        scanf(" %s", &perintah);
        if(!strcmp(perintah, "isi"))
        {
            scanf("%d", &isi);
            if(isi>0) bst_insert(&bst, isi);
        }
        else
        {
            scanf(" %s", &perintah);
            if(garis) printf("==============================\n");
            bst_postorder(&bst);
            garis++;
        }
    }
    
    return 0;
}
