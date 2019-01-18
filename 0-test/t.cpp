// Example program
#include <iostream>
#include <string>
#include <cstdlib>
#include <string.h>
// 
// double evalFri(char* strin){
//   char* div=strchr(strin,'/');
//   std::string numerator(strin,div-strin);
//   std::string denominator(div+1);
//   return stof(numerator)/stof(denominator);
// }


int main()
{
  std::cout << atof("0") << "\n";
  std::cout << atof("-0") << "\n\n";// 0 + -0 => 0

  std::cout << atof("-.1") << "\n";
  std::cout << atof("-1.1") << "\n";
  std::cout << atof(".1") << "\n";
  std::cout << atof("1.1") << "\n\n";

  std::cout << atof("-1.") << "\n";
  std::cout << atof("-1") << "\n";
  std::cout << atof("1.") << "\n";
  std::cout << atof("1") << "\n\n";

  std::cout << atof(".") << "\n\n";

  std::cout << atof("") << "\n\n";



  // std::cout << atof(".456") << "\n";
  // std::cout << atof(".456") << "\n";
  //
  // char * yytext="5/6";
  // char * token;
  // token=strtok(yytext,"/");
  // std::cout << token << "\n";

  // double numberValue=atof(strtok(NULL,"/")) / atof(strtok(NULL,""));

  // std::cout << numberValue << "\n";

}
