#ifndef TERM_H
#define TERM_H
#include <string>

using std::string;

class Term{
public:
    virtual string  symbol()const=0;
    virtual string value(){
        return symbol();
    }
    virtual bool match(Term &term){
         if(65<=int(term.value()[0]) && int(term.value()[0])<=90){
         term.value() = value();
          return true;
         }
         
        return term.symbol()==symbol();


    }

};
#endif