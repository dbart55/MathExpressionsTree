#include <iostream>
#include "expression_tree.h"

using namespace std;

int main()
{
    ExpressionBtree *tree = new ExpressionBtree("(( 7 +3) *    ( 5-  2))");
    tree->inOrder();
    string resultado = tree->evaluate();
    cout<<resultado<<endl;
    return 0;
}
