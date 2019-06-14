#ifndef AST_H
#define AST_H

#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace std;

struct Node {
  int type;
  string name;
  string value;
  vector<Node *> children;
};

Node *addNode(string name, string value);
Node *addNode(string name);
void generateGraphViz(Node *n, string parent, string side);
void print_assign(Node *n, string parent, string side);
void print_block(Node *n, string parent, string side);
void print_if(Node *n, string parent, string side);
void print_elif(Node *n, string parent, string side);
void print_else(Node *n, string parent, string side);
void print_while(Node *n, string parent, string side);
void print_break(Node *n, string parent, string side);
void print_terminal(Node *n, string parent, string side);
void printTree(Node *n, string parent, string side);

#endif
