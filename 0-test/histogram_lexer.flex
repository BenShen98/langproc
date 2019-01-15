%option noyywrap

%{
/* Now in a section of C that will be embedded
   into the auto-generated code. Flex will not
   try to interpret code surrounded by %{ ... %} */

/* Bring in our declarations for token types and
   the yylval variable. */
#include "histogram.hpp"

#include <string>




// This is to work around an irritating bug in Flex
// https://stackoverflow.com/questions/46213840/get-rid-of-warning-implicit-declaration-of-function-fileno-in-flex
extern "C" int fileno(FILE *stream);

/* End the embedded code section. */
%}

word  [a-z]|[A-Z]

%%

  //add \n to end of line

[0-9]+          { fprintf(stderr, "Number : %s\n", yytext); yylval.numberValue=atof(yytext); /* */ return Number; }

{word}+          { fprintf(stderr, "Word : %s\n", yytext); yylval.wordValue=yytext;/* yylval WAS STRING* */ return Word; }


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
