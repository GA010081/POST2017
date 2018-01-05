#include <iostream>
#include "atom.h"
#include "parser.h"
#include <string>

using namespace std;

int main()
{
    
    string enter;
    string x="";
    cout<<"?- ";
    while(std::getline (std::cin,enter))
    {
        x+=enter;
        if(enter.empty())
        {
            if(x=="");
            cout<<"?- ";    
        }
        if(!x.empty() && x[x.length()-1]!='.')
        cout<<"|   ";
        if(enter == "halt.")
        break;
        if(x[x.length()-1]=='.'){
                std::cout<<x<<endl;
                Scanner s(x);
                Parser p(s);
            try{
                p.buildExpression();
                Node * et = p.expressionTree();
                et->evaluate();
                string result = et->getResult();
                cout<<result<<endl;
                symtable.clear();
                symtable2.clear();
                termtable.clear();
                termtable2.clear();
                resultTable.clear();
                resultTable2.clear();
                gloabalInt=0;
                gloabalInt2 = 0;
                x="";
            } 
            catch (std::string & msg) {               
                cout<< msg <<endl;
                symtable.clear();
                symtable2.clear();
                termtable.clear();
                termtable2.clear();
                resultTable.clear();
                resultTable2.clear();
                gloabalInt=0;
                gloabalInt2 = 0;
                x="";
            }
            cout<<"?- ";
        }
         
    }
    return 0;
}
