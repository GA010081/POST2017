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
       Variable *ps3 = static_cast<Variable *>(&term);
         if(65<=int(ps3->value()[0]) && int(ps3->value()[0])<=90 ||*ps3->_value == value()){
         *ps3->_value = value();
          return true;
         }
        return term.symbol()==symbol();
       ps3 = NULL;
    }
