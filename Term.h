#ifndef TERM_H
#define TERM_H

#include "Atom.h"

class Number{
public:
        Number(double _Symbol):_Symbol(_Symbol){}
        double value(){return _Symbol;}
        bool operator =(Number s){return _Symbol = s._Symbol;}
        bool operator =(Atom s){return false;}
private:
    double _Symbol;
};


#endif