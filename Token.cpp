#include <unordered_map>
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

string Token::type2name(Token::Type type)
{
    static unordered_map<Type, string> names{
        {ILLEGAL, "ILLEGAL"},
        {EOF0, "EOF"},
        {IDENT, "IDENT"},
        {PLUS, "+"},
        {MINUS, "-"},
        {ASTERISK, "*"},
        {SLASH, "/"},
        {LPAREN, "("},
        {RPAREN, ")"},
    };
    if(names.count(type))
        return names[type];

    return "none";
}
