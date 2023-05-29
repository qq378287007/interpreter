#include "Ast.h"

Identifier::Identifier(Token token)
    : m_Token(token)
{

}

string Identifier::String()
{
    return m_Token.literal();
}

string NumberLiteral ::String()
{
    return m_Token.literal();
}

string PrefixExpression ::String()
{
    return "(" + m_Token.literal() + m_Right->String() + ")";
}

string InfixExpression ::String()
{
    return "(" + m_Left->String() + m_Token.literal() + m_Right->String() + ")";
}

