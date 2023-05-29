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
    virtual Type type() const override;
    virtual string Inspect()  const override;
private:
    double value;
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
    virtual Type type() const override;
    virtual string Inspect()  const override;
private:
    string message;
};
