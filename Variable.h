#ifndef VARIABLE_H
#define VARIABLE_H

// class Atom;

#include<string>
using std::string;

class Variable{
public:
    Variable(string s){
        this->_Symbol = s;
    }  
    double value(){
        return _ValueN;
    }
    string valueS(){
        return _ValueS;
    }
    void setValue(double param){
        _ValueN = param;
    }
    bool Variable_Matchable_Number(Variable &s ,double _param){   

        if(s.value() == 0.1 || this->value() == _param)    
        {
            _Matchable = true;
            s.setValue(_param);
        }
        else
            _Matchable = false;
        
        return _Matchable;
    }
    bool Variable_Matchable_String(string _param){   
        if(_ValueS.empty() || !(_ValueS.compare(_param)))    
        {
            _Matchable = true;
            _ValueS.replace(_ValueS.begin(),_ValueS.end(),_param);
        }
        else
            _Matchable = false;
        
        return _Matchable;
    }
    // bool operator =(Number *s){}
    // bool operator =(Atom *s){
    //     Atom y = &s;
    // }
private:
    string  _Symbol;
    double _ValueN = 0.1;
    string _ValueS ="";
    bool _Matchable = true;

};
#endif