#include "Lexer.h"

Lexer::Lexer(const string &Input)
    : m_Input(Input)
{
    m_InputSize = Input.size();
    readChar();
}

void Lexer::readChar()
{
    if (m_ReadPosition >= m_InputSize)
        m_Ch = 0;
    else
        m_Ch = m_Input[m_ReadPosition];

    m_Position = m_ReadPosition;
    m_ReadPosition += 1;
}

char Lexer::peekChar()
{
    if (m_ReadPosition >= m_InputSize)
        return 0;
    else
        return m_Input[m_ReadPosition];
}

void Lexer::skipWhitespace()
{
    while (isWhitespace(m_Ch))
        readChar();
}

string Lexer::readIdentifier()
{
    int curPos = m_Position;
    while (isLetter(m_Ch) || isDigit(m_Ch))
        readChar();
    return m_Input.substr(curPos, m_Position - curPos);
}

string Lexer::readNumber()
{
    int curPos = m_Position;
    while (isDigit(m_Ch))
        readChar();
    if(m_Ch =='.')
        readChar();
    while (isDigit(m_Ch))
        readChar();
    return m_Input.substr(curPos, m_Position - curPos);
}

Token Lexer::NextToken()
{
    skipWhitespace();

    Token tok;
    switch (m_Ch)
    {
    case '+':
        tok = Token(Token::PLUS, {m_Ch});
        break;
    case '-':
        tok = Token(Token::MINUS, {m_Ch});
        break;
    case '*':
        tok = Token(Token::ASTERISK, {m_Ch});
        break;
    case '/':
        tok = Token(Token::SLASH, {m_Ch});
        break;
    case '(':
        tok = Token(Token::LPAREN, {m_Ch});
        break;
    case ')':
        tok = Token(Token::RPAREN, {m_Ch});
        break;
    case 0:
        tok = Token(Token::EOF0, "");
        break;
    default:
    {
        if (isLetter(m_Ch))
        {
            tok = Token(Token::IDENT, readIdentifier());
            return tok;
        }
        else if (isDigit(m_Ch))
        {
            tok = Token(Token::NUMBER, readNumber());
            return tok;
        }
        else
        {
            tok = Token(Token::ILLEGAL, {m_Ch});
        }
        break;
    }
    }

    readChar();
    return tok;
}

