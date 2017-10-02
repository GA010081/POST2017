#include "variable.h"
#include "number.h" 
#include "atom.h"
#include <string>
using std::string;

Atom::Atom(string _Symbol){
    this->_Symbol = _Symbol;
}

string Atom::value(){
    return _Symbol;
}
bool Atom::match(Number *s){
    return false;
}
bool Atom::match(Variable *s){
    return s->Variable_Matchable_String(this->_Symbol);
}