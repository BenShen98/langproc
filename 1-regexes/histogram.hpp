#ifndef histogram_hpp
#define histogram_hpp

#include <string>

enum TokenType{
    None   = 0, // This indicates there are no more tokens
    Number = 1, // token codes must be positive
    Word      // = 2, implicit from C++ enumeration
};

union TokenValue{
    double numberValue;
    char *wordValue;
};

// This is a global variable used to move the
// attribute value from the lexer back to the
// main program.
// By convention it is called yylval, as that is
// the name that will be automatically generated
// by Bison (see next lab).
extern TokenValue yylval;

// This is the lexer function defined by flex. Each
// time it is called, a token type value will be
// returned.
extern int yylex();

#endif

// when input is string, use yyleng to get char* length
// use string constructor(const char* s, size_t n) to ensure code still work with non-visiable char (eg 0x00)
#ifndef YYLENG
extern size_t yyleng;
#endif
