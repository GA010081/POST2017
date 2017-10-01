#ifndef ATOM_H
#define ATOM_H

class Number;
#include "number.h"
#include "variable.h"
#include <string>

using std::string;

class Atom{
public:
        Atom(string _Symbol):_Symbol(_Symbol){}
        string value(){
            return _Symbol;
        }
        bool operator =(Number *s){return false;}

        bool operator =(Variable *s){
            return s->Variable_Matchable_String(this->_Symbol);
          }
private:
    string const _Symbol;
};


#endif