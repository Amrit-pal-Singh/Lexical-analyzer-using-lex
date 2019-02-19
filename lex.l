int yywrap(void){}
%{  
    #include <iostream>
    #include "processor.h"
    using namespace std;
    int i = 0;
%}
%option nounput yylineno

%%
=   {return EQUAL;}
"int"   {return INT;}    
[_a-zA-Z][a-zA-Z0-9]*	return IDENTIFIER;
[1-9][0-9]*	    return INTEGER;
(   {return LEFT_BRACKET}
)   {return RIGHT_BRACKET}
[ \t\n] {;}
.   {cout<<"Syntax error"<<endl;}
%%

int yywrap(void){}
