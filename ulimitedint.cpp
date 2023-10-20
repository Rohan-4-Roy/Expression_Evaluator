/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
UnlimitedInt::UnlimitedInt(){
    size=1;
    sign=0;
    capacity=1;
    unlimited_int=new int[size];
    unlimited_int[0]=0;
}
UnlimitedInt::UnlimitedInt(string s){
   
    int k=0;
    if(s[0]=='-')
    {   
        sign=-1;k++;
        size=s.length()-1;}
    else if(s=="0")
    {  
        sign=0;size=s.length();}
    else
    {size=s.length();sign=1;}
    unlimited_int=new int[size];
    
    capacity=0;
    for(;k<s.length();k++)
    {   
        unlimited_int[capacity++]=(int)(s[k])-48;
    }
}
UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz){
    this->unlimited_int=unlimited_int;
    capacity=cap;
    sign=sgn;
    size=sz;
}
UnlimitedInt::UnlimitedInt(int i){
    string s=std::to_string(i);
    int k=0;
    if(s[0]=='-')
    {   
        sign=-1;k++;
        size=s.length()-1;}
    else if(s=="0")
    {  
        sign=0;size=s.length();}
    else
    {size=s.length();sign=1;}
    unlimited_int=new int[size];
    
    capacity=0;
    for(;k<s.length();k++)
    {   
        unlimited_int[capacity++]=(int)(s[k])-48;
    }  
}
UnlimitedInt::~UnlimitedInt(){
    size=0;
    sign=0;
    capacity=0;
    delete [] unlimited_int;
}
int UnlimitedInt::get_size(){
    return size;
}
int UnlimitedInt::get_capacity(){
    return capacity;
}

int * UnlimitedInt::get_array(){
    return unlimited_int;
}

