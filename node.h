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
          if((n->left->term->value() == n->right->term->value())   &&  isupper(n->left->term->symbol()[0]) == isupper(n->right->term->symbol()[0]) )
          {
              if(n->left->term->match(*n->right->term))
              {
                
                resultTable.clear();
                if(resultTable2.size()==0)
                resultTable.push_back("true");
              }
          }
          else if(n->left->term->match(*n->right->term))
          {
            resultTable.clear();
            resultTable2.push_back(n->left->term);
            resultTable2.push_back(n->right->term);          
          }
          else if(!n->left->term->match(*n->right->term))
          {
            resultTable.clear();
            resultTable2.clear();
            resultTable.push_back("false");
          }
          if( isupper(n->left->term->symbol()[0]) || isupper(n->right->term->symbol()[0]) )
          {
            for(int i = first ;i<rest;i++)
              {
                Struct *s1 = dynamic_cast<Struct *>(termtable2[i]);
                List *l1 = dynamic_cast<List *>(termtable2[i]);
                if(s1)
                {
                    findStuct(s1,n->right,n->left);
                }
                if(l1)
                {
                   findList(l1,n->right,n->left);
                }
                else{
                  if( (termtable2[i]->symbol()==n->left->term->symbol()) &&  !(termtable2[i]->value() == termtable2[i]->symbol()) )
                    if(!termtable2[i]->match(*n->left->term))
                    {
                       resultTable2.clear();
                       resultTable.push_back("false");
                    }
                  else if((termtable2[i]->symbol()==n->right->term->symbol()) && !(termtable2[i]->value() == termtable2[i]->symbol()) )   
                    if(!termtable2[i]->match(*n->right->term))
                    {
                       resultTable2.clear();                      
                       resultTable.push_back("false");
                    }
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
  void findList(List *list,Node *l,Node *r){
    for(int i =0 ;i<list->arity();i++)
    {
      List *s1 = dynamic_cast<List *>(list->args(i));
      if(s1)
      findList(s1,l,r);
      else{
        s1=0;
      if(list->args(i)->symbol()==l->term->symbol()) 
        l->term->match(*list->args(i));
      if(list->args(i)->symbol()==r->term->symbol())
        r->term->match(*list->args(i));
      }
    }
  }
  string getResult(){
    string finalString ;
    for(int i = 0 ; i<resultTable.size(); i ++)
    {
      finalString += resultTable[i];
    }
    for(int i = 0 ; i<resultTable2.size(); i ++)
    {
     if(isupper(resultTable2[i]->symbol()[0]))
     finalString += resultTable2[i]->symbol();
     else
     finalString += resultTable2[i]->value();
     if(i>0 && i %2 ==1)
     finalString+= (i+1 == resultTable2.size())? "":", ";
     else
     finalString+= (i+1 == resultTable2.size())? "":" = ";
    }
    stringstream ss(finalString);
    string token;
    string old="";
    string newString="";
    string newString2="";
    while(std::getline(ss,token, ',')){
      newString = token;
      if(newString[0]==' ')
       newString.erase(newString.begin());
      if(old != newString)
      {
      if(old == "")
      newString2+= newString;
      else
      newString2+=", "+ newString;
      }
      old = newString;
    }
    newString2+=".";
    return newString2;
  }
  Operators payload ;
  Term *term;
  Node *left;
  Node *right;
};

#endif