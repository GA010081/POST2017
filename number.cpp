#include "number.h"

Number::Number(double _symbol){
    this->_Symbol = _symbol;
}
double Number::value()
{
    return _Symbol;
}
bool Number::operator =(Number s){
    return _Symbol == s._Symbol;
}
bool Number::operator =(Atom s){
    return false;
}
bool Number::operator =(Variable s){
    return s.Variable_Exit_Value(s);
}