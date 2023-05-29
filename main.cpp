#include <iostream>
using namespace std;

#include "Parser.h"

int main(){
    {
        string line{"_a+b25*c-(12.52+5)"};
        Lexer l{line};
        for(Token token = l.NextToken(); token.type() != Token::EOF0; token = l.NextToken())
            cout<<token.literal()<<"\n";
    }
    {
        string line{"a+b*c-(12+5.26)"};
        Lexer l{line};
        Parser p{l};

        Expression *exp = p.parseExpression();
        cout<<exp->String()<<endl;
    }

    cout<<"Over!\n";
    return 0;
}
