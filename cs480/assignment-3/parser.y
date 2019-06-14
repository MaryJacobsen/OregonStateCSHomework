%{
#include <iostream>
#include <set>

#include "parser.hpp"
#include "ast.h"

extern int yylex();
void yyerror(YYLTYPE* loc, const char* err);
std::string* translate_boolean_str(std::string* boolean_str);

/*
 * Here, target_program is a string that will hold the target program being
 * generated, and symbols is a simple symbol table.
*/
//std::string* target_program;
//std::set<std::string> symbols

Node *root = addNode("Block");
%}

%code requires{
#include "ast.h"
}

/* Enable location tracking. */
%locations

/*
 * Because the lexer can generate more than one token at a time (i.e. DEDENT
 * tokens), we'll use a push parser.
 */
%define api.pure full
%define api.push-pull push

%union {
  std::string* str;
  Node *nodes;
  vector<Node*> *children;
}

/*
 * These are all of the terminals in our grammar, i.e. the syntactic
 * categories that can be recognized by the lexer.
 */
%token <str> IDENTIFIER FLOAT INTEGER TRUE FALSE
%token <nodes> INDENT DEDENT NEWLINE
%token <nodes> AND BREAK DEF ELIF ELSE FOR IF NOT OR RETURN WHILE
%token <nodes> ASSIGN PLUS MINUS TIMES DIVIDEDBY
%token <nodes> EQ NEQ GT GTE LT LTE
%token <nodes> LPAREN RPAREN COMMA COLON

/*
 * Here, we're defining the precedence of the operators.  The ones that appear
 * later have higher precedence.  All of the operators are left-associative
 * except the "not" operator, which is right-associative.
 */
%left OR
%left AND
%left PLUS MINUS
%left TIMES DIVIDEDBY
%left EQ NEQ GT GTE LT LTE
%right NOT

%type <children> statements
%type <nodes> statement primary_expression negated_expression
%type <nodes> expression assign_statement block condition
%type <nodes> if_statement elif_blocks else_block
%type <nodes> while_statement break_statement

/* This is our goal/start symbol. */
%start program

%%

/*
 * Each of the CFG rules below recognizes a particular program construct in
 * Python and creates a new string containing the corresponding C/C++
 * translation.  Since we're allocating strings as we go, we also free them
 * as we no longer need them.  Specifically, each string is freed after it is
 * combined into a larger string.
 */

program
  : statements { root->children = *$1; root->type = 4; }
  ;

statements
  : statement { $$ = new vector <Node*> ({$1}); }
  | statements statement { $1->push_back($2); $$ = $1; }
  ;

statement
  : assign_statement { $$ = $1; }
  | if_statement { $$ = $1; }
  | while_statement { $$ = $1; }
  | break_statement { $$ = $1; }
  ;

primary_expression
  : IDENTIFIER { Node *n = addNode("Identifier: ", *$1); $$ = n; }
  | FLOAT { Node *n = addNode("Float: ", *$1); $$ = n; }
  | INTEGER { Node *n = addNode("Integer: ", *$1); $$ = n; }
  | TRUE { Node *n = addNode("Boolean: ", "1"); $$ = n; }
  | FALSE { Node *n = addNode("Boolean: ", "0"); $$ = n; }
  | LPAREN expression RPAREN { $$ = $2; }
  ;

negated_expression
  : NOT primary_expression { }
  ;

