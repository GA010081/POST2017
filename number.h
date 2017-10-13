#ifndef NUMBER_H
#define NUMBER_H

class Atom;
class Variable;
#include <string>
#include "term.h"
using std::string;

class Number:public Term{
public:
        Number(double _Symbol);
        string symbol()const;
private:
    int _Symbol;
};


#endif