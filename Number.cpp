#include "number.h"
#include<iostream>
Number::Number(double _symbol){
    this->_Symbol = _symbol;
}
string Number::symbol()const{
    return (std::to_string(_Symbol));
}
