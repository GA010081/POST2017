#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include "term.h"
using std::string;

class Number:public Term{
public:
        Number(double _Symbol);
        string symbol()const;
        bool match(Term &term);
private:
    double _Symbol;
};


#endif