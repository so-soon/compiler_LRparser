
#ifndef resource_h
#define resource_h

#include <vector>
#include <deque>
#include <map>
#include <string>

using namespace std;

//MARK:- T_TYPE

typedef enum{ // types of token
    PROG, //porg 0
    DECLS, //delcs 1
    DECL, //decl 2
    WORDS, //words 3
    VTYPE, //vtype 4
    BLOCK, //block 5
    SLIST, //slist 6
    STAT, //stat 7
    COND, // cond 8
    EXPR, //expr 9
    TERM, //term 10
    FACT, //fact 11
    WORD, //word 12
    NUM, //num 13
    SOPT, // small open parenthesis '(' 14
    SCPT, // small close parenthesis ')' 15
    COM, // ',' 16
    SEMICOL, // ';' 17
    MOPT, // middle open parenthesis '{' 18
    MCPT, // middle close parenthesis '}' 19
    INT, // int 20
    CHAR, // char 21
    IF, // 22
    THEN, // 23
    ELSE, // 24
    WHILE, // 25
    ASGN, // assign '=' 26
    RETURN, //27
    GT, // greater '>' 28
    EQ, // equal '==' 29
    PLUS, // '+' 30
    MUL, // '*' 31
    END, // $ 32
    EPS // epsilon 33
}t_type;

//MARK:- TOKEN STRUCT

typedef struct _Token{ //token struct
    int type; // token type
    char* value; // token value (only available in NUM,WORD type
    
    _Token() : type(EPS) ,value(nullptr) {} // initializer
    _Token(int t, char *v) : type(t), value(v) {} // constructor
    
}Token;


//MARK:- ACTION

typedef struct _Action{
    char* action; // shift,reduce,goto,accept
    int next_state; // 0,1,2,3, ...
    
    _Action() : action(nullptr), next_state(-1) {}
    _Action(char* a, int ns) : action(a) , next_state(ns) {}
    
}Action;

//MARK:- STACKITEM
typedef struct _StackItem{
    Token t; // E,T,F,id,*,...,etc
    int state; // state number 0,1,2,3,...
    
    _StackItem() : t(-1,nullptr) , state(-1) {}
    _StackItem(Token temp_t, int s) : t(temp_t), state(s) {}
}StackItem;

//MARK:- GRAMMAR
typedef struct _Grammar{
    Token LHS; // left hand side
    int count; //how many times pop token from stack
    
    _Grammar() : LHS(Token(EPS,nullptr)) , count(0) {}
    _Grammar(Token lhs,int co) : LHS(lhs),count(co) {}
    
}Grammar;

//MARK:- SYNTAX TREE
typedef struct _Parse_tree_Node{
    Token t;
    
    _Parse_tree_Node* parent;
    vector<_Parse_tree_Node*> child;
    
    _Parse_tree_Node() : t(Token(-1,nullptr)),parent(nullptr) {};
    _Parse_tree_Node(_Parse_tree_Node *p,Token t) : t(t),parent(p) {};
    
}Parse_tree_Node;
typedef struct _Syntax_tree{
    Parse_tree_Node *root;
    
    _Syntax_tree(): root(nullptr){};
    _Syntax_tree(Parse_tree_Node *r): root(r) {};
}Syntax_tree;

typedef struct _Symbol_table_row{
    string name;
    string type;
    string scope;
    int size;
    
    _Symbol_table_row() : name(""),type(""),scope(""),size(-1){};
    _Symbol_table_row(string n,string t,string s,int sz) : name(n),type(t),scope(s),size(sz){};
    
}Symbol_table_row;
// make it global
extern deque<Token> t_list;
extern deque<Token> p_list;
extern map<int,map<int,Action> > parsing_table;
extern vector<Grammar> grammar_table;
extern Syntax_tree syntax_tree;
extern vector<Symbol_table_row> symbol_table;
#endif /* resource_h */
