#include "variable.h"
#include "atom.h"
#include "number.h"

Number::Number(int _symbol){
    this->_Symbol = _symbol;
}
string Number::value(){
    return (std::to_string(_Symbol));
}
string Number::symbol(){
    return (std::to_string(_Symbol));
}
bool Number::match(Number s){
    return _Symbol == s._Symbol;
}
bool Number::match(Atom s){
    return false;
}
bool Number::match(Variable *s){
    return s->Variable_Matchable_String((this->symbol()));
}