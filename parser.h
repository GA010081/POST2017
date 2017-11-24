#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "node.h"

#include "utParser.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }
    else if(token == '['){
      return list();
    }


    return nullptr;
  }

void matchings(){
  createTerms();
  Node *eqaulLeft=0;
  Node *equalRight=0;
  Node *commaLeft=0;
  Node *commaRight=0;
  if(symtable2.size()==1)
  rootTree = new Node(EQUALITY,0,0,0);
  else
  {
    for(int i = 1 ; i <symtable2.size() ; i++)
    {
      if(symtable2[i] == "," || symtable2[i]==";" )
      {
          commaLeft = new Node(EQUALITY,0,0,0);
          if(i+2<symtable2.size())
          commaRight = new Node(COMMA,0,0,0);
          else
          commaRight = new Node(EQUALITY,0,0,0);
          if(!rootTree)
          {
            if(symtable2[i]==",")
            rootTree = new Node(COMMA,0,commaLeft,commaRight);
            else
            rootTree = new Node(SEMICOLON,0,commaLeft,commaRight);     
          }
          else if(symtable2.size()%2==1 && symtable2.size()>3)
          {
            Node *payloadComma = findLeft(rootTree);
            payloadComma->left = commaLeft;
             payloadComma->right = commaRight;
          }

      }

    }
     
  }
   findTerm(rootTree);
  
}
Node *findLeft(Node *l)
{
  if(l->payload == COMMA && l->left==0)
  return l;
  else
  return findLeft(l->right);
}

Node findTerm(Node *nodetree)
{
  if(nodetree->payload == EQUALITY)
  {
    nodetree->left = new Node(TERM,termtable[0],0,0);
    termtable.erase (termtable.begin());
    nodetree->right = new Node(TERM,termtable[0],0,0);
    termtable.erase (termtable.begin());
  }
  else if(nodetree->payload == COMMA|| nodetree->payload == SEMICOLON)
  {
  findTerm(nodetree->left);
  findTerm(nodetree->right);
  }
  
}
Node *expressionTree(){
  return rootTree;
}
  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else {
      throw string("unexpected token");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    } else {
      throw string("unexpected token");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == 260) {
        _terms.push_back(createTerm());
         termtable = _terms;
         termtable2 =_terms;
      }
    }
  
  }

  vector<Term *> _terms;
  Scanner _scanner;
  Node *rootTree;
  int _termsInt = 0;
  int _currentToken;
};
#endif
