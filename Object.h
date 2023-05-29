#pragma once

#include <string>
using namespace std;

class Object
{
public:
    enum Type // 类型
    {
        NULL_OBJ  , //
        ERROR_OBJ , //
        NUMBER_OBJ ,
    };
    static string type2name(Type type) ;

public:
    virtual Type type() const = 0;
    virtual string Inspect() const  = 0;
};

class Number : public Object
{
public:
    Number(double value = 0.0);
    virtual Type type() const override;
    virtual string Inspect()  const override;

    inline double value() const {return m_Value;}
private:
    double m_Value;
};


class Null : public Object
{
public:
    virtual Type type() const override;
    virtual string Inspect()  const override;
};

class Error : public Object
{
public:
    Error(const string &message = "");
    virtual Type type() const override;
    virtual string Inspect()  const override;
private:
    string m_Message;
};
