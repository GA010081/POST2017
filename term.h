#ifndef TERM_H
#define TERM_H

#include <string>
using std::string;

class Term{
public:
    string symbol(){}
    bool match(Term){}
    string value(){}
};
#endif