/*
 * Lexer definition for simplified Python syntax.
 */

/*
 * Since we're only parsing 1 file, we don't need to have yywrap() (plus,
 * having it included messes up compilation).
 */
%option noyywrap
%option yylineno

%{
#include <iostream>
#include <stack>
#include <cstdlib>
#include <vector>
#include <set>

#include "parser.hpp"

YYSTYPE yylval;
YYLTYPE yylloc;
yypstate *ps = yypstate_new();

#define PUSH_TOKEN(token) do {                            \
  int status = yypush_parse(ps, token, &yylval, &yylloc); \
  if(status != YYPUSH_MORE) {                             \
    yypstate_delete(ps);                                  \
    return status;                                        \
  }                                                       \
} while(0)

#define YY_USER_ACTION \
  yylloc.first_line = yylloc.last_line = yylineno;

/*
 * We'll use this stack to keep track of indentation level, as described in
 * the Python docs:
 *
 * https://docs.python.org/3/reference/lexical_analysis.html#indentation
 */
std::stack<int> _indent_stack;

%}

%option noyywrap
%option yylineno

%%

%{
  /*
   * These lines go at the top of the lexing function.  We only want to
   * initialize the indentation level stack once by pushing a 0 onto it (the
   * indentation stack should never be empty, except immediately after it is
   * created).
   */
  if (_indent_stack.empty()) {
    _indent_stack.push(0);
  }
%}

^[ \t]*\r?\n   { /* Skip blank lines */ }

^[ \t]*#.*\r?\n    { /* Skip whole-line comments. */ }

#.*$          { /* Skip comments on the same line as a statement. */ }

^[ \t]+       {
                /*
                 * Handle indentation as described in Python docs linked above.
                 * Note that this pattern treats leading spaces and leading tabs
                 * equivalently, which could cause some unexpected behavior if
                 * they're combined in a single line.  For the purposes of this
                 * project, that's OK.
                 */
                if (_indent_stack.top() < yyleng) {
                  /*
                   * If the current indentation level is greater than the
                   * previous indentation level (stored at the top of the stack),
                   * then emit an INDENT and push the new indentation level onto
                   * the stack.
                   */
                  PUSH_TOKEN((yylval.category=INDENT));
                  _indent_stack.push(yyleng);
                } else {
                  /*
                   * If the current indentation level is less than or equal to
                   * the previous indentation level, pop indentation levels off
                   * the stack until the top is equal to the current indentation
                   * level.  Emit a DEDENT for each element popped from the stack.
                   */
                  while (!_indent_stack.empty() && _indent_stack.top() != yyleng) {
                    _indent_stack.pop();
                    PUSH_TOKEN((yylval.category=DEDENT));
                  }

                  /*
                   * If we popped everything off the stack, that means the
                   * current indentation level didn't match any on the stack,
                   * which is an indentation error.
                   */
                  if (_indent_stack.empty()) {
                    std::cerr << "Error: Incorrect indentation on line "
                      << yylineno << std::endl;
                    return 1;
                  }
                }
              }

^[^ \t\r\n]+  {
                /*
                 * If we find a line that's not indented, pop all indentation
                 * levels off the stack, and emit a DEDENT for each one.  Then,
                 * call REJECT, so the next rule matching this token is also
                 * applied.
                 */
                while (_indent_stack.top() != 0) {
                  _indent_stack.pop();
                  PUSH_TOKEN((yylval.category=DEDENT));
                }
                REJECT;
              }

\r?\n         { PUSH_TOKEN((yylval.category=NEWLINE)); }

<<EOF>>       {
                /*
                 * If we reach the end of the file, pop all indentation levels
                 * off the stack, and emit a DEDENT for each one.
                 */
                while(_indent_stack.top() != 0) {
                  _indent_stack.pop();
                  PUSH_TOKEN((yylval.category=DEDENT));
                }
                int status = yypush_parse(ps, 0, NULL, NULL);
                yypstate_delete(ps);
                return status;
              }

[ \t]         { /* Ignore spaces that haven't been handled above. */ }

"and"         { PUSH_TOKEN(AND); }
"break"       { PUSH_TOKEN(BREAK); }
"elif"        { PUSH_TOKEN(ELIF); }
"else"        { PUSH_TOKEN(ELSE); }
"if"          { PUSH_TOKEN(IF); }
"not"         { PUSH_TOKEN(NOT); }
"or"          { PUSH_TOKEN(OR); }
"return"      { PUSH_TOKEN(RETURN); }
"while"       { PUSH_TOKEN(WHILE); }

"True"        { PUSH_TOKEN(TRUE); }

"False"       { PUSH_TOKEN(FALSE); }

[a-zA-Z_][a-zA-Z0-9_]*  {
                          yylval.str = new std::string(yytext, yyleng);
                          PUSH_TOKEN(IDENTIFIER);
                        }

-?[0-9]*"."[0-9]+       {
                          yylval.str = new std::string(yytext, yyleng);
                          PUSH_TOKEN(NUMBER);
                        }

-?[0-9]+      {
                yylval.str = new std::string(yytext, yyleng);
                PUSH_TOKEN(NUMBER);
              }

"="           { PUSH_TOKEN((yylval.category=EQUALS)); }
"+"           { PUSH_TOKEN((yylval.category=PLUS)); }
"-"           { PUSH_TOKEN((yylval.category=MINUS)); }
"*"           { PUSH_TOKEN((yylval.category=TIMES)); }
"/"           { PUSH_TOKEN((yylval.category=DIVIDEDBY)); }

"=="          { PUSH_TOKEN((yylval.category=EQ)); }
"!="          { PUSH_TOKEN((yylval.category=NEQ)); }
">"           { PUSH_TOKEN((yylval.category=GT)); }
">="          { PUSH_TOKEN((yylval.category=GTE)); }
"<"           { PUSH_TOKEN((yylval.category=LT)); }
"<="          { PUSH_TOKEN((yylval.category=LTE)); }

"("           { PUSH_TOKEN((yylval.category=LPAREN)); }
")"           { PUSH_TOKEN((yylval.category=RPAREN)); }

","           { PUSH_TOKEN((yylval.category=COMMA)); }
":"           { PUSH_TOKEN((yylval.category=COLON)); }

.             {
                std::cerr << "Unrecognized token on line " << yylineno << ": "
                  << yytext << std::endl;
                return 1;
              }

%%
