#pragma once

#include <string>
using namespace std;

// 词法分析中的最小单元
// 标记
class Token
{
public:
    enum Type // 标记类型
    {
        ILLEGAL, // 未知词法单元

        EOF0, // 字符串表达式结尾

        IDENT,  // 标识符，add, foobar, x, y, ...
        NUMBER, // 数值，1343456, 0.258, ...

        // 运算符
        PLUS,     // "+"
        MINUS,    // "-"
        ASTERISK, // "*"
        SLASH,    // "/"

        //括号
        LPAREN,   // "("
        RPAREN,   // ")"

    };
    Token(Type type = ILLEGAL, const string &literal = "");
    Token(const Token &token);
    Token &operator=(const Token &token);

    static string type2name(Type type) ;

public:
    inline Type type() const
    {
        return m_Type;
    }
    inline const string &literal() const
    {
        return m_Literal;
    }

private:
    Type m_Type;      // 标记类型
    string m_Literal; // 标记字面量
};
