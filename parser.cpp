

#include <stdio.h>
#include "parser.h"
vector<vector<t_type> > nearby = { // {LHS,CURRENT,NEARBY}
    {PROG,BLOCK,SCPT},
    {PROG,SCPT,SOPT},
    {PROG,SOPT,WORD},
    {DECLS,DECL,DECLS},
    {DECL,SEMICOL,WORDS},
    {DECL,WORDS,VTYPE},
    {WORDS,WORD,COM},
    {WORDS,COM,WORDS},
    {BLOCK,MCPT,SLIST},
    {BLOCK,SLIST,DECLS},
    {BLOCK,DECLS,MOPT},
    {SLIST,STAT,SLIST},
    {STAT,BLOCK,ELSE},
    {STAT,ELSE,BLOCK},
    {STAT,BLOCK,THEN},
    {STAT,THEN,COND},
    {STAT,COND,IF},
    {STAT,COND,BLOCK},
    {STAT,BLOCK,WHILE},
    {STAT,SEMICOL,EXPR},
    {STAT,EXPR,ASGN},
    {STAT,ASGN,WORD},
    {STAT,SEMICOL,EXPR},
    {STAT,EXPR,RETURN},
    {COND,EXPR,GT},
    {COND,GT,EXPR},
    {COND,EXPR,EQ},
    {COND,EQ,EXPR},
    {EXPR,TERM,PLUS},
    {EXPR,PLUS,TERM},
    {TERM,FACT,MUL},
    {TERM,MUL,FACT}
    
};

void dfs(Parse_tree_Node *cur);
void parser(){
    vector<StackItem> s;
    deque<int> a;
    bool isFinished = false;
    Token leftInput;
    StackItem stackTop;
    Action nowAction;
    
    s.emplace_back(Token(END,nullptr),0);
    
    try{
        while (!isFinished) {
            
            leftInput = t_list.front();
            stackTop = s.back();
            
            nowAction = parsing_table[stackTop.state][leftInput.type];
            
            if (strcmp(nowAction.action,"shift") == 0) {
                p_list.emplace_back(leftInput);
                s.emplace_back(leftInput,nowAction.next_state);
                t_list.pop_front();
            }else if(strcmp(nowAction.action, "reduce") == 0){
                
                for (int i = 0; i < grammar_table[nowAction.next_state].count; i++) {
                    s.pop_back();
                }
                s.emplace_back(grammar_table[nowAction.next_state].LHS,parsing_table[s.back().state][grammar_table[nowAction.next_state].LHS.type].next_state);
                p_list.emplace_back(grammar_table[nowAction.next_state].LHS.type,nullptr);
            }else if(strcmp(nowAction.action,"accept") == 0){
                printf("Accept!");
                isFinished = true;
            }
        }
    }catch(...){
        printf("syntax error! \n");
        return;
    }
}

void parseTree(){
    Parse_tree_Node *rt = new Parse_tree_Node(NULL,p_list.back());
    p_list.pop_back();
    syntax_tree.root = rt;
    
    dfs(rt);
}

void dfs(Parse_tree_Node *cur){
    Token t;
    while (!(p_list.empty())) {
        t = p_list.back();
        bool isNearby = false;
        if (cur->child.empty()) {
            isNearby = true;
        }else{
            for (int i = 0 ; i < nearby.size(); i++) {
                if (cur->t.type == nearby[i][0] && cur->child.front()->t.type == nearby[i][1] && t.type == nearby[i][2]) {
                    isNearby = true;
                }
            }
        }
        
        
        if (isNearby) {
            p_list.pop_back();
            Parse_tree_Node *ch_node = new Parse_tree_Node(cur,t);
            cur->child.insert(cur->child.begin(), ch_node);
            
            if (t.type <= FACT) {
                dfs(ch_node);
            }
            
        }
        else{
            return;
        }
        
        
        
    }
}