int UnlimitedInt::get_sign()
{
    return sign;
}
string UnlimitedInt::to_string(){
    int* a=this->get_array();
    string s="";
    if(this->get_sign()==-1)
    s=s+'-';
    for(int i=0;i<this->get_size();i++)
    s=s+char(a[i]+48);
    return s;
}
UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2){
    string s;
    int l1=i1->get_size()-1,l2=i2->get_size()-1;
    int *a=i1->get_array();int *b=i2->get_array();
    int c=0;
    if(i2->get_sign()==-1&&i1->get_sign()!=-1)
    {   
        string str=i2->to_string();string s1;
        for(int i=1;i<str.length();i++)
        s1=s1+str[i];
        UnlimitedInt *i3=new UnlimitedInt(s1);
        UnlimitedInt *i4=sub(i1,i3);
        return i4;
    }
    if(i1->get_sign()==-1&&i2->get_sign()!=-1){
        
        string str=i2->to_string();
        str='-'+str;
        UnlimitedInt *i3=new UnlimitedInt(str);
        
        UnlimitedInt *i4=sub(i1,i3);
        return i4;
    }
    while(l1>=0&&l2>=0){
        int x=a[l1]+b[l2]+c;c=0;
        if(x>=10){
        s=char(x-10+48)+s;
        c++;}
        else
        s=char(x+48)+s;
        l1--;l2--;
    }
    while(l1>=0){
        int x=a[l1--]+c;c=0;
        s=char(x+48)+s;
    }
    while(l2>=0){
        int x=b[l2--]+c;c=0;
        s=char(x+48)+s;
    }
    if(c!=0)
    s=char(c+48)+s;
    
    if(i1->get_sign()==-1&&i2->get_sign()==-1)
    s='-'+s;
    UnlimitedInt *obj =new UnlimitedInt(s);
    return obj; 


}
UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2){
    string s;int flag=0;
    int l1=i1->get_size()-1,l2=i2->get_size()-1;
    int *a=i1->get_array();int *b=i2->get_array();
    if(l2>l1){
        int *temp=a;
        a=b;
        b=temp;
        flag=1;
        int t=l1;
        l1=l2;
        l2=t; 
              
    }
    else if(l1==l2&&i2->to_string()>i1->to_string()){
        int *temp=a;
        a=b;
        b=temp;
        flag=1;
        int t=l1;
        l1=l2;
        l2=t;
    }
    if((i2->get_sign()==-1&&i1->get_sign()!=-1)|| (i1->get_sign()==-1&&i2->get_sign()!=-1))
    {
        return add(i1,i2);
    }
    else if(i1->get_sign()==-1&&i2->get_sign()==-1)
    {  
        string s1,s2;string str1=i1->to_string();string str2=i2->to_string();
        for(int i =1;i<str1.length();i++)
         s1=s1+str1[i];
        for(int i =1;i<str2.length();i++)
         s2=s2+str2[i];
        UnlimitedInt *obj1=new UnlimitedInt(s1);
        UnlimitedInt *obj2=new UnlimitedInt(s2);
        UnlimitedInt *obj3=sub(obj1,obj2);
        s1=obj3->to_string();
        s1='-'+s1;
        UnlimitedInt *obj=new UnlimitedInt(s1);
        return obj;
    }
    int c=0,diff;
    while(l1>=0&&l2>=0){
        int x1=a[l1--],x2=b[l2--];
        x1=x1-c;c=0;
        if(x1==-1)
        {x1=9;c=1;}
        if(x1>=x2){
            diff=x1-x2;
        }
        else{
            diff=10+x1-x2;c++;
        }
        s=char(diff+48)+s;        
    }
    while(l1>=0){
        int x1=a[l1--];
        x1=x1-c;c=0;
        if(x1==-1)
        {x1=9;c=1;}
        s=char(x1+48)+s;
    }
    if(c!=0)
    {s=char(c+48)+s;s='-'+s;}
    if(flag==1)
    s='-'+s;
    string s1;int flg=0;
  
    for(int i=0;i<s.length();i++){
        if(s[i]!='0')
        flg=1;
        if(flg==1)
        s1=s1+s[i];
    }
   
    
    if(s1=="")
    s1="0";
    UnlimitedInt *obj =new UnlimitedInt(s1);
    return obj; 

}
UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2)
{
   
    string s;
    int l1=i1->get_size(),l2=i2->get_size();
    int *a=i1->get_array();int *b=i2->get_array();
    int k1=i1->get_sign(),k2=i2->get_sign();
    if(k1==0||k2==0)
    {
        s="0";
        UnlimitedInt *obj=new UnlimitedInt(s);
        return obj;
    }
    if(l2>l1){
        int *temp=a;
        a=b;
        b=temp;
        int t=l1;
        l1=l2;
        l2=t;
    }
    string s2="0";int c=0;
    for(int i=0;i<l2;i++){
        int x=b[l2-i-1];
        string s1=""; c=0;
        for(int j=0;j<l1;j++){
            int y=a[l1-j-1];
            int k=x*y+c;
            c=k/10.0;
            k=k%10;
            s1=char(k+48)+s1;
        }
        if(c!=0)
        s1=char(c+48)+s1;
        for(int p=0;p<i;p++){
            s1=s1+'0';
        }
        UnlimitedInt * obj1=new UnlimitedInt(s1);
        UnlimitedInt * obj2=new UnlimitedInt(s2);
        UnlimitedInt *obj=add(obj1,obj2);
        s2=obj->to_string();
    }
    if(k1*k2==-1)
    s2='-'+s2;
    
    UnlimitedInt *obj=new UnlimitedInt(s2);
    
    return obj;
}
UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2){
    string s;
    int flag=0;
    int l1=i1->get_size(),l2=i2->get_size();
    int *a=i1->get_array();int *b=i2->get_array();
    int k1=i1->get_sign(),k2=i2->get_sign();
    if(l2>l1||k2==0||k1==0){
        
        UnlimitedInt *obj=new UnlimitedInt();
        return obj;
    }
    if(k1*k2==-1){
        flag=1;
        if(k1==-1)
        {
            string s1;
            string str=i1->to_string();
            for(int i=1;i<str.length();i++)
            s1=s1+str[i];
            UnlimitedInt *ob=new UnlimitedInt(s1);
            i1=ob;
          
        }
        if(k2==-1){
            string s1;
            string str=i2->to_string();
            for(int i=1;i<str.length();i++)
            s1=s1+str[i];
            UnlimitedInt *ob=new UnlimitedInt(s1);
            i2=ob;  
        }
    }
    if(k1==-1&&k2==-1){
            string s1;
            string str=i1->to_string();
            for(int i=1;i<str.length();i++)
            s1=s1+str[i];
            UnlimitedInt *ob=new UnlimitedInt(s1);
            i1=ob; 
            string s11;
            string str1=i2->to_string();
            for(int i=1;i<str1.length();i++)
            s11=s11+str1[i];
            UnlimitedInt *ob1=new UnlimitedInt(s11);
            i2=ob1;
    }
    if(l1==l2&&i2->to_string()>i1->to_string())
    {
        UnlimitedInt *obj=new UnlimitedInt();
        return obj; 
    }
  
    int k=0;string q="";
    string x="";
    for(int i=0;i<l2;i++){
    x=x+i1->to_string()[i];
        }
        k=k+l2;
   
    while(k<=l1){
       
        while(x.length()<=l2&&i2->to_string()>x){
        if(k>=l1)
        break;
        if(k==l2)
       { x=x+i1->to_string()[k];
        }
        else
        {   
           x=x+i1->to_string()[k];
           q=q+'0'; 
        }
        k++;
        }
        
        UnlimitedInt *temp=new UnlimitedInt(x);
        int i=0;
        UnlimitedInt* mult=new UnlimitedInt(i);
        while(sub(sub(temp,mul(mult,i2)),i2)->get_sign()!=-1){
            i++;
            mult=new UnlimitedInt(i);
        }
        q=q+mult->to_string();
        
        x=sub(temp,mul(i2,mult))->to_string();
       
        if(k<i1->get_size())
       { 
        x=x+i1->to_string()[k];}
        k++;
    }
    if(flag==1)
    {   
        if(mod(i1,i2)->get_sign()!=0)
        {  
            UnlimitedInt *obj=new UnlimitedInt(q);
            UnlimitedInt * one =new UnlimitedInt(1);
            UnlimitedInt *res=add(obj,one);
            q=res->to_string(); 
        }
        q='-'+q;
    }
    UnlimitedInt *obj=new UnlimitedInt(q);
    return obj;


}
UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2){
int flag=0;
if(i1->get_sign()==-1)
{   flag=1;
    string str=i1->to_string();
    string s1="";
    for(int i=1;i<str.length();i++)
    s1=s1+str[i];
    i1=new UnlimitedInt(s1);
}  
if(i2->get_sign()==-1)
{   
    string str=i2->to_string();
    string s1="";
    for(int i=1;i<str.length();i++)
    s1=s1+str[i];
    i2=new UnlimitedInt(s1);
}  
UnlimitedInt *obj1=div(i1,i2);
UnlimitedInt *obj2=mul(i2,obj1);
if(flag==0||sub(i1,obj2)->to_string()=="0")
return sub(i1,obj2);
string str=sub(i1,obj2)->to_string();
str='-'+str;
UnlimitedInt *obj=new UnlimitedInt(str);
return obj;
// UnlimitedInt *obj3=div(i1,i2);
// cout<<obj3->to_string()<<endl;
// UnlimitedInt *obj2=mul(i2,obj3);
// cout<<obj2->to_string()<<endl;
// UnlimitedInt *obj1=sub(i1,obj2);
// cout<<obj1->to_string()<<endl;
// return obj1;
}


