

#include <stdio.h>
#include "resource.h"

map<int,map<int,Action> > parsing_table; //map[state number][terminal or nonterminal] = action (ex. map[1][PLUS] = ("shift",6) )
deque<Token> t_list;
deque<Token> p_list;
vector<Grammar> grammar_table={
    {Token(PROG,nullptr),1},
    {Token(PROG,nullptr),4},
    {Token(DECLS,nullptr),2},
    {Token(DECLS,nullptr),0},
    {Token(DECL,nullptr),3},
    {Token(WORDS,nullptr),2},
    {Token(WORDS,nullptr),1},
    {Token(VTYPE,nullptr),1},
    {Token(VTYPE,nullptr),1},
    {Token(BLOCK,nullptr),4},
    {Token(BLOCK,nullptr),0},
    {Token(SLIST,nullptr),2},
    {Token(SLIST,nullptr),1},
    {Token(STAT,nullptr),6},
    {Token(STAT,nullptr),3},
    {Token(STAT,nullptr),4},
    {Token(STAT,nullptr),3},
    {Token(COND,nullptr),3},
    {Token(COND,nullptr),3},
    {Token(EXPR,nullptr),1},
    {Token(EXPR,nullptr),3},
    {Token(TERM,nullptr),1},
    {Token(TERM,nullptr),3},
    {Token(FACT,nullptr),1},
    {Token(FACT,nullptr),1},};


