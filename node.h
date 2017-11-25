#ifndef NODE_H
#define NODE_H

#include"atom.h"
enum Operators {SEMICOLON, COMMA, EQUALITY, TERM};

class Node {
public:
  Node(Operators op):payload(op), term(0), left(0), right(0) {}
  Node(Operators op, Term *t, Node *l, Node *r):payload(op), term(t), left(l), right(r) {}
  bool evaluate(){
      return findEqual(this,0,termtable2.size());
  }
  bool findEqual(Node *n,int first ,int rest)
    {
        if(n->payload == SEMICOLON)
        {
          gloabalInt+=2;
          return findEqual(n->left,0,gloabalInt) && findEqual(n->right,gloabalInt,termtable2.size()) ;
        }
        else if(n->payload == EQUALITY)
        {
          if( isupper(n->left->term->symbol()[0]) || isupper(n->right->term->symbol()[0]) )
          {
            for(int i = first ;i<rest;i++)
              {
            
                Struct *s1 = dynamic_cast<Struct *>(termtable2[i]);
                if(s1)
                {
                    findStuct(s1,n->right,n->left);
                }
                else{

                  if( (termtable2[i]->symbol()==n->left->term->symbol()) &&  !(termtable2[i]->value() == termtable2[i]->symbol()) )
                  termtable2[i]->match(*n->left->term);
                  else if(  (termtable2[i]->symbol()==n->right->term->symbol()) && !(termtable2[i]->value() == termtable2[i]->symbol()) )
                  termtable2[i]->match(*n->right->term);
              }
            }
          }
          return n->left->term->match(*n->right->term);
        }
      else
        return findEqual(n->left,gloabalInt,termtable2.size()) && findEqual(n->right,gloabalInt,termtable2.size()) ;
    }
  void findStuct(Struct *s,Node *l,Node *r){
    for(int i =0 ;i<s->arity();i++)
    { 
      Struct *s1 = dynamic_cast<Struct *>(s->args(i));
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