#ifndef NUMBER_H
#define NUMBER_H

#include "Atom.h"
#include "Variable.h"

class Number{
public:
        Number(double _Symbol):_Symbol(_Symbol){}
        double value(){return _Symbol;}
        bool operator =(Number s){return _Symbol == s._Symbol;}
        bool operator =(Atom s){return false;}
        bool operator =(Variable s){
           return s.Variable_Exit_Value(s);
        }
private:
    double const _Symbol;
};


#endif