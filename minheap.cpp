/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"

//Write your code below this line

MinHeap::MinHeap(){
root=new HeapNode();
size=0;
}
int minHeight(HeapNode* root)
{
    if(root==NULL)
    return 0;
    else if(root->left==NULL&&root->right==NULL)
    return 1;
    else if(root->left==NULL)
    return 1;
    else if (root->right==NULL)
    return 1 ;
    else 
    return 1+min(minHeight(root->left),minHeight(root->right));
}
HeapNode* iN;
void HeapifyUp(HeapNode* node){
while (node->par!=NULL)
{
    if(node->par->val<=node->val)
    break;
    int temp=node->val;
    node->val=node->par->val;
    node->par->val=temp;
    if(node->par!=NULL)
    node=node->par;
    else
    node=NULL;
}

}
void insert(HeapNode* root,int val)
{

HeapNode* node=new HeapNode(val);

if(root->left==NULL){
    root->left=node;
    node->par=root;
    iN=node;
    return;
}
else if(root->right==NULL){
    root->right=node;
    node->par=root;
    iN=node;
    return;
}
else if(minHeight(root->left)<=minHeight(root->right))
{   
    insert(root->left,val);}
else
{
    insert(root->right,val);}
}
void MinHeap::push_heap(int num){
HeapNode* node=new HeapNode(num);
size++;
if(size==1)
{
    root=node;
 iN=node;   }
else if(root->left==NULL&&root->right==NULL)
{  
    root->left=node;
node->par=root;
iN=node;}
else if(root->right==NULL)
{  
    root->right=node;
node->par=root;
iN=node;}
else if(minHeight(root->left)<=minHeight(root->right))
{
    insert(root->left,num);
}
else{
    insert(root->right,num);
}
HeapifyUp(iN);
}

int MinHeap::get_min(){
return root->val;
}
int maxHeight(HeapNode* root){
    if(root==NULL)
    return 0;
    else  if(root->left==NULL&&root->right==NULL)
    return 1;
    else if (root->left==NULL)
    return 1+ maxHeight(root->right);
    else if (root->right==NULL)
    return 1+maxHeight(root->left);
    else
    return 1 + max(maxHeight(root->left),maxHeight(root->right));

}

void HeapifyDown(HeapNode* root)
{
HeapNode *min=root;
if(root->left!=NULL)
    if(min->val>root->left->val)
    {
        min=root->left;
    }
if(root->right!=NULL)
    if(min->val>root->right->val)
    {
        min=root->right;
    }
if(min==root)
return;
else if(min==root->left){
    int t=root->val;
       root->val=root->left->val;
        root->left->val=t;
       HeapifyDown(root->left);
}
else
{
       int t=root->val;
       root->val=root->right->val;
        root->right->val=t;
       HeapifyDown(root->right);   
}
}

int  pop1(HeapNode* root)
{
    int t=100;
    if(root->left==NULL&&root->right==NULL)
    {
        t=root->val;
        if(root->par->right!=NULL&&root->par->right==root)
        {   
            root->par->right=NULL;}
        else if(root->par->left!=NULL&&root->par->left==root)
        {   
            root->par->left=NULL;
            }   
        delete root;
         root =NULL;    
    }
    else  if(maxHeight(root->right)<maxHeight(root->left))
   { 
    t= pop1(root->left);
    }
    else
   {
     t= pop1(root->right);
    }
    return t;
}

void MinHeap::pop(){
    size--;
    int t;
    if(root==NULL){
        return;}
    if(root->left==NULL&&root->right==NULL)
    {delete root;
    root=NULL;
    return;}
    else  if(maxHeight(root->right)<maxHeight(root->left))
    {
        t= pop1(root->left);
        }
    else
    {      
        t= pop1(root->right);       
        }
    root->val=t;
    HeapifyDown(root);
}
void postdel(HeapNode* root){
    if(root==NULL)
    return ;
    if(root->left!=NULL)
    postdel(root->left);
    if(root->right!=NULL)
    postdel(root->right);
    delete root;
}
MinHeap::~MinHeap(){
postdel(root);
}
