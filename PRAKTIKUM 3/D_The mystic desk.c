#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
typedef struct AVLNode_t
{
    char data[120];
    int freq;
    struct AVLNode_t *left,*right;
    int height;
}AVLNode;

typedef struct AVL_t
{
    AVLNode *_root;
    unsigned int _size;
}AVL;


AVLNode* _avl_createNode(char value[]);
AVLNode* _search(AVLNode *root, char value[]);
int _getHeight(AVLNode* node);
int _max(int a,int b);
int _min(int a, int b);
AVLNode* _rightRotate(AVLNode* pivotNode);
AVLNode* _leftRotate(AVLNode* pivotNode);
AVLNode* _leftCaseRotate(AVLNode* node);
AVLNode* _rightCaseRotate(AVLNode* node);
AVLNode* _leftRightCaseRotate(AVLNode* node);
AVLNode* _rightLeftCaseRotate(AVLNode* node);
int _getBalanceFactor(AVLNode* node);
AVLNode* _insert_AVL(AVL *avl,AVLNode* node,char value[]);
AVLNode* _findMinNode(AVLNode *node);
AVLNode* _remove_AVL(AVLNode* node,char value[]);
void avl_init(AVL *avl);
bool avl_isEmpty(AVL *avl);
bool avl_find(AVL *avl, char value[]);
void avl_insert(AVL *avl,char value[]);
void avl_remove(AVL *avl,char value[]);
void preorder(AVLNode *root, int freq);

int cekFreq;

int main(){
    AVL avl;
    avl_init(&avl);
    int kueri, format, freq;
    char kata[120], spasi;
    scanf("%d", &kueri);
    while(kueri--)
    {
        scanf("%d", &format);
        if(format==1)
        {
            scanf("%c", &spasi);
            gets(kata);
            avl_insert(&avl, kata);
        }
        if(format==2)
        {
            scanf("%c", &spasi);
            gets(kata);
            avl_remove(&avl, kata);
        }
        else
        if(format==0)
        {
            cekFreq = 0;
            scanf("%d", &freq);
            preorder(avl._root, freq);
            printf("---\n");
        }
    }
}

AVLNode* _avl_createNode(char value[]) 
{
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    //newNode->data = value;
    strcpy(newNode->data, value);
    newNode->freq = 1;
    newNode->height=1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

AVLNode* _search(AVLNode *root, char value[]) 
{
    while (root != NULL) 
    {
        int i=0;
        while(value[i]==root->data[i])
        {
            i++;
        }
        if(i>strlen(value) && strcmp(value, root->data)==0) return root;
        //printf("cek %c %s\n", root->data[i], value);
        if (value[i] < root->data[i])
            root = root->left;
        else if (value[i] > root->data[i])
            root = root->right;
        else return root;
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
int _min(int a, int b)
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

AVLNode* _insert_AVL(AVL *avl,AVLNode* node,char value[]) 
{
    
    if(node==NULL) // udah mencapai leaf
        return _avl_createNode(value);
     
    int i=0;
    while(value[i]==node->data[i])
    {
        i++;
    }    
    
    if(value[i] < node->data[i])
        node->left = _insert_AVL(avl,node->left,value);
    else if(value[i] > node->data[i])
        node->right = _insert_AVL(avl,node->right,value);
    
    node->height= 1 + _max(_getHeight(node->left),_getHeight(node->right)); 

    int balanceFactor=_getBalanceFactor(node);
    
    if(balanceFactor > 1 && value[i] < node->left->data[i]) // skewed kiri (left-left case)
        return _leftCaseRotate(node);
    if(balanceFactor > 1 && value[i] > node->left->data[i]) // 
        return _leftRightCaseRotate(node);
    if(balanceFactor < -1 && value[i] > node->right->data[i])
        return _rightCaseRotate(node);
    if(balanceFactor < -1 && value[i] < node->right->data[i])
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

AVLNode* _remove_AVL(AVLNode* node, char value[])
{
    if(node==NULL)
    {
        return node;
    }
    
    int i=0;
    while(value[i]==node->data[i])
    {
        //printf("%c", value[i]);
        i++;
    }   
    //printf("\n");
    int val;
    int dat;
    
    if(i>strlen(value)) val = 0;
    else val = value[i];
    
    if(i>strlen(node->data)) dat = 0;
    else dat = node->data[i];
    
    if(val > dat )
    {
        node->right= _remove_AVL(node->right,value);
    }
    else if(val < dat)
        node->left= _remove_AVL(node->left,value);
    else
    {
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
            char sementara[120];
            temp = _findMinNode(node->right);
            strcpy(node->data, temp->data);
            node->freq = temp->freq;
            strcpy(sementara, temp->data);
            node->right = _remove_AVL(node->right, sementara);
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

bool avl_find(AVL *avl, char value[]) 
{
    AVLNode *temp = _search(avl->_root, value);
    if (temp == NULL)
    {
        return false;
    }
    
    if (strcmp(temp->data,value)==0)
    {
        temp->freq = temp->freq + 1;
        return true;
    }
    else
        return false;
}

void avl_insert(AVL *avl,char value[])
{
    if(!avl_find(avl,value)){
        avl->_root=_insert_AVL(avl,avl->_root,value);
        avl->_size++;
    }

}

void avl_remove(AVL *avl,char value[])
{
    
    if(avl_find(avl,value))
    {
        avl->_root=_remove_AVL(avl->_root,value);
        avl->_size--;
    }
}

void preorder(AVLNode *root, int freq) 
{
    if (root) {
        preorder(root->right, freq);
        if(cekFreq < freq)
        {
            int butuh = _min(freq, root->freq);
            //printf(" butuh %d", root->freq);
            cekFreq += butuh;
            int i;
            for(i=0; i < butuh; i++)
                printf("%s\n", root->data);
        }
        preorder(root->left, freq);
    }
}

