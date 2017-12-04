#ifndef LIST_H
#define LIST_H

#include "atom.h"
class Struct;

#include <vector>
#include <string>
#include <typeinfo>
#include <iostream>
template<typename T>
class Iterator;
using std::vector;


class Variable ;

class List : public Term {
public:
  string symbol() const ;
  string value() const ;
  bool match(Term & term) ;
public:
  std::vector<Term *> _q;    
  List (vector<Term *> const & elements):_elements(elements){}
  List (): _elements(0) {}
  Term * head() const;
  List * tail() const;
  Term * args_q(int index) {
    return _q[index];
  }
  Term * args(int index) {
    return _elements[index];
  }
  int arity() const {return _elements.size();}
  Iterator<Term *> * createIterator();  
  Iterator<Term *> * createDFSIterator();  
  Iterator<Term *> * createBFSIterator();    
  vector<Term *> _elements;
void prepareDFSStack();
void prepareBFSStack();
void findNestedStruct(Struct *s2);
void findNestedList(List *l2);
void findNestedStructB(Struct *s2);
void findNestedListB(List *l2);
    
private:
};

#endif