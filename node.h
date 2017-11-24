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
        if(n->payload == SEMICOLON)
        {
          gloabalInt+=2;
        }
        if(n->payload == EQUALITY)
        {
        if( isupper(n->left->term->symbol()[0]) || isupper(n->right->term->symbol()[0]) )
        {
          for(int i = gloabalInt ;i<termtable2.size();i++)
          {
           
              Struct *s1 = dynamic_cast<Struct *>(termtable2[i]);
              if(s1)
              {
                  findStuct(s1,n->right,n->left);
              }
              else{
              if(termtable2[i]->symbol()==n->left->term->symbol() && termtable2[i]->value() !=termtable2[i]->symbol())
              {
                s1=0;
                n->left->term->match(*termtable2[i]);
              }
              if(termtable2[i]->symbol()==n->right->term->symbol() && termtable2[i]->value()!=termtable2[i]->symbol())
              n->right->term->match(*termtable2[i]);
              s1=0;
            }
          }
        }
        return n->left->term->match(*n->right->term);
        }
      else
        return findEqual(n->left) && findEqual(n->right) ;
    }
  void findStuct(Struct *s,Node *l,Node *r){
    for(int i =0 ;i<s->arity();i++)
    { 
      Struct *s1 = dynamic_cast<Struct *>(s->args(i));
      std::cout<<s->args(i)->symbol()<<std::endl; 

      if(s1)
      findStuct(s1,l,r);
      else{
        s1=0;
      if(s->args(i)->symbol()==l->term->symbol())
      l->term->match(*s->args(i));
      if(s->args(i)->symbol()==r->term->symbol())
      r->term->match(*s->args(i));
      }
    }
  }
  Operators payload ;
  Term *term;
  Node *left;
  Node *right;
};

#endif