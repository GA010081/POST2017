#ifndef NUMBER_H
#define NUMBER_H

class Atom;
class Variable;

class Number{
public:
        Number(double _Symbol);
        double value();
        bool match(Number);
        bool match(Atom );
        bool match(Variable *);
private:
    double _Symbol;
};


#endif