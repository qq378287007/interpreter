#pragma once

#include "Lexer.h"

// 表达式
class Expression
{
public:
    virtual string String() = 0;
    virtual ~Expression() = default;
};

// 标识符
class Identifier : public Expression
{
public:
    explicit Identifier(Token token);
    virtual string String() override;

private:
    Token m_Token;
};

// 数值字面量
class NumberLiteral : public Expression
{
public:
    virtual string String() override;

    inline void setToken(Token token){m_Token=token;}
    inline void setValue(double value){m_Value=value;}
private:
    Token m_Token;
    double m_Value;
};

// 前缀表达式
class PrefixExpression : public Expression
{
public:
    virtual string String() override;

    inline void setToken(Token token){m_Token=token;}
    inline void setRight(Expression *right){m_Right=right;}
private:
    Token m_Token;
    Expression *m_Right{nullptr};
};

// 中缀表达式
class InfixExpression : public Expression
{
public:
    virtual string String() override;

    inline void setToken(Token token){m_Token=token;}
    inline void setLeft(Expression *left){m_Left=left;}
    inline void setRight(Expression *right){m_Right=right;}
private:
    Token m_Token;
    Expression *m_Left{nullptr};
    Expression *m_Right{nullptr};
};

