#ifndef VARIABLE_H
#define VARIABLE_H

class Atom;
class Number;

#include<string>
#include "term.h"
using std::string;

class Variable:public Term{
public:
    Variable(string s);
    string value();
    bool Variable_Matchable_String(string _param);
    bool match(Atom);
    bool match(Number);
    bool match(Variable &);
 
private:
    string  _Symbol;
    string _Value ="";
    bool _Matchable = true;
};
#endif