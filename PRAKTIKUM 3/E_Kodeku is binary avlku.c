#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct bstnode_t {
    int key;
    struct bstnode_t \
        *left, *right;
} BSTNode;

typedef struct bst_t {
    BSTNode *_root;
    unsigned int _size;
} BST;

typedef struct AVLNode_t
{
    int data;
    struct AVLNode_t *left,*right;
    int height;
}AVLNode;

typedef struct AVL_t
{
    AVLNode *_root;
    unsigned int _size;
}AVL;


AVLNode* _avl_createNode(int value);
AVLNode* _search(AVLNode *root, int value);
int _getHeight(AVLNode* node);
int _max(int a,int b);
AVLNode* _rightRotate(AVLNode* pivotNode);
AVLNode* _leftRotate(AVLNode* pivotNode);
AVLNode* _leftCaseRotate(AVLNode* node);
AVLNode* _rightCaseRotate(AVLNode* node);
AVLNode* _leftRightCaseRotate(AVLNode* node);
AVLNode* _rightLeftCaseRotate(AVLNode* node);
int _getBalanceFactor(AVLNode* node);
AVLNode* _insert_AVL(AVL *avl,AVLNode* node,int value);
AVLNode* _findMinNode(AVLNode *node);
AVLNode* _remove_AVL(AVLNode* node,int value);
void avl_init(AVL *avl);
bool avl_isEmpty(AVL *avl);
bool avl_find(AVL *avl, int value);
void avl_insert(AVL *avl,int value);
void avl_remove(AVL *avl,int value);
void preorder(AVLNode *root);
void preoderPrint(AVLNode *root);
//bst


BSTNode* __bst__createNode(int value);
BSTNode* __bst__insert(BSTNode *root, int value);
BSTNode* __bst__search(BSTNode *root, int value);

/**
 * PRIMARY FUNCTION
 * ---------------------------
 * Accessible and safe to use.
 */

void bst_init(BST *bst);
bool bst_isEmpty(BST *bst);
bool bst_find(BST *bst, int value);
void bst_insert(BST *bst, int value);
void masuk_avl(BSTNode *root, AVL *avl);

bool genap;
bool ganjil;
bool cek;

int main(){
    AVL avl;
    avl_init(&avl);
    BST bst;
    bst_init(&bst);
    
    char kata[120];
    int pengali, i;
    int panjang, banyak;
    scanf("%d%d", &panjang, &banyak);
    while(banyak--)
    {
        int sum = 0;
        scanf("%s", &kata);
        pengali = kata[panjang] - 48;
        for(i=0; i<panjang; i++)
        {
            if(kata[i]!='X')
            {
                sum += ((int)kata[i]-64);
                bst_insert(&bst, sum*pengali);
                //printf("%d\n", ((int)kata[i]-64)*pengali);
            }
        }
    }
    
    if(bst._root->left != NULL) masuk_avl(bst._root->left, &avl);
    if(bst._root->right != NULL) masuk_avl(bst._root->right, &avl);
    
    
    preorder(avl._root);
    
    if(!cek)
    {
        printf("Input-nya kurang mas/mbak.\n");
    }
    else
    {
        if(genap && ganjil) printf("goatapkil");
        else
        if(genap) printf("mantap");
        else
        if(ganjil) printf("gokil");
    
        preoderPrint(avl._root);
        printf(".avl\n");
    }
    return 0;
}


void masuk_avl(BSTNode *root, AVL *avl)
{
    if(root)
    {
        if(root->left || root->right)
        {
            avl_insert(avl, root->key);
        }
    }
    if(root->left) masuk_avl(root->left, avl); 
    if(root->right) masuk_avl(root->right, avl);
}


AVLNode* _avl_createNode(int value) 
{
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height=1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

AVLNode* _search(AVLNode *root, int value) 
{
    while (root != NULL) {
        if (value < root->data)
            root = root->left;
        else if (value > root->data)
            root = root->right;
        else
            return root;
    }
    return root;
}

int _getHeight(AVLNode* node)
{
    if(node==NULL)
        return 0; 
    return node->height;
}

int _max(int a,int b)
{
    return (a > b)? a : b;
}

AVLNode* _rightRotate(AVLNode* pivotNode) 
{

    AVLNode* newParrent=pivotNode->left;
    pivotNode->left=newParrent->right;
    newParrent->right=pivotNode;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                      _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                       _getHeight(newParrent->right))+1;
    
    return newParrent;
}

