#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "processor.h"

extern int yylex();
extern int  yylineno;
extern char* yytext;

using namespace std;


void variable_declaration(char* yytext, int &int_start, int &uppercase, int &underscore, int &int_inside){
    for(int i = 0; i < strlen(yytext); i++){
        if(yytext[0] >= 48 && yytext[0] <= 57){
            yylex();         // Total name except first element is another token IDENTIFIER
            int_start = 1;
            int_inside = 1;
            break;          // why removing this change my output
        }
        if(yytext[i] >= 65 && yytext[i] <= 90){
            uppercase = 1;
        }
        if(yytext[i] == '_'){
            underscore = 1;
        }
        if(yytext[i] >= 48 && yytext[i] <= 57){
            int_inside = 1;
        }
    }
}


int main(){
    int flag = 1,next_token = 1, value_token, uppercase = 0, int_start = 0, left_bracket = 0, left_curly_bracket = 0, underscore = 0, int_inside= 0, line_no;
    while(next_token){
        next_token = yylex();       // take the data  type
        
        if(next_token == COMMENT){
            line_no = yylineno;
        }
        else if(next_token != TYPE ){
            while(next_token != TYPE){
                next_token = yylex();
            }
        }
        next_token = yylex();       // take the variable
        if(next_token == 0){
            break;
        }
        variable_declaration(yytext, int_start, uppercase, underscore, int_inside);
        next_token = yylex();
        switch(next_token){
            case EQUAL:
                if(uppercase == 1){
                    cout<<"line: "<<yylineno<<" Uppercase in variable declaration is not allowed"<<endl;
                    uppercase = 0;
                }
                if(int_start == 1){
                    cout <<"line: "<<yylineno<<" Variable name cannot start with INT"<<endl;
                    int_start = 0;
                }
                if(underscore == 1){
                    cout <<"line: "<<yylineno<<" Variable name cannot have \"_\""<<endl;
                    underscore = 0;
                }
                if(yylineno - line_no != 1){
                    cout <<"line: "<<yylineno<<" Variable declaration is not documented"<<endl;
                }
                next_token = yylex();       // take the value assigned
                break;
            case PARAMETER:
                if(uppercase == 1){
                    cout<<"line: "<<yylineno<<" Uppercase in function declaration is not allowed"<<endl;
                    uppercase = 0;
                }
                if(int_inside == 1){
                    cout<<"line: "<<yylineno<<" Function declaration cannot contain INTEGER"<<endl;
                    int_inside = 0;
                }
                if(yylineno - line_no != 1){
                    cout <<"line: "<<yylineno<<" Function declaration is not documented"<<endl;
                }
                break;
        }
        value_token, uppercase = 0, int_start = 0, left_bracket = 0, left_curly_bracket = 0, underscore = 0, int_inside= 0;
    }

}