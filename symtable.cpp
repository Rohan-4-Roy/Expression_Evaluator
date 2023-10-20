/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
SymbolTable::SymbolTable(){
    root=new SymEntry();
    size=0;
}
void postdel(SymEntry* root){
    if(root==nullptr)
    return ;
    if(root->left!=nullptr)
    postdel(root->left);
    if(root->right!=nullptr)
    postdel(root->right);
    delete root;
}
SymbolTable::~SymbolTable(){
    postdel(root);
}

int SymbolTable::get_size(){
    return size;
}
SymEntry* SymbolTable::get_root(){
    return root;
}
void insert1(string k,UnlimitedRational *v,SymEntry *node){
    
    UnlimitedRational* v1=new UnlimitedRational(v->get_p(),v->get_q());
    if(node->key=="")
    {
        node->key=k;
        node->val=v1;
        return;
    }
   else  if(node->key==k)
    {
        node->val=v1;
        return;
    }
    else if (node->key>k){
        if(node->left==nullptr)
        {
        SymEntry *x =new SymEntry(k,v1);
        node->left=x;
        insert1(k,v1,node->left);}
        else
        insert1(k,v1,node->left);
    }
    else if(node->key<k){
        if(node->right==nullptr){
        SymEntry *x=new SymEntry(k,v1);
        node->right=x;
        insert1(k,v1,node->right);}
        else
        insert1(k,v1,node->right);
    }

    
}
void SymbolTable :: insert(string k, UnlimitedRational* v)
{   UnlimitedRational* v2=new UnlimitedRational(v->get_p(),v->get_q());
    SymEntry* temp=root;
    size++;
    insert1(k,v2,temp);

}
void del(string k,SymEntry * n){
    if(n->key==k)
    {
        if(n->left==nullptr&&n->right==nullptr)
        {delete  n;return ;}
        if(n->left==nullptr)
        {*n=*n->right;
           delete n->right;
           return; }
        else
        {
            *n=*n->left;
           delete n->left;
           return;
        }
    }
    else if(n->key>k)
    del(k,n->left);
    else
    del(k,n->right);
}
void SymbolTable:: remove(string k){
    size--;
    while(true){
        if(root->key==k)
        {
           if(root->left==nullptr&&root->right==nullptr)
           {delete root;return;}
           if(root->left==nullptr){
            *root=*root->right;
            delete root->right;
            return;
           }
           if(root->right==nullptr){
            *root=*root->left;
            delete root->left;
            return;
           }
           else{
            SymEntry *node=root->right;
            while(node->left!=NULL)
                node=node->left;
            root->val=node->val;
            root->key=node->key;
            del(node->key,root->right);
           }

        }
        else if(root->key>k){
            root=root->left;
            continue;
        }
        else
        {
            root=root->right;
            continue;
        }
    }
}

UnlimitedRational* SymbolTable:: search(string k){
    
   SymEntry* temp=root;
   while(true){
    if(temp->key==k)
    {   UnlimitedRational* v=new UnlimitedRational(temp->val->get_p(),temp->val->get_q());
        return v;}
    else if(temp->key>k)
    temp=temp->left;
    else
    temp=temp->right;}
    
}