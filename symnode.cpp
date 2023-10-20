/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){
key="";
height=1;
par=NULL;
left=NULL;
right=NULL;
}

SymNode::SymNode(string k){
key=k;
height=1;
par=NULL;
left=NULL;
right=NULL;
}

SymNode* SymNode::LeftLeftRotation(){//RIGHT ROTATE

SymNode *x=this->left;
SymNode *T2=x->right;
x->right=this;
this->left=T2;
if(this->par!=NULL)
{x->par=this->par;
if(this->par->left!=NULL&&this->par->left==this)
this->par->left=x;
else if(this->par->right!=NULL&&this->par->right==this)
this->par->right=x;
}
else
x->par=NULL;
this->par=x;
if(T2!=NULL)
T2->par=this;
if(this->right==NULL&&this->left==NULL)
this->height=1;
else if(this->right==NULL)
this->height=1+this->left->height;
else if(this->left==NULL)
this->height=1+this->right->height;
else
this->height=max(this->right->height,this->left->height)+1;
if(x->right==NULL&&x->left==NULL)
x->height=1;
else if(x->right==NULL)
x->height=1+x->left->height;
else if(x->left==NULL)
x->height=1+x->right->height;
else
x->height=max(x->left->height,x->right->height)+1;
return x;
}
SymNode* SymNode::RightRightRotation(){//LEFT ROTATE

SymNode *y=this->right;
SymNode *T2=y->left;
y->left=this;
this->right=T2;
if(this->par!=NULL)
{y->par=this->par;
if(this->par->left!=NULL&&this->par->left==this)
this->par->left=y;
else if(this->par->right!=NULL&&this->par->right==this)
this->par->right=y;
}
else 
y->par=NULL;
this->par=y;
if(T2!=NULL)
T2->par=this;
if(this->right==NULL&&this->left==NULL)
this->height=1;
else if(this->right==NULL)
this->height=1+this->left->height;
else if(this->left==NULL)
this->height=1+this->right->height;
else
this->height=max(this->right->height,this->left->height)+1;
if(y->right==NULL&&y->left==NULL)
y->height=1;
else if(y->right==NULL)
y->height=1+y->left->height;
else if(y->left==NULL)
y->height=1+y->right->height;
else
y->height=max(y->left->height,y->right->height)+1;
return y;
}

SymNode* SymNode::LeftRightRotation(){
    
this->left=this->left->RightRightRotation();
this->LeftLeftRotation();
return this;

}

SymNode* SymNode::RightLeftRotation(){
    
this->right=this->right->LeftLeftRotation();
this->RightRightRotation();
return this;
}

SymNode::~SymNode(){

par=NULL;
left=NULL;
right=NULL;
}