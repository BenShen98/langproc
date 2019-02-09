# flex
* [lex Patterns](http://ftp.gnu.org/old-gnu/Manuals/flex-2.5.4/html_mono/flex.html#SEC7)
* [STRTOK](https://www.codingame.com/playgrounds/14213/how-to-play-with-strings-in-c/string-split)
* [strtok segmentation fault](https://stackoverflow.com/questions/8957829/strtok-segmentation-fault)

# [bison](http://www.iro.umontreal.ca/~fourniep/bison/bison_6.html#SEC52)\
* terminal symbol: token returned by flex, i.e. T_* this sub2
  %left, %right, or %nonassoc can be used to replace %token (specify precedence)
* [Operator Precedence](http://www.iro.umontreal.ca/~fourniep/bison/bison_6.html#SEC51)
  - The associativity of an operator op determines how repeated uses of the operator nest: whether `x op y op z' is parsed by grouping x with y first or by grouping y with z first. %left specifies left-associativity (grouping x with y first) and %right specifies right-associativity (grouping y with z first). %nonassoc specifies no associativity, which means that `x op y op z' is considered a syntax error.
  - The precedence of an operator determines how it nests with other operators. All the tokens declared in a single precedence declaration have equal precedence and nest together according to their associativity. When two tokens declared in different precedence declarations associate, the one declared later has the higher precedence and is grouped first.
