#ifndef VARIABLE_H
#define VARIABLE_H

#include<string>
#include "term.h"
#include "atom.h"
#include "number.h"
#include "struct.h"
using std::string;

class Variable:public Term{
  public:
    Variable(string s):_symbol(s),y(_symbol){
    _value=&y;

    }
    string _symbol;
    string symbol()const{
      return _symbol;
    }
    string   value(){
      if(stuct2!=NULL)
      *_value = stuct2->value();
      return *_value;
    }
    void setMemory(string &s)
    {
      _value = &s;
    }
    bool match(Term &term){
     
        Atom *ps = static_cast<Atom *>(&term);
        Struct *ps2 = dynamic_cast<Struct *>(&term);
        Variable *ps3 = static_cast<Variable *>(&term);
      if(65<=int(ps->symbol()[0]) && int(ps->symbol()[0])<=90){
   
        if((65>int(ps3->value()[0]) || int(ps3->value()[0]) >90) && (65<=int((*_value)[0]) && int((*_value)[0])<=90))
        {_value = ps3->_value;  return true;}
        else if((65>int(ps3->value()[0]) || int(ps3->value()[0]) >90) && (65>int((*_value)[0]) || int((*_value)[0])>90))
        return false;
        else if((65<=int(ps3->value()[0]) && int(ps3->value()[0]) <=90) && (65<=int((*_value)[0]) && int((*_value)[0])<=90))
        {
          if(ps3->v==NULL && v==NULL)
          {
           v  = &v2 ;
           ps3-> v = &v2;
          } 
          else if(ps3->v==NULL && v!=NULL)
          ps3->v = v;
          else if(ps3->v!=NULL && v==NULL)
          v = ps3->v ;
          else
          {
            std::vector<string *>::iterator it;         
            std::vector<string *>::iterator it2;  
            std::vector<string *>::iterator it3;     
            it = v->begin();
            it2 = ps3->v->begin();
            it3 = ps3->v->end();
            v->insert(it,it2,it3);
            ps3->v= NULL;
          }
          if(_value == ps3->_value)
          v2.push_back(_value);
          else
          {
          v2.push_back(_value);
          v2.push_back(ps3->_value);
          }
     
       *_value = *ps3->_value ; 
        ps3->setMemory(*_value); 
        return true;
        }
        else 
        {
         ps3->setMemory(*_value);
          return true;
        }
       
      }
      else{
        if(ps && (65<=int(value()[0]) && int(value()[0])<=90) || *_value ==ps->symbol())
        {
          if(ps2)
          {
          stuct2=ps2;
          }
          if(v!=NULL)
          {
            std::vector<string *>::iterator it;
            for (it=v->begin(); it<v->end(); it++)
            **it= ps->value();
            return true;
          }
          *_value = ps->value();
          return true;
        }
      }
 
        return false;
    }
      string *_value;
      Struct *stuct2=NULL;
  private:
    std::vector<string *> *v=NULL;
    string y;

};
//
#endif
