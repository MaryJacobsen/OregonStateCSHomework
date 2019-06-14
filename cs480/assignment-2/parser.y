%{
#include <iostream>
#include <vector>
#include <algorithm>
#include "parser.hpp"

std::vector<std::string> identifiers;
std::vector<std::string> prog;
bool _error = false;

extern int yylex();

void yyerror(YYLTYPE* loc, const char* err) {
  std::cerr << "Error (line " << loc->first_line << "): " << err << std::endl;
}
%}

%locations
%define api.pure full
%define api.push-pull push

%union {
  std::string* str;
  int category;
}

%token <str> IDENTIFIER TRUE FALSE NUMBER
%token <category> IF ELIF ELSE AND OR WHILE BREAK
%token <category> EQUALS PLUS MINUS TIMES DIVIDEDBY NOT
%token <category> EQ NEQ GT GTE LT LTE
%token <category> LPAREN RPAREN COMMA COLON RETURN
%token <category> NEWLINE INDENT DEDENT SEMICOLON

%type <str> statement value expression conditional logic ifblock elifblock elseblock indentdedent head

%start program

%%

program: head { prog.push_back(*$1); delete $1; }

head
  : statement { $$ = $1; }
  | head statement { auto temp = new std::string(*$$ + "\n" + *$2);
                     delete $$, $1, $2;
                     $$ = temp;
                   }
  ;

statement
  : IDENTIFIER EQUALS expression NEWLINE { if(std::find(identifiers.begin(), identifiers.end(), *$1) == identifiers.end()) {
                                              identifiers.push_back(*$1);
                                           }
                                           $$ = new std::string(*$1 + " = " + *$3 + ";");
                                           delete $1, $3;
                                         }
  | conditional { $$ = $1; }
  | WHILE logic COLON NEWLINE indentdedent { $$ = new std::string("while (" + *$2 + ") {\n" + *$5 + "\n}");
                                             delete $2, $5;
                                           }
  | BREAK NEWLINE { $$ = new std::string("break;"); }
  | error SEMICOLON  { std::cerr << "Error: bad statement on line " << @1.first_line << std::endl; _error = true; }
  ;

value
  : NUMBER { $$ = $1; }
  | IDENTIFIER { $$ = $1; }
  | TRUE { $$ = new std::string("true"); }
  | FALSE { $$ = new std::string("false"); }
  | LPAREN expression RPAREN { $$ = new std::string("(" + *$2 + ")"); delete $2; }
  ;

expression
  : expression PLUS expression { $$ = new std::string(*$1 + " + " + *$3); delete $1, $3; }
  | expression MINUS expression { $$ = new std::string(*$1 + " - " + *$3); delete $1, $3; }
  | expression TIMES expression { $$ = new std::string(*$1 + " * " + *$3); delete $1, $3; }
  | expression DIVIDEDBY expression { $$ = new std::string(*$1 + " / " + *$3); delete $1, $3; }
  | value { $$ = $1; }
  ;

conditional
  : ifblock { $$ = new std::string(*$1); delete $1; }
  | ifblock elifblock { $$ = new std::string(*$1 + *$2); delete $1, $2; }
  | ifblock elseblock { $$ = new std::string(*$1 + *$2); delete $1, $2; }
  | ifblock elifblock elseblock { $$ = new std::string(*$1 + *$2 + *$3); delete $1, $2, $3; }
  ;

logic
  : NOT logic { $$ = new std::string("!" + *$2); delete $2; }
  | logic AND logic { $$ = new std::string(*$1 + " && " + *$3); delete $1, $3; }
  | logic OR logic { $$ = new std::string(*$1 + " || " + *$3); delete $1, $3; }
  | logic EQ logic { $$ = new std::string(*$1 + " == " + *$3); delete $1, $3; }
  | logic NEQ logic { $$ = new std::string(*$1 + " != " + *$3); delete $1, $3; }
  | logic LT logic { $$ = new std::string(*$1 + " < " + *$3); delete $1, $3; }
  | logic LTE logic { $$ = new std::string(*$1 + " <= " + *$3); delete $1, $3; }
  | logic GT logic { $$ = new std::string(*$1 + " > " + *$3); delete $1, $3; }
  | logic GTE logic { $$ = new std::string(*$1 + " >= " + *$3); delete $1, $3; }
  | value { $$ = $1; }
  ;

ifblock
  : IF logic COLON NEWLINE indentdedent { $$ = new std::string("if (" + *$2 + ") {\n" + *$5 + "\n}"); delete $2, $5; }
  ;

elifblock
  : ELIF logic COLON NEWLINE indentdedent elifblock { $$ = new std::string(" else if (" + *$2 + ") {\n" + *$5 + "\n}" + *$6); delete $2, $5, $6; }
  | ELIF logic COLON NEWLINE indentdedent { $$ = new std::string(" else if (" + *$2 + ") {\n" + *$5 + "\n}"); delete $2, $5; }
  ;

elseblock
  : ELSE logic COLON NEWLINE indentdedent { $$ = new std::string(" else (" + *$2 + ") {\n" + *$5 + "\n}"); delete $2, $5; }
  | ELSE COLON NEWLINE indentdedent { $$ = new std::string(" else {\n" + *$4 + "\n}"); delete $4; }
  ;

indentdedent
  : INDENT indentdedent DEDENT { $$ = new std::string(*$2); delete $2; }
  | INDENT head DEDENT { $$ = new std::string(*$2); delete $2; }
  ;

  %%
