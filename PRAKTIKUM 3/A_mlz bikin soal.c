#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

typedef struct AVLNode_t
{
    int data;
    struct AVLNode_t *left,*right, *parent, *embah;
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
void kasi_nilai_parent(AVLNode *root);

int main(){
    AVL avl;
    avl_init(&avl);
    int T, nDicek, angka;
    
    scanf("%d %d", &T, &nDicek);
    
    //insert dulu
    while(T--)
    {
        scanf("%d", &angka);
        avl_insert(&avl, angka);
    }
    
    //kasi nilai parent 
    kasi_nilai_parent(avl._root);
    
    //cek yg mau dicek
    while(nDicek--)
    {
        scanf("%d", &angka);
        avl_find(&avl, angka);
    }

}


void kasi_nilai_parent(AVLNode *root)
{
    if(root == NULL) return;
    
    //kasi 1 1
    //kiri kiri
    if(root->left != NULL)
    {
        root->left->parent = root;
        
        if(root->left->left != NULL)
        {
            root->left->left->embah = root;
        }
    }
    
    //kiri kanan
    if(root->left != NULL)
    {
        root->left->parent = root;
        
        if(root->left->right != NULL)
        {
            root->left->right->embah = root;
        }
    }
    
    
    //kanan kiri
    if(root->right != NULL)
    {
        root->right->parent = root;
        
        if(root->right->left != NULL)
        {
            root->right->left->embah = root;
        }
    }
    
    
    //kanan kanan
    if(root->right != NULL)
    {
        root->right->parent = root;
        
        if(root->right->right != NULL)
        {
            root->right->right->embah = root;
        }
    }
    if(root->left != NULL) kasi_nilai_parent(root->left);
    if(root->right != NULL) kasi_nilai_parent(root->right);
}


AVLNode* _avl_createNode(int value) 
{
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height=1;
    newNode->left = newNode->right = newNode->parent = newNode->embah = NULL;
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
    {
        if(temp->embah != NULL)
        {
            int anak_kiri = temp->embah->left->data;
            int anak_kanan = temp->embah->right->data;
            printf("%d\n", abs(anak_kiri - anak_kanan));
        }
        else
        if(temp->parent != NULL)
        {
            printf("%d\n", temp->parent->data);
        }
        else printf("0\n");
        return true;
    }
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
        preorder(root->right);
        printf("%d ", root->data);
        preorder(root->left);
    }
}

