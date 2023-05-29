#pragma once

#include <unordered_map>
#include <string>
using namespace std;

#include "Object.h"

class Environment
{
public:
    Environment(Environment *out = nullptr);
    Object * Get(const string &name) const ;
    void Set(const string &name, Object *val);

private:
    unordered_map<string, Object *> store;
    Environment *outer{nullptr};
};
