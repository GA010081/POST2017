#include "atom.h"
#include "variable.h"
#include <typeinfo>
#include <iostream>
#include <string>
#include "list.h"
#include "iterator.h"
#include "struct.h"
using std::vector;

string List::symbol() const{
    string ret ;
    if(_elements.size()==0 ){
      ret = "[]";
    }
    else{
      ret  = "[";
      std::vector<Term *>::const_iterator it = _elements.begin();
      for( ; it != _elements.end()-1 ; ++it ){
        ret += (*it)->symbol()+", ";
      }
      ret += (*it)->symbol()+"]";
    }
    return ret;
  }
string List::value() const{
    string ret ;
    if(_elements.empty()){
        ret = "[]";
    }
    else{
        ret  = "[";
        std::vector<Term *>::const_iterator it = _elements.begin();
        for( ; it != _elements.end()-1 ; ++it ){
        ret += (*it)->value()+", ";
        }
        ret += (*it)->value()+"]";
}
return ret;
}
bool List::match(Term & term) {
    if(typeid(term) ==  typeid(List)){
        bool ret =true;
        List * ptrls = dynamic_cast<List*>(&term);
        if( _elements.size() != ptrls->_elements.size() ){
        ret = false;
        }
        else{
            for(int i = 0 ; i < _elements.size() ;i++ ){
                ret = _elements[i]->match(*(ptrls->_elements[i])) ;
                if(ret == false)
                    return ret;
            }
        }
        return ret;
    }
    else if(typeid(term) == typeid(Variable)){
        bool ret =true;
        for(int i = 0 ; i < _elements.size() ;i++ ){
        if(_elements[i]->symbol() ==  term.symbol()){
            if( _elements[i]->symbol() == term.symbol() ){
                ret= false;
                return ret;
            }
        ret = _elements[i]->match(term) ;
        }
        if(ret == false)
                return ret;
        }
        return ret;
    }
    else{
        return value () == term.value();
    }
}
Term * List::head() const{
    if(_elements.empty())
        throw std::string("Accessing head in an empty list");

    return _elements[0];
}
List * List::tail() const {
    if(_elements.empty())
        throw std::string("Accessing tail in an empty list");
    vector<Term *> _clone_elements;
    _clone_elements.assign(_elements.begin()+1, _elements.end());
    List *ls= new List(_clone_elements) ;
    return ls;
}
Iterator<Term *> * List::createIterator()
{
  return new ListIterator<Term*>(this);
}

Iterator<Term *> * List::createDFSIterator()
{
  prepareDFSStack();
  return new ListDFSIterator<Term*>(this);
}
Iterator<Term *> * List::createBFSIterator(){
    prepareBFSStack();
    return new ListBFSIterator<Term*>(this);
} 

void List::prepareDFSStack(){
    
   for(int i = 0 ; i<_elements.size();i++)
   {
     Struct *s1 = dynamic_cast<Struct *>(_elements[i]);
     List *s2 = dynamic_cast<List *>(_elements[i]);      
     if(s1)
     {
       _q.push_back(_elements[i]);
       findNestedStruct(s1);
     }
     else if(s2)
     {
       _q.push_back(_elements[i]);
       findNestedList(s2);
     }
     else
     {
     _q.push_back(_elements[i]);
     }

   }
 }
void List::prepareBFSStack(){ 
  int j =0;
  while(j<_elements.size())
  {
    _q.push_back(_elements[j]);
    j++;
  }
  for(int i = 0 ; i<_elements.size();i++)
  {
    Struct *s1 = dynamic_cast<Struct *>(_elements[i]);
    List *s2 = dynamic_cast<List *>(_elements[i]);      
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
void List::findNestedStruct(Struct *s2)
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
void List::findNestedList(List *l2)
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
void List::findNestedStructB(Struct *s2){
    int k =0;
    while(k<s2->_args.size())
    {
      _q.push_back(s2->_args[k]);
      k++;
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
  void List::findNestedListB(List *l2){
    int l =0;
    while(l<l2->_elements.size())
    {
      _q.push_back(l2->_elements[l]);
      l++;
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