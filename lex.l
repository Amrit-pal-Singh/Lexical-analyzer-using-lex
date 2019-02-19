int yywrap(void){}
%{  
    #include <iostream>
    #include "processor.h"
    using namespace std;
    int i = 0;
%}

%option nounput yylineno
datatype int|char|bool|float|void|for|do|while|if|else|return|void

%%
{datatype}  {return TYPE;}
=   {return EQUAL;}
"(".*")"   {return PARAMETER;}
"{"   {return LEFT_CURL;}
"}"     {return RIGHT_CURL;}
[a-zA-Z_][a-zA-Z0-9_]*	return IDENTIFIER;
[1-9][0-9]*	    return INTEGER;
[ \t\n] {;}
"/*".*"*/"     {return COMMENT;}
<<EOF>> return END_OF_FILE;
.   {cout<<"line "<<yylineno<<" INVALID TOKEN " <<yytext<<endl;}
%%

int yywrap(void){}


// when there is INVALID TOKEN no other result will be shown
// how to handle the waste code