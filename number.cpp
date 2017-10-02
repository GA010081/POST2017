#include "variable.h"
#include "atom.h"
#include "number.h"

Number::Number(double _symbol){
    this->_Symbol = _symbol;
}
double Number::value(){
    return _Symbol;
}
bool Number::match(Number s){
    return _Symbol == s._Symbol;
}
bool Number::match(Atom s){
    return false;
}
bool Number::match(Variable *s){
    return s->Variable_Matchable_Number(s->value(),this->_Symbol);
}