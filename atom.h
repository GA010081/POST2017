#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "term.h"

using std::string;

class Atom:public Term{
public:
        Atom(string _Symbol);
        string symbol()const;
        bool match(Term &term);
private:
    string _Symbol;
};


#endif