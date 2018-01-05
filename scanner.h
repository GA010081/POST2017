#ifndef SCANNER_H
#define SCANNER_H

#include "global.h"


#include <string>
#include <vector>
using std::string;
using std::vector;

class Scanner {
public:
  Scanner (string in=""):buffer(in), pos(0), _tokenValue(NONE){}
  void setInput(string in) {buffer = in;}

  int nextToken() {
      if(buffer[buffer.length()-1] == '.' && (buffer[buffer.length()-2] ==';'))
      throw string("Unexpected ';' before '.'");
      if(buffer[buffer.length()-1] == '.' && isCon(buffer[buffer.length()-2]))
      throw string("Unexpected ',' before '.'");
      std::string str2 ("=");
      std::size_t found = buffer.find(str2);
      if(found==std::string::npos)
      throw string("X does never get assignment");
      for(int i = 0 ; i <buffer.length();i++)
      {
        if(buffer[i]==';' && (buffer [i+1] ==')' || buffer [i+1] ==']'))
        throw string("Unbalanced operator");
      }
      if(currentChar()=='[' ||currentChar()=='(')
      {
        gloabalInt2++;
      }
      if(currentChar()==']' ||currentChar()==')')
      {
        gloabalInt2--;
      }
      if (skipLeadingWhiteSpace() >= buffer.length())
      {
        if(buffer[buffer.length()-1]!= '.')
        throw string("Missing token '.'");
        return EOS;
      }
      else if (isdigit(currentChar())) {
        _tokenValue = extractNumber();
        return NUMBER;
      }  else if (islower(currentChar())) {
        string s = extractAtom();
        processToken<ATOM>(s);
        return ATOM;
      } else if (isSpecialCh(currentChar())) {
        string s = extractAtomSC();
        processToken<ATOMSC>(s);
        return ATOMSC;
      } else if (isupper(currentChar()) || currentChar() == '_') {
        string s = extractVar();
        processToken<VAR>(s);
        return VAR;
      }
      else if (isCon(currentChar()) || currentChar() == ';') {
        string s = extractCon();
        if(gloabalInt2 == 0)
        processToken<Con>(s);
        return Con;
      }
      else {
        _tokenValue = NONE;
        return extractChar();
      }
  }

  int tokenValue() const {return _tokenValue;}

  int skipLeadingWhiteSpace() {
    for (; (buffer[pos] == ' ' || buffer[pos] == '\t') && pos<buffer.length(); ++pos);
    return position();
  }

  int position() const {return pos;}

  char currentChar() {
    return buffer[pos];
  }

  // extractX: extract X and set position right after X
  int extractNumber() {
    int posBegin = position();
    for (;isdigit(buffer[pos]); ++pos);
    return stoi(buffer.substr(posBegin, pos-posBegin));
  }

  string extractAtom() {
    int posBegin = position();
    for (;isalnum(buffer[pos]) || currentChar() == '_'; ++pos);
    return buffer.substr(posBegin, pos-posBegin);
  }

  string extractAtomSC() {
    int posBegin = position();
    for (;isSpecialCh(buffer[pos]); ++pos);
    return buffer.substr(posBegin, pos-posBegin);
  }

  string extractVar() {
    int posBegin = position();
    for (;isalnum(buffer[pos]) || buffer[pos] == '_'; ++pos);
    return buffer.substr(posBegin, pos-posBegin);
  }
  string extractCon() {
    int posBegin = position();
    for (;isCon(buffer[pos]) || currentChar() == ';'; ++pos);
    return buffer.substr(posBegin, pos-posBegin);
  }
  char extractChar() {
    return buffer[pos++];
  }

private:
  string buffer;
  int pos;
  int _tokenValue;

private:
  // case-based populating symtable and setting _tokenValue
  template <int TokenType>
  void processToken(string const & s) {
    int val = -1;
    if (symbolExist(s,val) && TokenType!=260) {
        _tokenValue = val;
    } else {
      if(TokenType ==260)
      {
        symtable2.push_back(s);
      }
      else
      {
        if(s=="." && currentChar() !='(');
        else
        symtable.push_back(pair<string, int>(s,TokenType));
        _tokenValue = symtable.size()-1; // index to symtable
      }
    }
  }
};


#endif
