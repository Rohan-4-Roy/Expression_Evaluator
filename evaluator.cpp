/* Do NOT add/remove any includes statements from this header file */
/* unless" EXPLICTLY clarified on Piazza. */
#include "evaluator.h"
Evaluator::Evaluator(){
    symtable=new SymbolTable();
    expr_trees={};
}
vector<ExprTreeNode*> v1;
void postdel(ExprTreeNode* root){
    if(root==nullptr)
    return ;
    if(root->left!=nullptr)
    postdel(root->left);
    if(root->right!=nullptr)
    postdel(root->right);
    delete root;
}
Evaluator::~Evaluator(){

    
    for(int i=0;i<expr_trees.size();i++){
        postdel( expr_trees[i]);
    }
        if(symtable!=nullptr)
    delete symtable;
}
int i=0;
vector<ExprTreeNode*> vec;
ExprTreeNode *root;

void Evaluator:: parse(vector<string> code)
{
 
    if(i==0)

   { 
    root=new ExprTreeNode();
    ExprTreeNode *x=new ExprTreeNode();
    root->left=x;    
    x->type="VAR";
    x->id=code[i]; 
    i++;
    parse(code);
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
        parse(code);
    }
   
    if(i==code.size())
   { vec.clear();
    i=0;
    return;}
    if(i<code.size()&&i>1){
    if(code[i]=="("){
       
        ExprTreeNode *x=new ExprTreeNode();
        root->left =x;
        vec.push_back(root);
        
        root=x;
        i++;
        parse(code);
    }
   
    else if(code[i]==")"){
        root=vec[vec.size()-1];vec.pop_back();
        
        i++;
        parse(code);
    }
    
    else if (code[i]=="+"||code[i]=="-"||code[i]=="*"||code[i]=="/")
    {  
        if(code[i]=="+")
        root->type="ADD";
        else if(code[i]=="-")
        root->type="SUB";
        else if(code[i]=="*")
        root->type="MUL";
        else
        root->type="DIV";
        ExprTreeNode *x=new ExprTreeNode();
        root->right=x;
        vec.push_back(root);
        root=x;
        i++;

        parse(code);
    }
    
    else if((int(code[i][0])<=57&&int(code[i][0])>=48)||code[i][0]=='-'){
       
        root->type="VAL";
        UnlimitedInt* num=new UnlimitedInt(code[i]);
        UnlimitedInt *den=new UnlimitedInt(1);
        UnlimitedRational *obj=new UnlimitedRational(num,den);
        root->val=obj;
        root->evaluated_value=obj;
        root=vec[vec.size()-1];vec.pop_back();
        i++;
        parse(code);        
    }
   
    else{
        
     
     
        root->type="VAR";
        root->id=code[i];
        UnlimitedRational* v= new UnlimitedRational(symtable->search(root->id)->get_p(),symtable->search(root->id)->get_q());
        root->val=v;
         
        root->evaluated_value=v;
           
        root=vec[vec.size()-1];vec.pop_back();
        i++;
               
        parse(code); 
    }}

    
}
void evaluate(ExprTreeNode* root){
    if(root->left==nullptr)
    return;
    if(root->left->left!=nullptr)
    evaluate(root->left);
    if(root->right->right!=nullptr)
    evaluate(root->right);
    if(root->type=="ADD")
   { 
    UnlimitedRational *i1=new UnlimitedRational(root->left->evaluated_value->get_p(),root->left->evaluated_value->get_q());
    UnlimitedRational *i2=new UnlimitedRational(root->right->evaluated_value->get_p(),root->right->evaluated_value->get_q());
    root->evaluated_value=UnlimitedRational::add(i1,i2);}
    else if(root->type=="SUB")
       { 
    UnlimitedRational *i1=new UnlimitedRational(root->left->evaluated_value->get_p(),root->left->evaluated_value->get_q());
    UnlimitedRational *i2=new UnlimitedRational(root->right->evaluated_value->get_p(),root->right->evaluated_value->get_q());
    root->evaluated_value=UnlimitedRational::sub(i1,i2);}
    else if(root->type=="MUL")
   { 
    UnlimitedRational *i1=new UnlimitedRational(root->left->evaluated_value->get_p(),root->left->evaluated_value->get_q());
    UnlimitedRational *i2=new UnlimitedRational(root->right->evaluated_value->get_p(),root->right->evaluated_value->get_q());
    root->evaluated_value=UnlimitedRational::mul(i1,i2);}
    else if(root->type=="DIV")
   { 
    UnlimitedRational *i1=new UnlimitedRational(root->left->evaluated_value->get_p(),root->left->evaluated_value->get_q());
    UnlimitedRational *i2=new UnlimitedRational(root->right->evaluated_value->get_p(),root->right->evaluated_value->get_q());
    root->evaluated_value=UnlimitedRational::div(i1,i2);}
}
void Evaluator::eval(){
    ExprTreeNode * root=expr_trees[expr_trees.size()-1];
    ExprTreeNode *temp=root;
    root=root->right;
    
    if(root->type=="VAL"||root->type=="VAR"){
        if(root->type=="VAR"){
    
   UnlimitedRational* v= new UnlimitedRational(symtable->search(root->id)->get_p(),symtable->search(root->id)->get_q());
   root->evaluated_value=v;
   root->val=v;
        }
    else
    {   UnlimitedRational *x=new UnlimitedRational(root->val->get_p(),root->val->get_q());
        root->evaluated_value=x;}
    
    }
    if(root->type=="ADD")
    {   
        if(root->left->left!=nullptr)
        evaluate(root->left);
        if(root->right->right!=nullptr)
        evaluate(root->right);
    UnlimitedRational *i1=new UnlimitedRational(root->left->evaluated_value->get_p(),root->left->evaluated_value->get_q());
    UnlimitedRational *i2=new UnlimitedRational(root->right->evaluated_value->get_p(),root->right->evaluated_value->get_q());
    root->evaluated_value=UnlimitedRational::add(i1,i2);
    }
   else  if(root->type=="SUB")
    {
        if(root->left->left!=nullptr)
        evaluate(root->left);
        if(root->right->right!=nullptr)
        evaluate(root->right);
            UnlimitedRational *i1=new UnlimitedRational(root->left->evaluated_value->get_p(),root->left->evaluated_value->get_q());
    UnlimitedRational *i2=new UnlimitedRational(root->right->evaluated_value->get_p(),root->right->evaluated_value->get_q());
    root->evaluated_value=UnlimitedRational::sub(i1,i2);
    }
      else   if(root->type=="DIV")
    {
        if(root->left->left!=nullptr)
        evaluate(root->left);
        if(root->right->right!=nullptr)
        evaluate(root->right);
       
        
           UnlimitedRational *i1=new UnlimitedRational(root->left->evaluated_value->get_p(),root->left->evaluated_value->get_q());
    UnlimitedRational *i2=new UnlimitedRational(root->right->evaluated_value->get_p(),root->right->evaluated_value->get_q());
    root->evaluated_value=UnlimitedRational::div(i1,i2);
       
    }
      else   if(root->type=="MUL")
    {
        if(root->left->left!=nullptr)
        evaluate(root->left);
        if(root->right->right!=nullptr)
        evaluate(root->right);
        
           UnlimitedRational *i1=new UnlimitedRational(root->left->evaluated_value->get_p(),root->left->evaluated_value->get_q());
    UnlimitedRational *i2=new UnlimitedRational(root->right->evaluated_value->get_p(),root->right->evaluated_value->get_q());
    root->evaluated_value=UnlimitedRational::mul(i1,i2);
    }
    UnlimitedRational *x=new UnlimitedRational(temp->right->evaluated_value->get_p(),temp->right->evaluated_value->get_q());
    string s = temp->left->id;
    symtable->insert(s,x);
}