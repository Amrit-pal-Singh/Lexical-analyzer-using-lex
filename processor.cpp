#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "processor.h"

extern int yylex();
extern int  yylineno;
extern char* yytext;

using namespace std;

int main(){
    int next_token = 1, value_token, uppercase = 0, int_start = 0;
    while(next_token){
        next_token = yylex();       // take the data  type
        next_token = yylex();       // take the variable
        
        if(next_token == 0){
            break;
        }

        /* variable declaration start */
        
        for(int i = 0; i < strlen(yytext); i++){
            if(yytext[0] >= 48 && yytext[0] <= 57){
                // 
                yylex();
                int_start = 1;
                flag = 1;
            }
            else if(yytext[i] >= 65 && yytext[i] <= 90){
                //
                break;
                flag = 1;
                uppercase = 1;
            }
            
        }
        
        next_token = yylex();       // take in  =
        if(next_token != EQUAL){
            cout<<"line: "<<yylineno<<" = Expected but not found"<<endl;    
            yylex();
            flag = 1;
            continue;
        }
        next_token = yylex();
        if(next_token != INTEGER){
            cout<<"line: "<<yylineno<<" Expected a INTEGER but found " << yytext<<endl;    
        }
        
        if(flag == 0){
            cout<<"correct statement" << endl;
        }


        /* variable declaration end */
        
        switch(next_token){
            case EQUAL:
                if(uppercase == 1){
                    cout<<"line: "<<yylineno<<" Uppercase in variable declaration is not allowed"<<endl;
                }
                if(int_start == 1){
                    cout <<"line: "<<yylineno<<" Variable name cannot start with INT"<<endl;
                }
                next_token = yylex();
                break;
            case LEFT_BRACKET:
                
        }

    }

}