

#include <stdio.h>
#include <fstream>
#include "scanner.h"


#define MAX_CHAR 256 //# of maximum chractor in a line

using namespace std;
char line[MAX_CHAR];


//MARK:- SCANNER

void scanner(char *file_name){
    ifstream read_file;
    read_file.open(file_name);
    if (read_file.is_open()) {
        while (!read_file.eof()) {
            read_file.getline(line, MAX_CHAR);
            tokenizing(line);
        }

        t_list.emplace_back(END,nullptr);
        
        read_file.close();
    }else{ //error handling : file not exist
        printf("file does not exist\n");
        return;
    }
    
    return;
}
//MARK:- TOKENIZER
void tokenizing(char *str){
    int idx = 0;
    
    char raw_token[256] = {0,}; //raw token value only in NUM,WORD type (ex.number(1,2,3, ..) , word(function name, variable name, ..)
    t_type type;
    char *value = nullptr;
    //hello () {int a; int b; a = 3; b = a + 3;}
    for (int i = 0 ; i <= int(strlen(str)) ; i++) {
        if (idx != 0 && (str[i] == '(' || str[i] == ')' || str[i] == ';' || str[i] == ',' || str[i] == '{' || str[i] == '}' || str[i] == '=' || str[i] == '>' || str[i] == '+' || str[i] == '*' || str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\0')) {
            
            // If str[i] is not first of line and str[i] is other terminals or blank, store it in token list(t_list)
            
            raw_token[idx] = '\0'; //append end of charactor
            
            if (strcmp(raw_token, "int") == 0) type = INT;
            else if (strcmp(raw_token, "char") == 0) type = CHAR;
            else if (strcmp(raw_token, "IF") == 0) type = IF;
            else if (strcmp(raw_token, "THEN") == 0) type = THEN;
            else if (strcmp(raw_token, "ELSE") == 0) type = ELSE;
            else if (strcmp(raw_token, "WHILE") == 0) type = WHILE;
            else if (strcmp(raw_token, "RETURN") == 0) type = RETURN;
            else if (raw_token[0] >= '0' && raw_token[0] <= '9'){
                type = NUM;
                value = strdup(raw_token);
            }else{
                type = WORD;
                value = strdup(raw_token);
            }
            if (type == NUM or type == WORD) {
                t_list.emplace_back(type,value);
            }else{
                t_list.emplace_back(type,nullptr);
            }
            
            idx = 0;
            
        }
        
        //If str[i] is terminal , store it
        
        if (str[i]  == '(') {
            type = SOPT;
            t_list.emplace_back(type,nullptr);
        }else if (str[i]  == ')') {
            type = SCPT;
            t_list.emplace_back(type,nullptr);
        }else if (str[i]  == '{') {
            type = MOPT;
            t_list.emplace_back(type,nullptr);
        }else if (str[i]  == '}') {
            type = MCPT;
            t_list.emplace_back(type,nullptr);
        }else if (str[i]  == ';') {
            type = SEMICOL;
            t_list.emplace_back(type,nullptr);
        }else if (str[i] == ',') {
            type = COM;
            t_list.emplace_back(type,nullptr);
        }else if (str[i]  == '=') {
            if (str[i+1] == '='){
                type = EQ;
                i++;
            }
            else type = ASGN;
            t_list.emplace_back(type,nullptr);
        }else if (str[i]  == '>') {
            type = GT;
            t_list.emplace_back(type,nullptr);
        }else if (str[i]  == '+') {
            type = PLUS;
            t_list.emplace_back(type,nullptr);
        }else if (str[i]  == '*') {
            type = MUL;
            t_list.emplace_back(type,nullptr);
        }else if(str[i] == ' ' || str[i] == '\n' || str[i] == '\0' || str[i] == '\t'){ // If str[i] is blank or something about newline charactor, just continue
            continue;
        }else{ // make value of NUM,WORD
            raw_token[idx++] = str[i];
        }
    }
    
    
    return;
}
