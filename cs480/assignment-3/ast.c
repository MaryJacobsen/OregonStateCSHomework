#include "ast.h"

Node *addNode(string name, string value) {
  Node *temp = new Node;
  temp->name = name;
  boost::erase_all(value, ".0");
  temp->value = value;
  return temp;
}

Node *addNode(string name) {
  Node *temp = new Node;
  temp->name = name;
  return temp;
}

void print_assign(Node *n, string parent, string side) {
  string child = parent + side;
  if(parent != child) {
    cout << " " << parent << " -> " << child << ";" << endl;
  }
  cout << "  " << child << " [label=\""<< n->name << "\"];" << endl;
  generateGraphViz(n->children[0], child, "_lhs"); //left child
  generateGraphViz(n->children[1], child, "_rhs"); //right child
}

void print_block(Node *n, string parent, string side){
  string unique_name = parent + side;
  if (parent.compare("n0") != 0 && (parent != unique_name)) {
    cout << "  " << parent << " -> " << unique_name << ";" << endl;
  }
  cout << "  " << unique_name << " [label=\"Block\"];" << endl;
  for (int i=0; i < n->children.size(); i++) {
    string child = unique_name + "_" + to_string(i);
    cout << "  " << unique_name << " -> " << child << ";" << endl;
    generateGraphViz(n->children[i], child, "");
  }
}

void print_if(Node *n, string parent, string side){
  string child = parent + side;
  cout << "  " << child << " [label=\"If\"];" << endl;
  generateGraphViz(n->children[0], child, "_cond");
  for (int i = 1; i < n->children.size(); i++) {
    generateGraphViz(n->children[i], child, "_if");
  }
}

void print_elif(Node *n, string parent, string side){
  string child = parent + side;
  cout << "  " << child << " [label=\"Elif\"];" << endl;
  generateGraphViz(n->children[0], child, "_cond");
  for (int i=1; i < n->children.size(); i++) {
    generateGraphViz(n->children[i], child, "_elif");
  }
}

void print_else(Node *n, string parent, string side){
  string unique_name = parent + "_else";
  cout << "  " << parent << " -> " << unique_name << ";" << endl;
  generateGraphViz(n->children[0], unique_name, "");
}

void print_while(Node *n, string parent, string side){
  string child = parent + side;
  cout << "  " << child << " [label=\"While\"];" << endl;
  generateGraphViz(n->children[0], child, "_cond");
  for (int i=1; i < n->children.size(); i++)
  {
    generateGraphViz(n->children[i], child, "_while");
  }
}

void print_break(Node *n, string parent, string side){
  string unique_name = parent + side;
  if(parent != unique_name) {
    cout << "  " << parent << " -> " << unique_name << ";" << endl;
    cout << "  " << unique_name << " [label=\"Break\"];" << endl;
  }
}

void print_terminal(Node *n, string parent, string side) {
  string unique_name = parent + side;
  if (parent != unique_name){
    cout << "  " << parent << " -> " << unique_name << ";" << endl;
  }
  cout << "  " << unique_name << " [shape=box,label=\"" << n->name << n->value << "\"];" << endl;
}

void generateGraphViz(Node *n, string parent, string side) {
  if(n != NULL) {
    if(n->type == 0) {
      print_assign(n, parent, side);
    }
    else if(n->type == 1 && n->children.size() == 2) {
      print_assign(n, parent, side);
    }
    else if(n->type == 2) {
      print_block(n, parent, side);
    }
    else if(n->type == 3) {
      print_assign(n, parent, side);
    }
    else if(n->type == 4) {
      print_if(n, parent, side);
    }
    else if(n->type == 5) {
      print_elif(n, parent, side);
    }
    else if(n->type == 6) {
      print_else(n, parent, side);
    }
    else if(n->type == 7) {
      print_while(n, parent, side);
    }
    else if(n->type == 8) {
      print_break(n, parent, side);
    }
    else if(n->children.size() == 0) {
      print_terminal(n, parent, side);
    }
  }
}

void printTree(Node * n, string parent, string side)
{
    if (n != NULL) {
        string child = "";
        //assignment
        if (n->type == 0 && (n->children.size() == 2)) {
            //print_assign(n, parent, side);
            child = parent + side;
            if (parent != child) {
              cout << "  " << parent << " -> " << child << ";" << endl;
            }
            cout << "  " << child << " [label=\""<< n->name << "\"];" << endl;
            printTree(n->children[0], child, "_lhs");
            printTree(n->children[1], child, "_rhs");
        }
        //if
        else if (n->type == 1) {
            child = parent + side;
            cout << "  " << child << " [label=\"If\"];" << endl;
            printTree(n->children[0], child, "_cond");
            int i;
            for (i = 1; i < n->children.size(); i++) {
                printTree(n->children[i], child, "_if");
            }
        }
        //terminal
        else if (n->children.size() == 0) {
            string this_name = parent + side;
            if (parent != this_name) {
                cout << "  " << parent << " -> " << this_name << ";" << endl;
            }
            if (n->type != 7) {
                cout << "  " << this_name << " [shape=box,label=\"" << n->name << n->value << "\"];" << endl;
            }
            else {
                cout << "  " << this_name << " [label=\"Break\"];" << endl;
            }
        }
        //block
        else if (n->type == 4) {
            string this_name = parent + side;
            if (parent.compare("n0") != 0 && (parent != this_name)) {
                cout << "  " << parent << " -> " << this_name << ";" << endl;
            }
            cout << "  " << this_name << " [label=\"Block\"];" << endl;
            int i;
            for (i = 0; i < n->children.size(); i++) {
                child = this_name + "_" + to_string(i);
                cout << "  " << this_name << " -> " << child << ";" << endl;
                printTree(n->children[i], child, "");
            }
        }
        //else
        else if (n->type == 5 && n->children.size() == 1) {
            string this_name = parent + "_else";
            cout << "  " << parent << " -> " << this_name << ";" << endl;
            printTree(n->children[0], this_name, "");
        }
        //while
        else if (n->type == 6) {
            child = parent + side;
            cout << "  " << child << " [label=\"While\"];" << endl;
            printTree(n->children[0], child, "_cond");
            int i;
            for (i = 1; i < n->children.size(); i++) {
                printTree(n->children[i], child, "_while");
            }
        }
    }
}
