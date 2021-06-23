#include <iostream>
#include "expression_tree.h"
#include <string.h>
using namespace std;

int main()
{

    cout<<"Ingrese una expresion matematica:"<<endl;
    string s;
    getline(cin, s);
    cout<<s<<endl;
    ExpressionTree *tree = new ExpressionTree(s.c_str());
    int resultado = tree->evaluate();
    cout<<"Resultado: "<<resultado<<endl;

    cout<<"Notacion Infija:"<<endl;
    tree->recorridoInorden();
    cout<<"Notacion Prefija:"<<endl;
    tree->recorridoPreOrden();
    cout<<"Notacion Postfija:"<<endl;
    tree->recorridoPostOrden();
    return 0;
}
