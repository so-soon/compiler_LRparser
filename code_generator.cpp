

#include <stdio.h>
#include "code_generator.h"
#include <fstream>

vector<string> target_code;

vector<string> scope;
string val_type;
string func_name;
int size,label_co,regi_co = 0;
vector<string> dfs_search(Parse_tree_Node *cur,int regi_num);
string find(string name);

void code_generating(string output_name){
    label_co = 0;
    dfs_search(syntax_tree.root,0);
    ofstream write_file;
    write_file.open(output_name+".code");
    
    for (int i = 0 ; i < int(target_code.size()); i++) {
        write_file.write((target_code[i]+"\n").c_str(), (target_code[i]+"\n").size());
    }
    write_file.close();
    
    write_file.open(output_name+".symbol");
    
    for (int i = 0 ; i < int(symbol_table.size()); i++) {
        write_file.write(("name : "+symbol_table[i].name+" type : "+symbol_table[i].type+" scope : "+symbol_table[i].scope+" size : "+to_string(symbol_table[i].size)+"\n").c_str(), ("name : "+symbol_table[i].name+" type : "+symbol_table[i].type+" scope : "+symbol_table[i].scope+" size : "+to_string(symbol_table[i].size)+"\n").size());
    }
    write_file.close();
    printf("total register count : %d",regi_co+1);
    
    
}
vector<string> dfs_search(Parse_tree_Node *cur,int regi_num){
    int cur_type;
    vector<string> var;
    vector<string> val;
    
    cur_type = cur->t.type;
    regi_co = (regi_co < regi_num) ? regi_num : regi_co;
    
    if (cur_type == INT) {
        val_type = "integer";
        size = 4;
        var.emplace_back("INT");
        return var;
    }
    else if (cur_type == CHAR){
        val_type = "chractor";
        var.emplace_back("CHAR");
        return var;
    }
    else if (cur_type == WORD || cur_type == NUM){
        if (val_type == "chractor") {
            size = int(strlen(cur->t.value));
        }else if (cur->parent->t.type == PROG) {
            func_name = cur->t.value;
            target_code.emplace_back("BEGIN "+func_name);
            val_type = "function_name";
            size = 4;
        }else{ 
            size = 4;
        }
        if(cur_type == WORD && ((cur->parent->t.type == WORDS && cur->parent->parent->t.type == DECL) || (cur->parent->t.type == PROG))) symbol_table.emplace_back(cur->t.value,val_type,scope.back(),size);
        var.emplace_back(cur->t.value);
        
        return var;
    }else if(cur_type == DECL) {
        dfs_search(cur->child[0],0);
        dfs_search(cur->child[1],0);
        var.clear();

    }
    else if(cur_type == STAT){
        if (cur->child.size() == 6 && cur->child[0]->t.type == IF) { // if cond then block else block
            scope.emplace_back("IF");
            dfs_search(cur->child[1],0);
            target_code.emplace_back("JUMPF Reg#"+to_string(regi_num)+" LABEL - "+to_string(label_co));
            dfs_search(cur->child[3],0);
            target_code.emplace_back("JUMP LABEL - "+to_string(label_co+1));
            target_code.emplace_back("LABEL - "+to_string(label_co));
            dfs_search(cur->child[5],0);
            target_code.emplace_back("LABEL - "+to_string(label_co+1));
            label_co += 2;
            scope.pop_back();
            
        }else if(cur->child.size() == 3){
            if (cur->child[0]->t.type == WHILE) { // while cond block
                scope.emplace_back("WHILE");
                val = dfs_search(cur->child[1], 0);
                target_code.emplace_back("LABEL - "+to_string(label_co));
                target_code.emplace_back("JUMPF Reg#"+to_string(regi_num)+" LABEL - "+to_string(label_co+1));
                dfs_search(cur->child[2], 0);
                target_code.emplace_back("JUMP LABEL - "+to_string(label_co));
                target_code.emplace_back("LABEL - "+to_string(label_co+1));
                label_co += 2;
                scope.pop_back();
            }else if(cur->child[0]->t.type == RETURN){ //return expr
                dfs_search(cur->child[1], regi_num);
                target_code.emplace_back("END "+func_name);
                scope.pop_back();
            }
        }else if(cur->child.size() == 4){ //assign
            if (cur->child[1]->t.type == ASGN) {
                val = dfs_search(cur->child[0], regi_num);
                dfs_search(cur->child[2], regi_num);
                target_code.emplace_back("ST "+find(val[0])+" Reg# "+to_string(regi_num));
                
            }
        }
    }else if(cur_type == COND){
        if (cur->child.size() == 3) {//expr > expr
            val = dfs_search(cur->child[0], regi_num);
            var = dfs_search(cur->child[2], regi_num+1);
            
            target_code.emplace_back("LT Reg#"+to_string(regi_num)+" Reg# "+to_string(regi_num+1)+" Reg#"+to_string(regi_num));
        }
    }else if(cur_type == EXPR){
        if(cur->child.size() == 1){//term
            val = dfs_search(cur->child[0], regi_num);
            for (int i = 0 ; i < val.size(); i++) {
                var.emplace_back(val[i]);
            }
        }else{ // term + term
            dfs_search(cur->child[0], regi_num);
            dfs_search(cur->child[2], regi_num+1);
            target_code.emplace_back("ADD Reg#"+to_string(regi_num)+" Reg#"+to_string(regi_num)+" Reg#"+to_string(regi_num+1));
        }
    }else if(cur_type == TERM){
        if (cur->child.size() == 1) { // fact
            val = dfs_search(cur->child[0], regi_num);
            for (int i = 0; i < val.size(); i++) {
                var.emplace_back(val[i]);
            }
        }else{ //fact * fact
            dfs_search(cur->child[0], regi_num);
            dfs_search(cur->child[2], regi_num+1);
            target_code.emplace_back("MUL Reg# "+to_string(regi_num)+" Reg#"+to_string(regi_num) + "  Reg#"+to_string(regi_num+1));
        }
    }else if(cur_type == FACT){
        val = dfs_search(cur->child[0], regi_num);
        if (val[0] == "0" || val[0] == "1" || val[0] == "2" || val[0] == "3" || val[0] == "4" || val[0] == "5" || val[0] == "6" || val[0] == "7" || val[0] == "8" || val[0] == "9") { // number
            target_code.emplace_back("LD Reg#"+to_string(regi_num)+" "+val[0]);
        }else{ //word
            target_code.emplace_back("LD Reg#"+to_string(regi_num)+" "+find(val[0]));
        }
    }else{
        if(cur_type == PROG){
            scope.emplace_back("block local");
            
        }
        for (int i = 0; i < cur->child.size(); i++) {
            val = dfs_search(cur->child[i], 0);
            for (int j = 0; j < val.size(); j++) {
                var.emplace_back(val[j]);
            }
        }
    }
    return var;
}

string find(string name){
    for (int i = 0; i < symbol_table.size(); i++) {
        if (symbol_table[i].name == name) {
            return symbol_table[i].name;
        }
    }
    return "none";
}
