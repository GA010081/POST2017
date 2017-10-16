#ifndef STRUCT_H
#define STRUCT_H

#include<vector>
#include<string>
#include"atom.h"

using std::string;

class Struct:public Term{
public:
    Struct(Atom const name,std::vector<Term*> v):_Name(name),_v(v){}
    Term* args(int index)
    {
        return _v[index];
    }
    Atom const &name()
    {
        return  _Name;
    }
    string value(){
        string ret = _Name.symbol() +"(" + _v[0]->value();
        for(int i= 1 ; i<_v.size();i++)
        ret += ", " + _v[i]->value();
        ret += ")";
        return ret;

    }
    string symbol()const{
        string ret = _Name.symbol() +"(" + _v[0]->symbol();
        for(int i= 1 ; i<_v.size();i++)
        ret += ", " + _v[i]->symbol();
        ret += ")";
        return ret;
    }
    bool match(Term &term){
        Struct *ps = dynamic_cast<Struct *>(&term);
        if(ps)
        {
            for(int i =0;i<_v.size();i++){
                if(!_Name.match(ps->_Name) || _v.size()!=ps->_v.size()||_v[i]->symbol() != ps->_v[i]->symbol())
                return false;
            }
            return true;
        }
        return false;
    }
private:
    Atom _Name;
    std::vector<Term*> _v;
};
#endif
