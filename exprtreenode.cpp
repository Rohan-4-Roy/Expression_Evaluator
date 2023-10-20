/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"
ExprTreeNode::ExprTreeNode(){
    type="";
    val=new UnlimitedRational();
    left=nullptr;
    right=nullptr;
    id="";
    evaluated_value=new UnlimitedRational();
}
ExprTreeNode::ExprTreeNode(string t,UnlimitedInt *v){

    UnlimitedRational *x=new UnlimitedRational(v,new UnlimitedInt(1));
    type=t;
    left=nullptr;
    right=nullptr;
    id="";
    val=x;
    evaluated_value=x;
}
ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v){
    type=t;
    UnlimitedRational* x=new UnlimitedRational(v->get_p(),v->get_q());
    val=x;
    left=nullptr;
    right=nullptr;
    id="";
    evaluated_value=x;
}
ExprTreeNode::~ExprTreeNode(){
    delete val;
    left=nullptr;
    right=nullptr;


}