#include "list.h"
#include "variable.h"
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
    string ret = "[" + _elements[0]->value();
    for(int i= 1 ; i<_elements.size();i++)
    ret += ", " + _elements[i]->value();
    ret += "]";
    return ret;
    }
}
bool List::match(Term & term){
 
        List *ps = dynamic_cast<List *>(&term);
        Variable *ps2 = dynamic_cast<Variable *>(&term);
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
        else if(ps2)
        {
            std::size_t found= symbol().find(ps2->symbol());
            if(found!=std::string::npos)
            return false;
            *ps2->_value = value();
            return true;
        }
        return false;

    

}
Term * List::head() const{
try{
    if(_elements.empty())
    throw "Accessing head in an empty list";
    return _elements[0];
}
catch(std::exception& e){
 std::cerr <<"Accessing head in an empty list"<< e.what()<< std::endl; 
}
}

List * List::tail() const{
    try{
    if(_elements.empty())
    throw "Accessing head in an empty list";
    vector<Term *>  const & elements2=_elements;
    List *p=new List(elements2);
    (const_cast<List*>(p))->_elements.erase((const_cast<List*>(p)->_elements.begin()));
    return  p;
    }
    catch(std::exception& e){
 std::cerr <<"Accessing head in an empty list"<< e.what()<< std::endl; 
}
}