#ifndef LIST_H
#define LIST_H

#include "atom.h"
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
  List (vector<Term *> const & elements):_elements(elements){}
  List (): _elements(0) {}
  Term * head() const;
  List * tail() const;
  Term * args(int index) {
    return _elements[index];
  }
  int arity() const {return _elements.size();}
  Iterator<Term *> * createIterator();  
  vector<Term *> _elements;
private:
};

#endif