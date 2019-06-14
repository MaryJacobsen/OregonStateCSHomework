#include <iostream>
#include "parser.hpp"
#include "ast.h"

using namespace std;

extern int yylex();
extern Node *root;

int main() {
  if (!yylex()) {
    cout << "digraph G {" << endl;
    printTree(root, "n0", "");
    cout << "}" << endl;
  }
}
