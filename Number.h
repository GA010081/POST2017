#ifndef NUMBER_H
#define NUMBER_H

class Atom;
class Variable;
#include <string>
using std::string;

class Number{
public:
        Number(double _Symbol);
        double value();
        string symbol();
        bool match(Number);
        bool match(Atom );
        bool match(Variable *);
private:
    double _Symbol;
};


#endif