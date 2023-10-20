/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
UnlimitedInt* gcd (UnlimitedInt *n1,UnlimitedInt *n2){

    if(n1->get_sign()==-1)
    {
        string s=n1->to_string();
        string str="";
        for(int i=1;i<s.length();i++)
        str=str+s[i];
        n1=new UnlimitedInt(str);
    }
    if(n2->get_sign()==-1)
    {
        string s=n2->to_string();
        string str="";
        for(int i=1;i<s.length();i++)
        str=str+s[i];
        n1=new UnlimitedInt(str);
    }
    
    
    if(UnlimitedInt::sub(n2,n1)->get_sign()==1)
    {   
        UnlimitedInt *temp=n2;
        n2=n1;
        n1=temp;
    }
    
    while(n2->get_sign()!=0){
       
        UnlimitedInt* x=UnlimitedInt::mod(n1,n2);
        n1=n2;
        n2=x;
    }
    return n1;

    
}
UnlimitedRational::UnlimitedRational(){
    p=new UnlimitedInt(1);
    q=new UnlimitedInt(1);
}
UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den){
    
    UnlimitedInt * g=gcd(num,den);
    
    p=UnlimitedInt::div(num,g);
    q=UnlimitedInt::div(den,g);
    
    if(q->get_sign()==-1&&p->get_sign()!=-1){
        string qs=q->to_string();string qss;
        for(int i=1;i<qs.length();i++)
        qss=qss+qs[i];
        string ps=p->to_string();
        ps='-'+ps;
        p=new UnlimitedInt(ps);
        q=new UnlimitedInt(qss);
    } 
}
UnlimitedRational::~UnlimitedRational(){
    if(p!=nullptr)
    delete p;
    if(q!=nullptr)
    delete q;
}
UnlimitedInt* UnlimitedRational::get_p(){
return p;
}
UnlimitedInt* UnlimitedRational::get_q(){
return q;
}
string UnlimitedRational :: get_p_str(){
    return p->to_string();
}
string UnlimitedRational :: get_q_str(){
    return q->to_string();
}
string UnlimitedRational::get_frac_str(){
    return get_p_str()+"/"+get_q_str();
}
UnlimitedRational* UnlimitedRational:: add(UnlimitedRational* i1, UnlimitedRational* i2)
{   UnlimitedInt* den=UnlimitedInt::mul(i1->get_q(),i2->get_q());
    UnlimitedInt * num = UnlimitedInt::add(UnlimitedInt::mul(i1->get_p(),i2->get_q()),UnlimitedInt::mul(i2->get_p(),i1->get_q()));
    UnlimitedRational* obj=new UnlimitedRational(num,den);
    return obj;
}
UnlimitedRational* UnlimitedRational:: sub(UnlimitedRational* i1, UnlimitedRational* i2)
{
   UnlimitedInt* den=UnlimitedInt::mul(i1->get_q(),i2->get_q());
    UnlimitedInt * num = UnlimitedInt::sub(UnlimitedInt::mul(i1->get_p(),i2->get_q()),UnlimitedInt::mul(i2->get_p(),i1->get_q()));
    UnlimitedRational* obj=new UnlimitedRational(num,den);
    return obj;
}
UnlimitedRational* UnlimitedRational:: mul(UnlimitedRational* i1, UnlimitedRational* i2)
{
    UnlimitedInt* num=UnlimitedInt::mul(i1->get_p(),i2->get_p());
    UnlimitedInt* den=UnlimitedInt::mul(i1->get_q(),i2->get_q());
    UnlimitedRational* obj =new UnlimitedRational(num,den);
    return obj;
}
UnlimitedRational* UnlimitedRational:: div(UnlimitedRational* i1, UnlimitedRational* i2)
{   
    UnlimitedInt* num=UnlimitedInt::mul(i1->get_p(),i2->get_q());
  
    UnlimitedInt* den=UnlimitedInt::mul(i1->get_q(),i2->get_p());
    
    UnlimitedRational* obj =new UnlimitedRational(num,den);
    
    return obj;
}


