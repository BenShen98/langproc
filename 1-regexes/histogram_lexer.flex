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

//functions
double evalFri(char* strin){
  char* div=strchr(strin,'/');
  std::string numerator(strin,div-strin);
  std::string denominator(div+1);
  return stod(numerator)/stod(denominator);
}

/* End the embedded code section. */
%}

alphabet  [a-z]|[A-Z]
digit       [0-9]

%%

-?{digit}+\.?{digit}*         { yylval.numberValue=atof(yytext); return Number;}
-?{digit}+\/{digit}+          { yylval.numberValue=evalFri(yytext); return Number; }


({alphabet}+)|(\[[^\]\n]*\])  { yylval.wordValue=yytext; return Word; }

.|\n                        { } // keep consume the buffer, ignore undefined string


%%

/* Error handler. This will get called if none of the rules match. */
void yyerror (char const *s)
{
  fprintf (stderr, "Flex Error: %s\n", s); /* s is the text that wasn't matched */
  exit(1);
}
