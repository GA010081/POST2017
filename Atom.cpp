#include "atom.h"
#include <string>
using std::string;
Atom::Atom(string _Symbol){
    this->_Symbol = _Symbol;
}

string Atom::symbol()const{
    return _Symbol;
}