#include "Ast.h"

Identifier::Identifier(Token token)
    : m_Token(token)
{

}

string Identifier::String()
{
    return m_Token.literal();
}

Expression::Type Identifier::type()
{
    return Expression::IDENTIFIER;
}

string NumberLiteral ::String()
{
    return m_Token.literal();
}

Expression::Type NumberLiteral::type()
{
    return Expression::NUMBER;
}

string PrefixExpression ::String()
{
    return "(" + m_Token.literal() + m_Right->String() + ")";
}

Expression::Type PrefixExpression::type()
{
    return Expression::PREFIX;
}

string InfixExpression ::String()
{
    return "(" + m_Left->String() + m_Token.literal() + m_Right->String() + ")";
}

Expression::Type InfixExpression::type()
{
    return Expression::INFIX;
}

