#include "Environment.h"


Environment::Environment(Environment *out)
{
    outer = out;
}

Object *Environment::Get(const string &name) const
{
    Object *obj = store.at(name);
    if(obj != nullptr && outer != nullptr)
        return outer->Get(name);
    return obj;
}

void Environment::Set(const string &name, Object *val)
{
    store[name] = val;
}
