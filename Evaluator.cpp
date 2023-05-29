#include "Evaluator.h"


Object *Evaluator::Eval(Expression *exp, Environment *env)
{
    switch (exp->type()) {
    case Expression::NUMBER:
        return new Number(static_cast<NumberLiteral *>(exp)->value());
    case Expression::PREFIX:
    {
        PrefixExpression *node = static_cast<PrefixExpression *>(exp);
        Object *right = Eval(node->right(), env);
        if(isError(right))
            return right;
        return evalPrefixExpression(node->token().literal(), right);
    }
    case Expression::INFIX:
    {
        InfixExpression *node = static_cast<InfixExpression *>(exp);
        Object *left = Eval(node->left(), env);
        if(isError(left))
            return left;
        Object *right = Eval(node->right(), env);
        if(isError(right))
            return right;
        return evalInfixExpression(node->token().literal(), left, right);
    }
    case Expression::IDENTIFIER:
        return evalIdentifier(static_cast<Identifier *>(exp), env);
    default:
        return nullptr;
    }
}

Object *Evaluator::evalPrefixExpression(const string &operat, Object *right)
{
    if(operat == "-"){
        return evalMinusPrefixOperatorExpression(right);
    }else{
        return new Error{"unknown operator:" + operat};
    }
}

Object *Evaluator::evalMinusPrefixOperatorExpression(Object *right)
{
    if(right->type() != Object::NUMBER_OBJ)
        return new Error{"unknown operator:"};

    return new Number(-static_cast<Number *>(right)->value());
}

Object *Evaluator::evalInfixExpression(const string &operat, Object *left, Object *right)
{
    if(left->type() == Object::NUMBER_OBJ && right->type() == Object::NUMBER_OBJ)
        return evalNumberInfixExpression(operat, left, right);
    return new Error{"unknown operator:"};
}

Object *Evaluator::evalIdentifier(Identifier *exp, Environment *env)
{
    const string &str = exp->token().literal();
    if(env == nullptr)
        return new Error{"identifier not found: " + str};

    Object *obj = env->Get(str);
    if(obj == nullptr)
        return new Error{"identifier not found: " + str};
    return obj;
}

Object *Evaluator::evalNumberInfixExpression(const string &operat, Object *left, Object *right)
{
    double leftVal = static_cast<Number *>(left)->value();
    double rightVal = static_cast<Number *>(right)->value();


    if(operat == "+") {
        return new Number(leftVal + rightVal);
    } else if(operat == "-") {
        return new Number(leftVal - rightVal);
    }else if(operat == "*") {
        return new Number(leftVal * rightVal);
    }else if(operat == "/") {
        return new Number(leftVal / rightVal);
    }
    else {
        return new Error{"identifier not found: " };
    }
}
