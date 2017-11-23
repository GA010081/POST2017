#ifndef NODE_H
#define NODE_H

#include"atom.h"
enum Operators {SEMICOLON, COMMA, EQUALITY, TERM};

class Node {
public:
  Node(Operators op):payload(op), term(0), left(0), right(0) {}
  Node(Operators op, Term *t, Node *l, Node *r):payload(op), term(t), left(l), right(r) {}
  bool evaluate(){
      return findEqual(this);
    }
    bool findEqual(Node *n)
    {
        if(n->payload == EQUALITY)
        return n->left->term->match(*n->right->term);
        else
        return findEqual(n->left);
    }
  Operators payload ;
  Term *term;
  Node *left;
  Node *right;
};

#endif