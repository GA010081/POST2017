#ifndef VARIABLE_H
#define VARIABLE_H

class Atom;
class Number;

#include<string>
using std::string;

class Variable{
public:
    Variable(string s);
    double value();
    string valueS();
    void setValue(double param);
    bool Variable_Matchable_Number(double s ,double _param);
    bool Variable_Matchable_String(string _param);
    bool match(Atom);
    bool match(Number);
   
 
private:
    string  _Symbol;
    double _ValueN = 0.1;
    string _ValueS ="";
    bool _Matchable = true;
    bool Variable_is_assigned = false;

};
#endif