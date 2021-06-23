#ifndef ___EXPRESSION_H__
#define ___EXPRESSION_H__
#include "operator.h"
using std::string;

class Expression
{
public:
    Expression* left;
    Expression* right;
    Expression(Expression* left_=nullptr, Expression* right_=nullptr):left(left_), right(right_) {}
    virtual ~Expression() {};
    virtual string toString() const = 0;
    virtual int evaluate() const = 0;
};


class NumberExpression : public Expression
{
public:
    int value;
    NumberExpression(const int value_):Expression(), value(value_) {}
    string toString()
    const
    {
        return std::to_string(value);
    }
    int evaluate() const
    {
        return value;
    }
};

class BinaryExpression : public Expression
{
public:
    char operator_;
    BinaryExpression(const char oper, Expression* const left_ = 0, Expression* const right_ = 0):Expression(left_, right_), operator_(oper) {}
    string toString()
    const
    {
        return string{operator_};
    }

    int evaluate() const
    {
        if(operatorMap.count(operator_) > 0)
        {
            return operatorMap[operator_](left->evaluate(), right->evaluate());
        }
        return 0;
    }
};

class ExpressionTree
{
public:
    const int evaluate();
    ExpressionTree(const char*);
    void recorridoInorden();
    void recorridoPostOrden();
    void recorridoPreOrden();
private:
    const Expression* root;
    const Expression* buildTree(const char*&);
    Expression* parseNumero(const char*&);
    Expression* parseParentesis(const char*&);
    Expression* parseSumandos(const char*&);
    Expression* parseFactores(const char*&);
    void inorden(const Expression*);
    void postorden(const Expression*);
    void preorden(const Expression*);
};

const Expression* ExpressionTree::buildTree(const char*&s)
{
    return parseSumandos(s);
}

ExpressionTree::ExpressionTree(const char* input)
{
    root = buildTree(input);
}
const int ExpressionTree::evaluate()
{
    return root->evaluate();
}

Expression* ExpressionTree::parseNumero(const char*& s)
{
    NumberExpression* numExpr = new NumberExpression(0);
    while(*s && std::isdigit(*s))
    {
        numExpr->value = numExpr->value* 10 + *s++ - '0';
    }
    return numExpr;
}


Expression* ExpressionTree::parseParentesis(const char*& s)
{
    if(*s == 0)
    {
        throw std::runtime_error("Error: Invalid Expression.");
    }
    else if(*s == '(')
    {
        s++;
        Expression* expr = parseSumandos(s);
        if(*s == ')')
        {
            s++;
            return expr;
        }
        throw std::runtime_error("Error: Parentesis no balanceados");
    }
    else if(std::isdigit(*s))
    {
        Expression* expr = parseNumero(s);
        return expr;
    }
    throw std::runtime_error("Error: Character invalid.");
}

Expression* ExpressionTree::parseFactores(const char*&s)
{
    Expression* left = parseParentesis(s);
    while(*s)
    {
        if(*s == '*')
        {
            s++;
            Expression* right = parseParentesis(s);
            left = new BinaryExpression('*', left, right);
            continue;

        }
        else if(*s == '/')
        {
            s++;
            Expression* right = parseParentesis(s);
            left = new BinaryExpression('/', left, right);
            continue;
        }
        return left;
    }
    return left;
}


Expression* ExpressionTree::parseSumandos(const char*& s)
{
    Expression* left = parseFactores(s);
    while(*s)
    {
        if(*s=='+')
        {
            s++;
            Expression* right = parseFactores(s);
            left = new BinaryExpression('+', left, right);
            continue;
        }
        else if(*s == '-')
        {
            s++;
            Expression* right = parseFactores(s);
            left = new BinaryExpression('-', left, right);
            continue;
        }
        return left;
    }
    return left;
}

void ExpressionTree::inorden(const Expression* expr)
{
    if(expr)
    {
        inorden(expr->left);
        std::cout<<expr->toString()<<" ";
        inorden(expr->right);
    }
}

void ExpressionTree::recorridoInorden()
{
    inorden(root);
    std::cout<<std::endl;
}

void ExpressionTree::preorden(const Expression* expr)
{
    if(expr)
    {
        std::cout<<expr->toString()<<" ";
        preorden(expr->left);
        preorden(expr->right);
    }
}

void ExpressionTree::recorridoPreOrden()
{
    preorden(root);
    std::cout<<std::endl;
}

void ExpressionTree::postorden(const Expression* expr)
{
    if(expr)
    {
        postorden(expr->left);
        postorden(expr->right);
        std::cout<<expr->toString()<<" ";

    }
}

void ExpressionTree::recorridoPostOrden()
{
    postorden(root);
    std::cout<<std::endl;
}

#endif // ___EXPRESSION_H__
