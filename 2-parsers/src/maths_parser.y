%code requires{
  #include "ast.hpp"

  #include <cassert>

  extern const Expression *g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  const Expression *expr;
  double number;
  std::string *string;
}

%token T_MINUS  T_PLUS
%token T_DIVIDE T_TIMES
%token T_EXPONENT
%token T_LBRACKET T_RBRACKET
%token T_LOG T_EXP T_SQRT
%token T_NUMBER T_VARIABLE

%type <expr> EXPR TERM FACTOR FUNCTION_NAME EXPONENT
%type <number> T_NUMBER
%type <string> T_VARIABLE T_LOG T_EXP T_SQRT

%start ROOT

%%

/* In the code below, the precedence increases move down the code
 FUNCTION_NAME > FACTOR > EXPONENT > TERM > ROOT
 ONLY EXPONENT is right-associative  https://en.wikipedia.org/wiki/Operator_associativity
*/

ROOT : EXPR { g_root = $1; }

EXPR      : TERM                        { $$ = $1; }
          | EXPR T_PLUS TERM            { $$ = new AddOperator( $1, $3 ); }
          | EXPR T_MINUS TERM           { $$ = new SubOperator( $1, $3 ); }

TERM      : EXPONENT                    { $$ = $1; }
          | TERM T_TIMES EXPONENT       { $$ = new MulOperator( $1, $3 ); }
          | TERM T_DIVIDE EXPONENT      { $$ = new DivOperator( $1, $3 ); }


EXPONENT  : FACTOR T_EXPONENT EXPONENT  { $$ = new ExpOperator( $1, $3 ); }
          | FACTOR                      { $$ = $1; }

FACTOR    : T_NUMBER                    {  $$ = new Number( $1 ); }
          | T_VARIABLE                  {  $$ = new Variable( $1 ); }
          | T_LBRACKET EXPR T_RBRACKET  { $$ = $2; }
          | FUNCTION_NAME               { $$ = $1; }

FUNCTION_NAME   : T_LOG T_LBRACKET EXPR T_RBRACKET    {  $$ = new LogFunction( $3 ); }
                | T_EXP T_LBRACKET EXPR T_RBRACKET    {  $$ = new ExpFunction( $3 ); }
                | T_SQRT T_LBRACKET EXPR T_RBRACKET   {  $$ = new SqrtFunction( $3 ); }

%%

const Expression *g_root; // Definition of variable (to match declaration earlier)

const Expression *parseAST()
{
  g_root=0; // Expression == 0??? call Number constructor???
  yyparse();
  return g_root;
}