expression
  : primary_expression { $$ = $1; }
  | negated_expression { $$ = $1; }
  | expression PLUS expression {
                                 Node *plus = addNode("PLUS");
                                 plus->children.push_back($1);
                                 plus->children.push_back($3);
                                 $$ = plus;
                               }
  | expression MINUS expression {
                                  Node *minus = addNode("MINUS");
                                  minus->children.push_back($1);
                                  minus->children.push_back($3);
                                  $$ = minus;
                                }
  | expression TIMES expression {
                                  Node *times = addNode("TIMES");
                                  times->children.push_back($1);
                                  times->children.push_back($3);
                                  $$ = times;
                                }
  | expression DIVIDEDBY expression {
                                      Node *div = addNode("DIVIDEDBY");
                                      div->children.push_back($1);
                                      div->children.push_back($3);
                                      $$ = div;
                                    }
  | expression EQ expression {
                               Node *eq = addNode("EQ");
                               eq->children.push_back($1);
                               eq->children.push_back($3);
                               $$ = eq;
                             }
  | expression NEQ expression {
                                Node *neq = addNode("NEQ");
                                neq->children.push_back($1);
                                neq->children.push_back($3);
                                $$ = neq;
                              }
  | expression GT expression {
                               Node *gt = addNode("GT");
                               gt->children.push_back($1);
                               gt->children.push_back($3);
                               $$ = gt;
                             }
  | expression GTE expression {
                                Node *gte = addNode("GTE");
                                gte->children.push_back($1);
                                gte->children.push_back($3);
                                $$ = gte;
                              }
  | expression LT expression {
                               Node *lt = addNode("LT");
                               lt->children.push_back($1);
                               lt->children.push_back($3);
                               $$ = lt;
                             }
  | expression LTE expression {
                                Node *lte = addNode("LTE");
                                lte->children.push_back($1);
                                lte->children.push_back($3);
                                $$ = lte;
                              }
  ;

assign_statement
  : IDENTIFIER ASSIGN expression NEWLINE {
                                           Node *assign = addNode("Assignment");
                                           Node *id = addNode("Identifier: ", *$1);
                                           assign->type = 0;
                                           assign->children.push_back(id);
                                           assign->children.push_back($3);
                                           $$ = assign;
                                         }
  ;

block
  : INDENT statements DEDENT {
                                Node *block = addNode("Block");
                                block->type = 4;
                                block->children = *$2;
                                $$ = block;
                             }
  ;

condition
  : expression { $$ = $1; }
  | condition AND condition {
                               Node *a = addNode("And");
                               a->children.push_back($1);
                               a->children.push_back($3);
                               $$ = a;
                            }
  | condition OR condition {
                               Node *o = addNode("Or");
                               o->children.push_back($1);
                               o->children.push_back($3);
                               $$ = o;
                            }
  ;

if_statement
  : IF condition COLON NEWLINE block elif_blocks else_block {
                                                              Node *i = addNode("If");
                                                              i->type = 1;
                                                              i->children.push_back($2);
                                                              i->children.push_back($5);
                                                              i->children.push_back($6);
                                                              i->children.push_back($7);
                                                              $$ = i;
                                                            }
  ;

elif_blocks
  : %empty { $$ = NULL; }
  | elif_blocks ELIF condition COLON NEWLINE block {
                                                      Node *elif = addNode("Elif");
                                                      elif->children.push_back($1);
                                                      elif->children.push_back($3);
                                                      elif->children.push_back($6);
                                                      $$ = elif;
                                                   }
  ;

else_block
  : %empty { $$ = NULL; }
  | ELSE COLON NEWLINE block {
                               Node *e = addNode("Else");
                               e->type = 5;
                               e->children.push_back($4);
                               $$ = e;
                             }
;

while_statement
  : WHILE condition COLON NEWLINE block {
                                          Node *w = addNode("While");
                                          w->type = 6;
                                          w->children.push_back($2);
                                          w->children.push_back($5);
                                          $$ = w;
                                        }
  ;

break_statement
  : BREAK NEWLINE {
                    Node *b = addNode("Break");
                    b->type = 7;
                    $$ = b;
                  }
  ;

%%

void yyerror(YYLTYPE* loc, const char* err) {
  std::cerr << "Error (line " << loc->first_line << "): " << err << std::endl;
}

/*
 * This function translates a Python boolean value into the corresponding
 * C++ boolean value.
 */
std::string* translate_boolean_str(std::string* boolean_str) {
  if (*boolean_str == "True") {
    return new std::string("true");
  } else {
    return new std::string("false");
  }
}
