#include <unordered_map>
#include <sstream>
#include <iomanip>
#include "Object.h"

string Object::type2name(Object::Type type)
{
    static unordered_map<Type, string> names{
        {NULL_OBJ, "NULL"},
        {ERROR_OBJ, "ERROR"},
        {NUMBER_OBJ, "NUMBER"},
    };
    if(names.count(type))
        return names[type];

    return "none";
}

Number::Number(double value)
{
    m_Value = value;
}

Object::Type Number::type() const
{
    return NUMBER_OBJ;
}

string Number::Inspect() const
{
    std::stringstream ss;
    ss << std::setprecision(15) << m_Value;
    string str = ss.str();
    return  str;
}

Object::Type Null::type() const
{
    return NULL_OBJ;
}

string Null::Inspect() const
{
    return  "null";
}
Error::Error(const string &message)
    : m_Message(message)
{

}

Object::Type Error::type() const
{
    return ERROR_OBJ;
}

string Error::Inspect() const
{
    return  "Error: " + m_Message;
}
