%{
#include <iostream>
#include <stack>

std::stack<int> indent_level;

void check_indents(char *yy_text) {
  int indent = 0;
  while ((*yy_text == ' ') || (*yy_text == '  ')){
    indent++; //count indents
    yy_text++; //increment yy_text
  }

  if(indent == indent_level.top()){
    return;
  }

  else if(indent > indent_level.top()) {
    std::cout << "INDENT" << std::endl;
    indent_level.push(indent); //push new indent
    return;
  }

  while(indent < indent_level.top()){
    std::cout << "DEDENT" << std::endl;
    indent_level.pop(); //pop each dedent
  }
}


%}

%option noyywrap

%%

^#.*\n    {}
^[ \t]*\n   {}

^[ ]*[^ \n]+    {
                  int lastChar = yyleng - 1;
                  check_indents(yytext);
                  while((lastChar >= 0) && (yytext[lastChar] != ' ')){
                    unput(yytext[lastChar]);
                    lastChar--;
                  }
                }

"-"?[0-9]*    { std::cout << "INTEGER\t\t" << atoi(yytext) << std::endl; }
"-"?[0-9]*[.][0-9]+     { std::cout << "FLOAT\t\t" << atof(yytext) << std::endl; }

True    { std::cout << "BOOLEAN\t\t1" << std::endl; }

False    { std::cout << "BOOLEAN\t\t0" << std::endl; }

and     { std::cout << "AND\t\t" << yytext << std::endl; }
break     { std::cout << "BREAK\t\t" << yytext << std::endl; }
def     { std::cout << "DEF\t\t" << yytext << std::endl; }
elif     { std::cout << "ELIF\t\t" << yytext << std::endl; }
else     { std::cout << "ELSE\t\t" << yytext << std::endl; }
for     { std::cout << "FOR\t\t" << yytext << std::endl; }
if     { std::cout << "IF\t\t" << yytext << std::endl; }
not     { std::cout << "NOT\t\t" << yytext << std::endl; }
or     { std::cout << "OR\t\t" << yytext << std::endl; }
return     { std::cout << "RETURN\t\t" << yytext << std::endl; }
while     { std::cout << "WHILE\t\t" << yytext << std::endl; }

[a-zA-Z_][0-9a-zA-Z_]*    { std::cout << "IDENTIFIER\t" << yytext << std::endl; }

[\n]      { std::cout << "NEWLINE" << std::endl; }
"="     { std::cout << "ASSIGN\t\t" << yytext << std::endl; }
"+"     { std::cout << "PLUS\t\t" << yytext << std::endl; }
"-"     { std::cout << "MINUS\t\t" << yytext << std::endl; }
"*"     { std::cout << "TIMES\t\t" << yytext << std::endl; }
"/"     { std::cout << "DIVIDEDBY\t" << yytext << std::endl; }
"=="     { std::cout << "EQ\t\t" << yytext << std::endl; }
"!="     { std::cout << "NEQ\t\t" << yytext << std::endl; }
">="     { std::cout << "GTE\t\t" << yytext << std::endl; }
">"     { std::cout << "GT\t\t" << yytext << std::endl; }
"<="     { std::cout << "LTE\t\t" << yytext << std::endl; }
"<"     { std::cout << "LT\t\t" << yytext << std::endl; }
"("     { std::cout << "LPAREN\t\t" << yytext << std::endl; }
")"     { std::cout << "RPAREN\t\t" << yytext << std::endl; }
","     { std::cout << "COMMA\t\t" << yytext << std::endl; }
":"     { std::cout << "COLON\t\t" << yytext << std::endl; }

[ ]   {}

[    ]    {}

<<EOF>>   {
            check_indents((char *)"");
            return 0;
          }

%%

int main() {
  indent_level.push(0);
  yylex();
  return 0;

}
