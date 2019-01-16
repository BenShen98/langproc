%option noyywrap

%{
/* Now in a section of C that will be embedded
   into the auto-generated code. Flex will not
   try to interpret code surrounded by %{ ... %} */

/* Bring in our declarations for token types and
   the yylval variable. */
#include "histogram.hpp"

#include <string>
#include <cstdlib>




// This is to work around an irritating bug in Flex
// https://stackoverflow.com/questions/46213840/get-rid-of-warning-implicit-declaration-of-function-fileno-in-flex
extern "C" int fileno(FILE *stream);

double evalFri(char* strin){
  char* div=strchr(strin,'/');
  std::string numerator(strin,div-strin);
  std::string denominator(div+1);
  return stod(numerator)/stod(denominator);
}

/* End the embedded code section. */
%}

alphabet  [a-z]|[A-Z]
num       [0-9]

%%

  //add \n to end of line
  //yytext in stack? heap?


-?{num}*\.{num}*          { fprintf(stderr, "Number : %s\n", yytext); yylval.numberValue=atof(yytext); /* */ return Number; }
-?{num}*\/{num}*          { yylval.numberValue=evalFri(yytext); fprintf(stderr, "Number (fraction): %f\n", yylval.numberValue); return Number; } //bug


{alphabet}+         { fprintf(stderr, "Word : %s\n", yytext); yylval.wordValue=yytext;/* yylval WAS STRING* */ return Word; }
\[.*\]           { fprintf(stderr, "[Word] : %s\n", yytext); yylval.wordValue=yytext;/* yylval WAS STRING* */ return Word; } //watch out NULL in the middle, remove []

\n              { fprintf(stderr, "Newline\n"); }


%%

/* Error handler. sss*/
void yyerror (char const *s)
{
  fprintf (stderr, "Flex Error: %s\n", s); /* s is the text that wasn't matched */
  exit(1);
}

int main(){
  while(1){
    fprintf(stderr,"===enter lex===\n");
    int x=yylex();
    fprintf(stderr, "===info from main===\nyylex return code: %i\n", x);
    if(x==Number){
      fprintf(stderr, "[num]yylval: %f\n", yylval.numberValue);
    }else if(x==Word){
      fprintf(stderr, "[word]yylval: %s\n", yylval.wordValue);
    }else{
    break;
    }
    fprintf(stderr, "===LOOP end===\n\n");
    }
}
