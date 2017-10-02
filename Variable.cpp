#include"variable.h"
#include"atom.h"
#include"number.h"
#include<string>
using std::string;
Variable::Variable(string s){
    this->_Symbol = s;
}  
string Variable::valueS(){
    return _Value;
}

bool Variable::Variable_Matchable_String(string _param){   
     if((_Value.empty())  ||  !(_Value.compare(_param)))    
    {
        _Matchable = true;
         _Value.replace(_Value.begin(),_Value.end(),_param);
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
