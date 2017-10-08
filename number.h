#ifndef NUMBER_H
#define NUMBER_H

class Atom;
class Variable;
#include <string>
#include "term.h"
using std::string;

class Number:public Term{
public:
        Number(int _Symbol);
        string value();
        string symbol();
        bool match(Number);
        bool match(Atom );
        bool match(Variable &);
private:
    int _Symbol;
};


#endif