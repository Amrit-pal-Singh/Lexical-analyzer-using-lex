#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "processor.h"

extern int yylex();
extern int  yylineno;
extern char* yytext;

using namespace std;


/* this function is to print the error in variable declaration */
void print_specification_var(int &uppercase, int &int_start, int &underscore, int &line_no, int& yylineno){
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
    if(abs(yylineno - line_no) != 1){
        cout <<"line: "<<yylineno<<" Variable declaration is not documented"<<endl;
    }
}

/* This function is to print the error in function declaration*/
void print_specification_func(int &uppercase, int &int_inside, int &underscore, int &line_no, int& yylineno){
    if(uppercase == 1){
        cout<<"line: "<<yylineno<<" Uppercase in function declaration is not allowed"<<endl;
        uppercase = 0;
    }
    if(int_inside == 1){
        cout<<"line: "<<yylineno<<" Function declaration cannot contain INTEGER"<<endl;
        int_inside = 0;
    }
    if(abs(yylineno - line_no) != 1){
        cout <<"line: "<<yylineno<<" Function declaration is not documented"<<endl;
    }
}

/*  This function is used to return if there is any underscore, uppercase, integer in beginning or inside*/
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

/* what will happen if we get comma in declaration */
void comma_(int &int_start, int &uppercase, int &underscore, int &int_inside, int &line_no){
    while(1){
        int next_token = yylex();   // next name
        variable_declaration(yytext, int_start, uppercase, underscore, int_inside);
        line_no  = yylineno+1;
        print_specification_var(uppercase, int_start, underscore, line_no, yylineno);
        next_token = yylex();
        if(next_token == EQUAL){
            next_token = yylex();
            if(next_token != INTEGER && next_token != IDENTIFIER){
                cout <<"line: "<<yylineno<<" 1Wrong declaration of variable"<<endl;
                break;    
            }
            else{
                next_token = yylex();
                if(next_token == COMMA){
                    continue;
                }
                else if(next_token == SEMICOLON){
                    break;
                }
            }
        }
        else if(next_token != EQUAL && next_token != COMMA && next_token != SEMICOLON){
            cout <<"line: "<<yylineno<<" 2Wrong declaration of variable"<<endl;
            break;
        }
        else if(next_token == SEMICOLON){
            break;
        }
    }
}

int main(){
    int flag = 1,next_token = 1, value_token, uppercase = 0, int_start = 0, left_bracket = 0, left_curly_bracket = 0, underscore = 0, int_inside= 0, line_no;
    int fuck_you = 0;
    while(next_token != END_OF_FILE){
        next_token = yylex();       // take the data  type
        if(next_token == END_OF_FILE){
            break;
        }
        else if(next_token == COMMENT){
            line_no = yylineno;
        }
        else if(next_token == TYPE)
            next_token = yylex();       // take the variable
        else
            continue;
        variable_declaration(yytext, int_start, uppercase, underscore, int_inside);
        next_token = yylex();
        switch(next_token){
            case EQUAL:
                print_specification_var(uppercase, int_start, underscore, line_no, yylineno);
                next_token = yylex();       // take the value assigned
                if(next_token != INTEGER && next_token != IDENTIFIER){
                    cout <<"line: "<<yylineno<<" 3Wrong declaration of variable"<<endl;
                    break;    
                }
                else{
                    next_token = yylex();
                    if(next_token == COMMA){
                        comma_(int_start, uppercase, underscore, int_inside, line_no);
                    }
                    else if(next_token == SEMICOLON){
                        break;
                    }
                }
                break;

            case PARAMETER:
                print_specification_func(uppercase, int_inside, underscore, line_no, yylineno);
                break;
            case SEMICOLON:
                print_specification_var(uppercase, int_start, underscore, line_no, yylineno);
                break;
            default:
                break;
                
        }
        value_token, uppercase = 0, int_start = 0, left_bracket = 0, left_curly_bracket = 0, underscore = 0, int_inside= 0;
    }

}