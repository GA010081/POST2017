#include "number.h"
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
