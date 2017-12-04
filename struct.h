#ifndef STRUCT_H
#define STRUCT_H

#include "atom.h"
#include <vector>
#include <string>
#include <vector>
#include <iostream>
#include "list.h"


using std::string;
template<typename T>
class Iterator;

class Struct: public Term {
public:
  std::vector<Term *> _q;  
  Struct(Atom name, std::vector<Term *> args): _name(name) {
    _args = args;
  }

  Term * args(int index) {
    return _args[index];
  }
  Term * args_q(int index) {
    return _q[index];
  }

  Atom & name() {
    return _name;
  }
  string symbol() const {
    if(_args.empty())
    return  _name.symbol() + "()";
    string ret = _name.symbol() + "(";
    std::vector<Term *>::const_iterator it = _args.begin();
    for (; it != _args.end()-1; ++it)
      ret += (*it)->symbol()+", ";
    ret  += (*it)->symbol()+")";
    return ret;
  }

  string value() const {
    string ret = _name.symbol() + "(";
    std::vector<Term *>::const_iterator it = _args.begin();
    for (; it != _args.end()-1; ++it)
      ret += (*it)->value()+", ";
    ret  += (*it)->value()+")";
    return ret;
  }
  int arity() const {return _args.size();}
  Iterator<Term *> * createIterator();
  Iterator<Term *> * createDFSIterator();
  Iterator<Term *> * createBFSIterator();  
  void prepareDFSStack(){
     
    for(int i = 0 ; i<_args.size();i++)
    {
      Struct *s1 = dynamic_cast<Struct *>(_args[i]);
      List *s2 = dynamic_cast<List *>(_args[i]);      
      if(s1)
      {
        _q.push_back(_args[i]);
        findNestedStruct(s1);
      }
      else if(s2)
      {
        _q.push_back(_args[i]);
        findNestedList(s2);
      }
      else
      {
      _q.push_back(_args[i]);
      }

    }
  }
void prepareBFSStack(){
  int j =0;
  while(j<_args.size())
  {
    _q.push_back(_args[j]);
    j++;
  }
  for(int i = 0 ; i<_args.size();i++)
  {
    Struct *s1 = dynamic_cast<Struct *>(_args[i]);
    List *s2 = dynamic_cast<List *>(_args[i]);  
    if(s1)
    {
      for(int i = 0 ; i<s1->_args.size();i++)
      {
        _q.push_back(s1->_args[i]);
      }
    }    
    if(s2)
    {
      for(int i = 0 ; i<s2->_elements.size();i++)
      {
        _q.push_back(s2->_elements[i]);
      }
    }   
  }
  for(int i = 0 ; i<_args.size();i++)
  {
    Struct *s1 = dynamic_cast<Struct *>(_args[i]);
    List *s2 = dynamic_cast<List *>(_args[i]);      
    if(s1)
    {
      s2 = 0;
      findNestedStructB(s1);
    }
    else if(s2)
    {
      s1 = 0;
      findNestedListB(s2);
    }
  }
}
void findNestedStructB(Struct *s2){
  for(int i = 0 ; i<s2->_args.size();i++)
  {
    Struct *s1 = dynamic_cast<Struct *>(s2->_args[i]);
    List *l2 = dynamic_cast<List *>(s2->_args[i]);  
    if(s1)
    {
      for(int i = 0 ; i<s1->_args.size();i++)
      {
        _q.push_back(s1->_args[i]);
      }
    }    
    if(l2)
    {
      for(int i = 0 ; i<l2->_elements.size();i++)
      {
        _q.push_back(l2->_elements[i]);
      }
    }   
  }
  for(int i = 0 ; i<s2->_args.size();i++)
  {
    Struct *s1 = dynamic_cast<Struct *>(s2->_args[i]);
    List *l2 = dynamic_cast<List *>(s2->_args[i]);      
    if(s1)
    {
      l2 = 0;
      findNestedStructB(s1);
    }
    else if(l2)
    {
      s1 = 0;
      findNestedListB(l2);
    }
  }
}
void findNestedListB(List *l2){
  for(int i = 0 ; i<l2->_elements.size();i++)
  {
    Struct *s1 = dynamic_cast<Struct *>(l2->_elements[i]);
    List *l3 = dynamic_cast<List *>(l2->_elements[i]);  
    if(s1)
    {
      for(int i = 0 ; i<s1->_args.size();i++)
      {
        _q.push_back(s1->_args[i]);
      }
    }    
    if(l3)
    {
      for(int i = 0 ; i<l3->_elements.size();i++)
      {
        _q.push_back(l3->_elements[i]);
      }
    }   
  }
  for(int i = 0 ; i<l2->_elements.size();i++)
  {
    Struct *s1 = dynamic_cast<Struct *>(l2->_elements[i]);
    List *s2 = dynamic_cast<List *>(l2->_elements[i]);      
    if(s1)
    {
      s2 = 0;
      findNestedStructB(s1);
    }
    else if(s2)
    {
      s1 = 0;
      findNestedListB(s2);
    }
  }
}
void findNestedStruct(Struct *s2)
{
  for(int i = 0 ; i<s2->_args.size();i++)
  {
    Struct *s3 = dynamic_cast<Struct *>(s2->_args[i]);
    List *s4 = dynamic_cast<List *>(s2->_args[i]);  
    if(s3)
    {
    _q.push_back(s2->_args[i]);
    findNestedStruct(s3);
    }
    else if (s4)
    {
    _q.push_back(s2->_args[i]);
    findNestedList(s4);
    }
    else
    {      
      _q.push_back(s2->_args[i]);
    }

  }
}
void findNestedList(List *l2)
{
  for(int i = 0 ; i<l2->_elements.size();i++)
  {
    Struct *s3 = dynamic_cast<Struct *>(l2->_elements[i]);    
    List *l3 = dynamic_cast<List *>(l2->_elements[i]);
    if(l3)
    {
    _q.push_back(l2->_elements[i]);
    findNestedList(l3);
    }
    else if (s3)
    { 
      _q.push_back(l2->_elements[i]);
      findNestedStruct(s3);
    }
    else
    {      
      _q.push_back(l2->_elements[i]);
    }

  }
}
std::vector<Term *> _args;
private:
  Atom _name;
};

#endif