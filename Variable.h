#ifndef VARIABLE_H
#define VARIABLE_H

#include<string>
#include "Atom.h"
using std::string;

class Variable{
public:
    Variable(string s){
        this->_Symbol = s;
    }   
    double Value(){
        return _Value;
    }
    bool Variable_Exit_Value(Variable s)
    {
        if(s._Value == 0.1 || this->_Value == s._Value)
        {       
            _Matchable = true;
            this->_Value == s._Value;
        }
        else
             _Matchable = false;
             return _Matchable;
    }

private:
    string  _Symbol;
    double _Value = 0.1;
    bool _Matchable = true;

};
#endif