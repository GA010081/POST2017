#include "number.h"
#include "variable.h"
#include<iostream>
#include<sstream>

Number::Number(double _symbol){
    this->_Symbol = _symbol;
}
string Number::symbol()const{
    std::ostringstream strs;
    strs << _Symbol;
    std::string str = strs.str();
    return str;
}
 bool Number::match(Term &term){
    if(this==&term)
    return true;
    Variable *ps3 = dynamic_cast<Variable *>(&term);
    if(ps3){
    *ps3->_value = value();
    return true;
    }
    else 
    return false;
    }
