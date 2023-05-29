#pragma once

#include <unordered_map>
#include <string>
using namespace std;

#include "Object.h"
#include "Ast.h"
#include "Environment.h"

class Evaluator
{
public:
    Object *Eval(Expression *exp, Environment *env = nullptr);

    Object *evalPrefixExpression(const string &operat, Object *right);
    Object *evalMinusPrefixOperatorExpression(Object *right);

    Object *evalInfixExpression(const string &operat, Object *left, Object *right);

    Object *evalIdentifier(Identifier *exp, Environment *env);
    Object *evalNumberInfixExpression(const string &operat, Object *left, Object *right);

    inline bool isError(Object *obj) const {return obj->type() == Object::NULL_OBJ;}

private:

};
