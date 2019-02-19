int yywrap(void){}
%{  
    #include <iostream>
    #include "processor.h"
    using namespace std;
    int i = 0;
%}

%option nounput yylineno
datatype int|char|bool|float|double|string|void

%%
{datatype}  {return TYPE;}
=   {return EQUAL;}
;   {return SEMICOLON;}
,   {return COMMA;}
"(".*")"[ ]*"{"* {return PARAMETER;}
[a-zA-Z_][a-zA-Z0-9_]*	return IDENTIFIER;
[1-9][0-9]*	    return INTEGER;
[ \t\n] {;}
"/*".*"*/"     {return COMMENT;}
<<EOF>> return END_OF_FILE;
.   {;}
%%

int yywrap(void){}


// should be valid for even non declaration statement of function
// way to remove the break statement from the print_specification_var function.