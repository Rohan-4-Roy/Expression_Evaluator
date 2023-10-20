
/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your expression below this line

Parser::Parser(){
symtable=new SymbolTable();
expr_trees={};
}

int i=0;
vector<ExprTreeNode*> vec;
ExprTreeNode *root;

void Parser::parse(vector<string> expression){

 if(i==0)

   { 
    
    root=new ExprTreeNode();
    ExprTreeNode *x=new ExprTreeNode();
    root->left=x;  
    if(expression[i]=="del"){//CHANGES
        x->type="DEL";
    ExprTreeNode *y=new ExprTreeNode();
        root->right=y;
        root->type=":=";
        expr_trees.push_back(root);
        root->right->type="VAR";
        root->right->id=expression[2];
        root->right->num=symtable->search(expression[2]);
        last_deleted=root->right->num;
        symtable->remove(root->id);
        i=0;
        vec.clear();
        return;
    }
    if(expression[i]=="ret"){
        
        x->type="RET";
        i++;
        parse(expression);
        return;
    }
    x->type="VAR";
    x->id=expression[i]; 
    i++;
    parse(expression);
    return;
    }
    
    else if(i==1){
        ExprTreeNode *x=new ExprTreeNode();
        root->right=x;
        root->type=":=";
        expr_trees.push_back(root);
        vec.push_back(root);
        root=root->right;
        
        i++;
        parse(expression);
    }
   
    if(i==expression.size())
   { vec.clear();
    i=0;
    return;}
    if(i<expression.size()&&i>1){
        
    if(expression[i]=="("){
       
        ExprTreeNode *x=new ExprTreeNode();
        root->left =x;
        vec.push_back(root);
        
        root=x;
        i++;
        parse(expression);
    }
   
    else if(expression[i]==")"){
        root=vec[vec.size()-1];vec.pop_back();
        
        i++;
        parse(expression);
    }
    
    else if (expression[i]=="+"||expression[i]=="-"||expression[i]=="*"||expression[i]=="/")
    {  
        if(expression[i]=="+")
        root->type="ADD";
        else if(expression[i]=="-")
        root->type="SUB";
        else if(expression[i]=="*")
        root->type="MUL";
        else
        root->type="DIV";
        ExprTreeNode *x=new ExprTreeNode();
        root->right=x;
        vec.push_back(root);
        root=x;
        i++;

        parse(expression);
    }
    
    else if((int(expression[i][0])<=57&&int(expression[i][0])>=48)||expression[i][0]=='-'){

        root->type="VAL";
        root->num=stoi(expression[i]);
        root=vec[vec.size()-1];vec.pop_back();
        i++;
        parse(expression);        
    }
    else{
        root->type="VAR";
        root->id=expression[i];
        root->num=symtable->search(root->id) ; 
        root=vec[vec.size()-1];vec.pop_back();
        i++;        
        parse(expression); 
    }}
}

void postdel(ExprTreeNode* root){
    if(root==NULL)
    return ;
    if(root->left!=NULL)
    postdel(root->left);
    if(root->right!=NULL)
    postdel(root->right);
    delete root;
}
Parser::~Parser(){
   
    for(int i=0;i<expr_trees.size();i++){
        postdel( expr_trees[i]);
    }
    if(symtable!=NULL)
    delete symtable;
}