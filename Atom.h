#ifndef ATOM_H
#define ATOM_H

#include<string>
using std::string;

class Atom{
public:
        Atom(string _Symbol):_Symbol(_Symbol){}
        string value(){return _Symbol;}
        // bool operator =(Number s){return _Symbol = s._Symbol;}

private:
    string _Symbol;
};


#endif