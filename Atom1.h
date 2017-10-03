#ifndef ATOM_H
#define ATOM_H

class Number;
class Variable;

#include <string>
using std::string;

class Atom{
public:
        Atom(string _Symbol);
        string value();
        bool match(Number *);
        bool match(Variable *);
private:
    string _Symbol;
};


#endif