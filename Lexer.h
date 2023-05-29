#pragma once

#include "Token.h"

class Lexer
{
public:
    explicit Lexer(const string &Input = "");

    void readChar();
    char peekChar();
    void skipWhitespace();
    string readIdentifier();
    string readNumber();
    Token NextToken();

private:
    inline bool isLetter(char ch) const
    {
        return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == '_';
    }

    inline bool isDigit(char ch) const
    {
        return '0' <= ch && ch <= '9';
    }

    inline bool isWhitespace(char ch) const
    {
        return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
    }
private:
    string m_Input;        // 输入字符串
    int m_Position;        // 当前字符位置
    int m_ReadPosition{0}; // 下一个字符位置
    char m_Ch;             // 当前字符

    int m_InputSize;       // 字符串长度
};