AVLNode* _leftRotate(AVLNode* pivotNode) 
{
    AVLNode* newParrent=pivotNode->right;
    pivotNode->right=newParrent->left;
    newParrent->left=pivotNode;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                      _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                       _getHeight(newParrent->right))+1;
    
    return newParrent;
}

AVLNode* _leftCaseRotate(AVLNode* node)
{
    return _rightRotate(node);
}

AVLNode* _rightCaseRotate(AVLNode* node)
{
    return _leftRotate(node);
}

AVLNode* _leftRightCaseRotate(AVLNode* node)
{
    node->left=_leftRotate(node->left);
    return _rightRotate(node);
}

AVLNode* _rightLeftCaseRotate(AVLNode* node)
{
    node->right=_rightRotate(node->right);
    return _leftRotate(node);
}

int _getBalanceFactor(AVLNode* node)
{
    if(node==NULL)
        return 0;
    return _getHeight(node->left)-_getHeight(node->right);
}

AVLNode* _insert_AVL(AVL *avl,AVLNode* node,int value) 
{
    
    if(node==NULL) // udah mencapai leaf
        return _avl_createNode(value);
    if(value < node->data)
        node->left = _insert_AVL(avl,node->left,value);
    else if(value > node->data)
        node->right = _insert_AVL(avl,node->right,value);
    
    node->height= 1 + _max(_getHeight(node->left),_getHeight(node->right)); 

    int balanceFactor=_getBalanceFactor(node);
    
    if(balanceFactor > 1 && value < node->left->data) // skewed kiri (left-left case)
        return _leftCaseRotate(node);
    if(balanceFactor > 1 && value > node->left->data) // 
        return _leftRightCaseRotate(node);
    if(balanceFactor < -1 && value > node->right->data)
        return _rightCaseRotate(node);
    if(balanceFactor < -1 && value < node->right->data)
        return _rightLeftCaseRotate(node);
    
    return node;
}

AVLNode* _findMinNode(AVLNode *node) 
{
    AVLNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    return currNode;
}

AVLNode* _remove_AVL(AVLNode* node,int value)
{
    if(node==NULL)
        return node;
    if(value > node->data)
        node->right=_remove_AVL(node->right,value);
    else if(value < node->data)
        node->left=_remove_AVL(node->left,value);
    else{
        AVLNode *temp;
        if((node->left==NULL)||(node->right==NULL)){
            temp=NULL;
            if(node->left==NULL) temp=node->right;  
            else if(node->right==NULL) temp=node->left;
            
            if(temp==NULL){
                temp=node;
                node=NULL;
            }
            else
                *node=*temp;   
            
            free(temp);
        }
        else{
            temp = _findMinNode(node->right);
            node->data=temp->data;
            node->right=_remove_AVL(node->right,temp->data);
        }    
    }

    if(node==NULL) return node;
    
    node->height=_max(_getHeight(node->left),_getHeight(node->right))+1;

    int balanceFactor= _getBalanceFactor(node);
    
    if(balanceFactor>1 && _getBalanceFactor(node->left)>=0) 
        return _leftCaseRotate(node);

    if(balanceFactor>1 && _getBalanceFactor(node->left)<0) 
        return _leftRightCaseRotate(node);
  
    if(balanceFactor < -1 && _getBalanceFactor(node->right)<=0) 
        return _rightCaseRotate(node);

    if(balanceFactor < -1 && _getBalanceFactor(node->right)>0) 
        return _rightLeftCaseRotate(node);
    
    return node;
}

void avl_init(AVL *avl) 
{
    avl->_root = NULL;
    avl->_size = 0u;
}

bool avl_isEmpty(AVL *avl) 
{
    return avl->_root == NULL;
}

bool avl_find(AVL *avl, int value) 
{
    AVLNode *temp = _search(avl->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->data == value)
        return true;
    else
        return false;
}

void avl_insert(AVL *avl,int value)
{
    if(!avl_find(avl,value)){
        avl->_root=_insert_AVL(avl,avl->_root,value);
        avl->_size++;
    }

}

void avl_remove(AVL *avl,int value)
{
    if(avl_find(avl,value)){
        avl->_root=_remove_AVL(avl->_root,value);
        avl->_size--;
    }

}

void preorder(AVLNode *root) 
{
    if (root) {
        preorder(root->left);
        if(root->left == NULL && root->right == NULL)
        {
            cek = true;
            if(root->data%2) ganjil = true;
            else genap = true;
        }
        preorder(root->right);
    }
}

void preoderPrint(AVLNode *root)
{
    if (root) {
        preoderPrint(root->left);
        if(root->left == NULL && root->right == NULL)
        {
            printf("%d", root->data);
        }
        preoderPrint(root->right);
    }
}


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
