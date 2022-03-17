#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

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
int _min(int a,int b);
AVLNode* _rightRotate(AVLNode* pivotNode);
AVLNode* _leftRotate(AVLNode* pivotNode);
AVLNode* _leftCaseRotate(AVLNode* node);
AVLNode* _rightCaseRotate(AVLNode* node);
AVLNode* _leftRightCaseRotate(AVLNode* node);
AVLNode* _rightLeftCaseRotate(AVLNode* node);
int _getBalanceFactor(AVLNode* node);
AVLNode* _insert_AVL(AVL *avl,AVLNode* node,int value);
AVLNode* _findMinNode(AVLNode *node);
void avl_init(AVL *avl);
bool avl_isEmpty(AVL *avl);
bool avl_find(AVL *avl, int value);
void avl_insert(AVL *avl,int value);
void preorder(AVLNode *root);
void olah_kiri(AVLNode *root, AVL *kanan);
unsigned long long sum;

int main(){
    
    //buat diagonalnya
    AVL kanan, kiri;
    avl_init(&kanan);
    avl_init(&kiri);
    
    
    int ukuran, bishop, x, y;
    scanf("%d%d", &ukuran, &bishop);
    
    while(bishop--)
    {
        scanf("%d %d", &x, &y);
        //buat diagonal kanan dulss
        if(!avl_find(&kanan, x-y))
        {
            avl_insert(&kanan, x-y);
            sum += (ukuran-abs(x-y)); 
        }
        
        //buat diagonal kiri yeee
        //kaya cari ujungnya gitu loh
        int tmp = _min(x-1, ukuran-y);
        int tmp_x = x-tmp;
        int tmp_y = y+tmp;
        int beda = tmp_x - tmp_y;
        avl_insert(&kiri, beda);
    }
    
    //cari potongan dan tambahan sum
    olah_kiri(kiri._root, &kanan);
    
    printf("%llu", sum);
    return 0;
}



void olah_kiri(AVLNode *root, AVL *kanan)
{
    if(root)
    {
        int i;
        for(i=root->data; i<= abs(root->data); i+=2)
        {
            if(!avl_find(kanan, i))
                sum++;
        }
        olah_kiri(root->left, kanan);
        olah_kiri(root->right, kanan);
    }
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

int _min(int a,int b)
{
    return (a < b)? a : b;
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

void preorder(AVLNode *root) 
{
    if (root) {
        preorder(root->left);
        printf("%d ", root->data);
        preorder(root->right);
    }
}

