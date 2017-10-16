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
       Variable *ps3 = static_cast<Variable *>(&term);
         if(65<=int(ps3->value()[0]) && int(ps3->value()[0])<=90 || *ps3->_value == value()){
         *ps3->_value = value();
          return true;
         }
        return term.symbol()==symbol();
        ps3 = NULL;

    }
