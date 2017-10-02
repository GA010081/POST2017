#include"variable.h"
#include"atom.h"
#include"number.h"
#include<string>
using std::string;
Variable::Variable(string s){
    this->_Symbol = s;
}  
double Variable::value(){
    return _ValueN;
}
string Variable::valueS(){
    return _ValueS;
}
void Variable::setValue(double param){
    _ValueN = param;
}
bool Variable::Variable_Matchable_String(string _param){   
     if((_ValueS.empty() && !Variable_is_assigned)  ||  ((!(_ValueS.compare(_param)))  && Variable_is_assigned ) )   
    {
         Variable_is_assigned = true;
        _Matchable = true;
         _ValueS.replace(_ValueS.begin(),_ValueS.end(),_param);
    }
    else
        _Matchable = false;
        
    return _Matchable;
}
bool Variable::match(Atom s){
       return this->Variable_Matchable_String(s.value());
}
bool Variable::match(Number s){
       return this->Variable_Matchable_String(s.symbol());
}
