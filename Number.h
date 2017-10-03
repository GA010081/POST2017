#ifndef NUMBER_H
#define NUMBER_H

class Atom;
class Variable;
#include <string>
using std::string;

class Number{
public:
        Number(int _Symbol);
        string value();
        string symbol();
        bool match(Number);
        bool match(Atom );
        bool match(Variable *);
private:
    int _Symbol;
};


#endif