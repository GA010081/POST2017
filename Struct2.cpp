#include "struct.h"

Struct::Struct(Atom const name,std::vector<Term*> &v):_Name(name),_v(v){}
string Struct::symbol()const{
    string ret = _Name.symbol() +"(" + _v[0]->symbol();
    for(int i= 1 ; i<_v.size();i++)
    ret += ", " + _v[i]->symbol();
    ret += ")";
    return ret;
}
string Struct::value()const{
    string ret = _Name.symbol() +"(" + _v[0]->value();
    for(int i= 1 ; i<_v.size();i++)
    ret += ", " + _v[i]->value();
    ret += ")";
    return ret;

}

Term* Struct::args(int index)
{
    return _v[index];
}
Atom const &Struct::name()
{
    return  _Name;
}
bool Struct::match(Term &term){
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