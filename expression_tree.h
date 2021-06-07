#ifndef __EXPRESSION_TREE_H__
#define __EXPRESSION_TREE_H__

#include<algorithm>
#include<string>
#include<sstream>
#include<vector>
#include "list.h"
using namespace std;

class ExpressionBtree
{
    struct TreeNode
    {
        string key;
        TreeNode *left = nullptr;
        TreeNode *right = nullptr;
        TreeNode(string _key="")
        {
            key = _key;
        }
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
};

ExpressionBtree::ExpressionBtree(string exp)
{
    exp.erase(remove(exp.begin(),exp.end(),' '),exp.end());
    cout<<exp<<endl;
    cout<<exp.length()<<endl;
    if(exp.length()> 0)
    {

        string buf;
        stringstream ss(exp);
        vector<string> tokens;
        while (ss >> buf)
        {
            tokens.push_back(buf);
        }

        List<TreeNode*> parents;
        root = new TreeNode();
        TreeNode *currentNode = root;
        parents.pushFront(currentNode);

        for(size_t i=0 ; i<tokens.size(); i++)
        {
            string token = tokens[i];
            //Se inserta un nodo por la izquierda
            if(token == "(")
            {
                TreeNode *newNode = new TreeNode();
                if(currentNode->left != NULL)
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
                if(currentNode->right != NULL)
                {
                    newNode->right = currentNode->right;
                }
                currentNode->right = newNode;
                parents.pushFront(currentNode);
                currentNode = newNode;
            }
        }
    }

}


void ExpressionBtree::_inOrder(TreeNode* node)
{
    if(node != NULL)
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


#endif // __EXPRESSION_TREE_H__
