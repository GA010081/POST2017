#ifndef ATOM_H
#define ATOM_H

#include "Number.h"
#include "Variable.h"
#include <string>

using std::string;

class Atom{
public:
        Atom(string _Symbol):_Symbol(_Symbol){}
        string value(){
            return _Symbol;
        }
        bool operator =(Number s){return false;}
private:
    string const _Symbol;
};


#endif