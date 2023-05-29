#include "Parser.h"


Parser::Parser(const Lexer &lexer)
    : m_Lexer(lexer)
{

    registerPrefix(Token::IDENT, &Parser::parseIdentifier);
    registerPrefix(Token::NUMBER, &Parser::parseNumberLiteral);
    registerPrefix(Token::MINUS, &Parser::parsePrefixExpression);
    registerPrefix(Token::LPAREN, &Parser::parseGroupedExpression);

    registerInfix(Token::PLUS, &Parser::parseInfixExpression);
    registerInfix(Token::MINUS, &Parser::parseInfixExpression);
    registerInfix(Token::SLASH, &Parser::parseInfixExpression);
    registerInfix(Token::ASTERISK, &Parser::parseInfixExpression);

    nextToken();
    nextToken();
}

void Parser::nextToken()
{
    curToken = peekToken;
    peekToken = m_Lexer.NextToken();
}

bool Parser::expectPeek(Token::Type t)
{
    if(peekTokenIs(t)) {
        nextToken();
        return true;
    } else {
        peekError();
        return false;
    }
}

void Parser::peekError()
{
    string msg{"expected next token to be " + curToken.literal() + ", got " + peekToken.literal() + " instead"};
    m_Errors.push_back(msg);
}

void Parser::noPrefixParseFnError()
{
    string msg{"no prefix parse function for " + curToken.literal() + " found"};
    m_Errors.push_back(msg);
}

Expression* Parser::parseExpression(Parser::Priority precedence)
{
    prefixParseFn prefix = prefixParseFns[curToken.type()];
    if(prefix == nullptr)
        return nullptr;

    Expression* leftExp = (this->*prefix)();

    while(precedence < peekPrecedence()) {
        infixParseFn infix = infixParseFns[peekToken.type()];
        if(infix == nullptr)
            return leftExp;

        nextToken();
        leftExp = (this->*infix)(leftExp);
    }
    return leftExp;
}

Parser::Priority Parser::peekPrecedence() const
{
    Token::Type t = peekToken.type();
    if(precedences.count(t))
        return precedences.at(t);

    return LOWEST;

}

Parser::Priority Parser::curPrecedence() const
{
    Token::Type t = curToken.type();
    if(precedences.count(t))
        return precedences.at(t);

    return LOWEST;
}

Expression *Parser::parseNumberLiteral()
{
    string txt = curToken.literal();
    try
    {
        double value = stod(txt);
        NumberLiteral * lit = new NumberLiteral();
        lit->setToken(curToken);
        lit->setValue(value);
        return lit;
    }
    catch(const exception& e)
    {
        string msg{"could not parse " + txt + " as integer"};
        m_Errors.push_back(msg);
        return nullptr;
    }
}



Expression * Parser::parsePrefixExpression()
{
    PrefixExpression * expression = new PrefixExpression();
    expression->setToken(curToken);

    nextToken();

    Expression *right = parseExpression(PREFIX);
    expression->setRight(right);

    return expression;
}

Expression *Parser::parseInfixExpression(Expression *left)
{
    InfixExpression *expression = new InfixExpression();
    expression->setToken(curToken);
    expression->setLeft(left);

    Priority precedence = curPrecedence();
    nextToken();
    Expression *right = parseExpression(precedence);
    expression->setRight(right);

    return expression;
}

Expression *Parser::parseGroupedExpression()
{
    nextToken();

    Expression *exp = parseExpression(LOWEST);
    if(!(expectPeek(Token::RPAREN)))
        return nullptr;
    return exp;
}
