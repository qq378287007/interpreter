#pragma once

#include "Ast.h"

#include <unordered_map>
#include <list>
using namespace std;

class Parser
{
public:
    enum Priority
    {
        LOWEST,
        SUM,         // + -
        PRODUCT,     // * /
        PREFIX,      // -X
        CALL        // (
    };

private:
    unordered_map<Token::Type, Priority> precedences{
        {Token::PLUS, SUM},
        {Token::MINUS, SUM},
        {Token::SLASH, PRODUCT},
        {Token::ASTERISK, PRODUCT},
        {Token::LPAREN, CALL},
    };

    using prefixParseFn = Expression * (Parser::*)();
    using infixParseFn = Expression * (Parser::*)(Expression *);

public:
    explicit Parser(const Lexer &lexer);

    void nextToken();

    inline bool curTokenIs(Token::Type t) const
    {
        return curToken.type() == t;
    }
    inline bool peekTokenIs(Token::Type t) const
    {
        return peekToken.type() == t;
    }

    bool expectPeek(Token::Type t) ;

    inline list<string> errors() const
    {
        return m_Errors;
    }

    void peekError() ;
    void noPrefixParseFnError() ;


    Expression * parseExpression(Priority precedence = LOWEST);


    Priority peekPrecedence() const;
    Priority curPrecedence() const;


    inline Expression * parseIdentifier(){
        return new Identifier{curToken};
    }

    Expression * parseNumberLiteral();

    Expression * parsePrefixExpression();

    Expression * parseInfixExpression(Expression* left);

    Expression * parseGroupedExpression();

    inline void registerPrefix(Token::Type type, prefixParseFn fn) {
        prefixParseFns[type] = fn;
    }

    inline void registerInfix(Token::Type type, infixParseFn fn) {
        infixParseFns[type] = fn;
    }

private:
    Lexer m_Lexer;
    list<string> m_Errors;

    Token curToken;
    Token peekToken;

    unordered_map<Token::Type, prefixParseFn> prefixParseFns;
    unordered_map<Token::Type, infixParseFn> infixParseFns;

};
