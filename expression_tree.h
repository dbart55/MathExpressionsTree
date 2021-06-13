#ifndef __EXPRESSION_TREE_H__
#define __EXPRESSION_TREE_H__

#include<algorithm>
#include<string>
#include "util.h"
#include "stack.h"
using std::string;
using std::cout;
using std::cerr;

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
    int evaluate();
private:
    TreeNode *root = nullptr;
    void _inOrder(TreeNode *_root);
    List<string> getTokens(string expression);
    void clearExpression(string &exp);
    bool validateExpression(string exp);
};

ExpressionBtree::ExpressionBtree(string exp)
{
    try
    {
        clearExpression(exp);
        cout<<exp<<endl;
        if(validateExpression(exp))
        {
            List<string> tokens = getTokens(exp);
            Stack<TreeNode*> parents;
            root = new TreeNode();
            TreeNode *currentNode = root;
            parents.push(currentNode);

            auto it = tokens.getIterator();
            while(it.hasNext())
            {
                string token = it.next();
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
            }
        }
        else
        {
            throw "Invalid expression";
        }
    }
    catch(string error)
    {
        cerr<<error<<endl;
    }

}


void ExpressionBtree::_inOrder(TreeNode* node)
{
    if(!node)
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

int ExpressionBtree::evaluate()
{
    return 0;
}

List<string> ExpressionBtree::getTokens(string expr)
{
    List<string> tokens;
    return tokens;
}

void ExpressionBtree::clearExpression(string &exp)
{
    //Se elimina los espacios en blanco
    exp.erase(remove(exp.begin(),exp.end(),' '),exp.end());
}

bool ExpressionBtree::validateExpression(string exp)
{
    bool validate = true;

    return validate;
}




#endif // __EXPRESSION_TREE_H__
