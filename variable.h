#ifndef VARIABLE_H
#define VARIABLE_H

#include<string>
#include "term.h"
#include "atom.h"
#include "number.h"
using std::string;

class Variable:public Term{
  public:
    Variable(string s):_symbol(s),_value(&s),ptr(_value){
    }
    string _symbol;
    string symbol()const{
      return _symbol;
    }
    string value(){
      return *_value;
    }
    bool match(Term &term){
        Atom *ps = static_cast<Atom *>(&term);
        Variable *ps3 = static_cast<Variable *>(&term);
        if(65<=int(ps->symbol()[0]) && int(ps->symbol()[0])<=97){
        
          _value = ps3->_value;
      }
      else{
        if(ps && (65<=int(value()[0]) && int(value()[0])<=97) || *_value ==ps->symbol())
        {
          std::cout<<(65<=int(value()[0]) && int(value()[0])<=97)<<std::endl;
          *_value = ps->symbol();

          return true;
        }
      }


        return false;
    }
  private:
    string *_value;
    string *ptr;

};

#endif
