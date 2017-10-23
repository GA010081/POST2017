#include "list.h"
string List::symbol() const{    
    if(_elements.empty())
    return "[]";
    else
    {
    string ret = "[" + _elements[0]->symbol();
    for(int i= 1 ; i<_elements.size();i++)
    ret += ", " + _elements[i]->symbol();
    ret += "]";
    return ret;
    }
}
string List::value()
{
    if(_elements.empty())
    return "[]";
    else
    {
    string ret = "[" + _elements[0]->symbol();
    for(int i= 1 ; i<_elements.size();i++)
    ret += ", " + _elements[i]->symbol();
    ret += "]";
    return ret;
    }
}
bool List::match(Term & term){
 
        List *ps = dynamic_cast<List *>(&term);
        if(ps)
        {
            if(_elements.size()!=ps->_elements.size())
            return false;
            for(int i =0;i<_elements.size();i++){
                if(_elements[i]->value() != ps->_elements[i]->value())
                {
                    if((isupper(_elements[i]->value()[0]) && isupper(ps->_elements[i]->value()[0])))
                    {
                        return true;
                    }
                    if((isupper(_elements[i]->value()[0]) && !(isupper(ps->_elements[i]->value()[0]))))
                    {
                        _elements[i]->match(*ps->_elements[i]);
                        return true;
                    }
                    if((!(isupper(_elements[i]->value()[0])) && isupper(ps->_elements[i]->value()[0])))
                    {
                        ps->_elements[i]->match(*_elements[i]);
                        return true;
                    }
                    return false;
                }
            }
            return true;
        }
        else
        return false;

    

}
Term * List::head() const{

    if(_elements.empty())
    throw 0;
    return _elements[0];

}

List * List::tail() const{
    if(_elements.empty())
    throw 0;
    vector<Term *>  const & elements2=_elements;
    List *p=new List(elements2);
    (const_cast<List*>(p))->_elements.erase((const_cast<List*>(p)->_elements.begin()));
    return  p;
}