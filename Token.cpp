
#include "Token.h"

Token::Token(Type type, const string &literal)
    : m_Type(type)
    , m_Literal(literal)
{
}

Token::Token(const Token &token)
{
    m_Type = token.type();
    m_Literal = token.literal();
}

Token &Token::operator=(const Token &token)
{
    m_Type = token.type();
    m_Literal = token.literal();
    return *this;
}
