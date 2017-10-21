#include "atom.h"
#include <string>
#include "variable.h"
using std::string;
Atom::Atom(string _Symbol){
    this->_Symbol = _Symbol;
}

string Atom::symbol()const{
    return _Symbol;
}
 bool Atom::match(Term &term){
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
