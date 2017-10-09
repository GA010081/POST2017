#ifndef TERM_H
#define TERM_H

#include <string>
using std::string;

class Term{
public:
    bool match(Term){};
    virtual string value(){};
};
#endif