#ifndef __EXPRESSION_TREE_H__
#define __EXPRESSION_TREE_H__

#include<algorithm>
#include<string>
#include<regex>
#include "util.h"
#include "stack.h"
#include "operator.h"
using std::string;
using std::cout;
using std::cerr;
using std::sregex_token_iterator;
using std::to_string;
using std::stoi;

typedef sregex_token_iterator TokenIterator;

class ExpressionBtree
{
    struct TreeNode
    {
        string key;
        TreeNode *left = nullptr;
        TreeNode *right = nullptr;
        TreeNode(string _key=""):key(_key) {}
        string getKey()
        {
            return key;
        }
        void setKey(string _key)
        {
            key = _key;
        };
    };
public:
    ExpressionBtree(string exp);
    void inOrder();
    string evaluate();
private:
    TreeNode *root = nullptr;
    void _inOrder(TreeNode *_root);
    string _evaluate(TreeNode *node);
    sregex_token_iterator getTokens(string &expression);
    void clearExpression(string &exp);
    bool validateExpression(string exp);
};

ExpressionBtree::ExpressionBtree(string exp)
{
    try
    {
        clearExpression(exp);
        cout<<exp<<endl;
        if(exp.size())
        {
            Stack<TreeNode*> parents;
            root = new TreeNode();
            TreeNode *currentNode = root;
            parents.push(currentNode);

            regex rgx("[\\+\\-\\*\\/\\(\\)]|([0-9]+(\\.[0-9]+)*)");

            TokenIterator iter(exp.begin(), exp.end(), rgx);
            TokenIterator end;

            for(; iter!= end; ++iter)
            {
                string token = *iter;
                //Se inserta un nodo por la izquierda
                if(token == "(")
                {
                    TreeNode *newNode = new TreeNode();
                    if(currentNode->left)
                    {
                        newNode->left = currentNode->left;
                    }
                    currentNode->left = newNode;

                    parents.pushFront(currentNode);
                    currentNode = newNode;
                }
                //Se setea el valor en el nodo actual y se inserta un nodo por la derecha
                else if(token == "+" || token == "-" || token == "*" || token == "/")
                {
                    currentNode->setKey(token);
                    TreeNode *newNode = new TreeNode();
                    if(currentNode->right)
                    {
                        newNode->right = currentNode->right;
                    }
                    currentNode->right = newNode;
                    parents.pushFront(currentNode);
                    currentNode = newNode;
                }
                else if(token == ")")
                {
                    currentNode = parents.pop();

                }
                else if(isNumber(token))
                {
                    currentNode ->setKey(token);
                    currentNode = parents.pop();
                }
                else
                {
                    throw "Invalid expression";
                }
            }
        }
        else
        {
            throw "Empty expression";
        }
    }
    catch(string error)
    {
        cerr<<error<<endl;
    }

}


void ExpressionBtree::_inOrder(TreeNode* node)
{
    if(node)
    {
        _inOrder(node->left);
        cout<<node->getKey()<<" ";
        _inOrder(node->right);
    }
}

void ExpressionBtree::inOrder()
{
    _inOrder(root);
    cout<<endl;
}

string ExpressionBtree::_evaluate(TreeNode *node)
{
    TreeNode *leftNode = node->left;
    TreeNode *rightNode = node->right;
    if(leftNode && rightNode)
    {
        int resultLeft = stoi(_evaluate(leftNode));
        int resultRight = stoi(_evaluate(rightNode));
        int resultado = operatorMap[node->getKey()](resultLeft, resultRight);
        return to_string(resultado);
    }
    else
    {
        return node->getKey();
    }
}

string ExpressionBtree::evaluate()
{
    return _evaluate(root);
}

sregex_token_iterator ExpressionBtree::getTokens(string &expr)
{
    regex rgx("[\\+\\-\\*\\/\\(\\)]|([0-9]+(\\.[0-9]+)*)");

    return sregex_token_iterator(expr.begin(), expr.end(), rgx);
}

void ExpressionBtree::clearExpression(string &exp)
{
    //Se elimina los espacios en blanco
    exp.erase(remove(exp.begin(),exp.end(),' '),exp.end());
}


#endif // __EXPRESSION_TREE_H__
