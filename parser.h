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
  Node *EqaulLeft=0;
  Node *EqualRight=0;
  for(int i = 0 ; i <symtable.size() ; i ++)
  if(symtable[i].second == 260)
  symtable2.push_back(symtable[i].first);

  for(int i = 0 ; i <symtable2.size() ; i ++)
  {
    for(int j=i*2;j<(i+1)*2;j++)
    { 
      if(!EqaulLeft)
      EqaulLeft=new Node(TERM,_terms[j],0,0);
      else if (!EqualRight)
      EqualRight=new Node(TERM,_terms[j],0,0);
      if(EqualRight && EqaulLeft)
      rootTree =new Node(EQUALITY,0,EqaulLeft,EqualRight);
    }
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
         
      }
    }
  }

  vector<Term *> _terms;
  Scanner _scanner;
  Node *rootTree;
  int _currentToken;
};
#endif
