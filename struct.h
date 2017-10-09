#ifndef STRUCT_H
#define STRUCT_H

#include<vector>
#include<string>
#include"atom.h"

using std::string; 

class Struct:public Term{
public:
    Struct(string Name,std::vector<Term*> v)
    {   
        _Name=Name;
        _v=v;
    }
    Term* index(int a)
    {
        return _v[a];
    }
    string value()
    {
        return  _Name;
    }

private:
    string _Name;
    std::vector<Term*> _v;
};
#endif