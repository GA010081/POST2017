#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include "term.h"
using std::string;

class Number:public Term{
public:
        Number(double _Symbol);
        string symbol()const;
private:
    double _Symbol;
};


#endif