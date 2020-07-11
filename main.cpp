

#include <iostream>
#include <cstring>
#include <vector>
#include "scanner.h"
#include "parser.h"
#include "code_generator.h"
using namespace std;


vector<Symbol_table_row> symbol_table;
Syntax_tree syntax_tree;
void make_table();
int main(int argc, const char * argv[]) {
    char *file_name;
    char temp[256];
    if (argc <= 1) {
        printf((char*)"file name : ");
        scanf("%s",temp);
        file_name = strdup(temp);
    }else{
        file_name = strdup(argv[1]);
    }
    
    //action-goto table
    make_table();

    
    
    // scanner
    scanner(file_name);
    // parser
    parser();
    
    // build syntax_tree
    parseTree();
    
    // code generating
    code_generating(file_name);
    return 0;
}

void make_table(){
    parsing_table[0][WORD] = Action((char*)(char*)"shift",2);
    parsing_table[0][PROG] = Action((char*)"goto",1);
    parsing_table[1][END] = Action((char*)"accept",4);
    parsing_table[2][SOPT] = Action((char*)"shift",3);
    parsing_table[3][SCPT] = Action((char*)"shift",4);
    parsing_table[4][MOPT] = Action((char*)"shift",6);
    parsing_table[4][END] = Action((char*)"reduce",10);
    parsing_table[4][BLOCK] = Action((char*)"goto",5);
    parsing_table[5][END] = Action((char*)"reduce",1);
    parsing_table[6][WORD] = Action((char*)"reduce",3);
    parsing_table[6][INT] = Action((char*)"reduce",3);
    parsing_table[6][CHAR] = Action((char*)"reduce",3);
    parsing_table[6][IF] = Action((char*)"reduce",3);
    parsing_table[6][WHILE] = Action((char*)"reduce",3);
    parsing_table[6][RETURN] = Action((char*)"reduce",3);
    parsing_table[6][DECLS] = Action((char*)"goto",7);
    parsing_table[7][WORD] = Action((char*)"shift",14);
    parsing_table[7][INT] = Action((char*)"shift",16);
    parsing_table[7][CHAR] = Action((char*)"shift",17);
    parsing_table[7][IF] = Action((char*)"shift",12);
    parsing_table[7][WHILE] = Action((char*)"shift",13);
    parsing_table[7][RETURN] = Action((char*)"shift",15);
    parsing_table[7][DECL] = Action((char*)"goto",9);
    parsing_table[7][VTYPE] = Action((char*)"goto",11);
    parsing_table[7][SLIST] = Action((char*)"goto",8);
    parsing_table[7][STAT] = Action((char*)"goto",10);
    parsing_table[8][WORD] = Action((char*)"shift",14);
    parsing_table[8][MCPT] = Action((char*)"shift",18);
    parsing_table[8][IF] = Action((char*)"shift",12);
    parsing_table[8][WHILE] = Action((char*)"shift",13);
    parsing_table[8][RETURN] = Action((char*)"shift",15);
    parsing_table[8][STAT] = Action((char*)"goto",19);
    parsing_table[9][WORD] = Action((char*)"reduce",2);
    parsing_table[9][INT] = Action((char*)"reduce",2);
    parsing_table[9][CHAR] = Action((char*)"reduce",2);
    parsing_table[9][IF] = Action((char*)"reduce",2);
    parsing_table[9][WHILE] = Action((char*)"reduce",2);
    parsing_table[9][RETURN] = Action((char*)"reduce",2);
    parsing_table[10][WORD] = Action((char*)"reduce",12);
    parsing_table[10][MCPT] = Action((char*)"reduce",12);
    parsing_table[10][IF] = Action((char*)"reduce",12);
    parsing_table[10][WHILE] = Action((char*)"reduce",12);
    parsing_table[10][RETURN] = Action((char*)"reduce",12);
    parsing_table[11][WORD] = Action((char*)"shift",21);
    parsing_table[11][WORDS] = Action((char*)"goto",20);
    parsing_table[12][WORD] = Action((char*)"shift",27);
    parsing_table[12][NUM] = Action((char*)"shift",26);
    parsing_table[12][COND] = Action((char*)"goto",22);
    parsing_table[12][EXPR] = Action((char*)"goto",23);
    parsing_table[12][TERM] = Action((char*)"goto",24);
    parsing_table[12][FACT] = Action((char*)"goto",25);
    parsing_table[13][WORD] = Action((char*)"shift",27);
    parsing_table[13][NUM] = Action((char*)"shift",26);
    parsing_table[13][COND] = Action((char*)"goto",28);
    parsing_table[13][EXPR] = Action((char*)"goto",29);
    parsing_table[13][TERM] = Action((char*)"goto",24);
    parsing_table[13][FACT] = Action((char*)"goto",25);
    parsing_table[14][ASGN] = Action((char*)"shift",30);
    parsing_table[15][WORD] = Action((char*)"shift",35);
    parsing_table[15][NUM] = Action((char*)"shift",34);
    parsing_table[15][EXPR] = Action((char*)"goto",31);
    parsing_table[15][TERM] = Action((char*)"goto",32);
    parsing_table[15][FACT] = Action((char*)"goto",33);
    parsing_table[16][WORD] = Action((char*)"reduce",7);
    parsing_table[17][WORD] = Action((char*)"reduce",8);
    parsing_table[18][END] = Action((char*)"reduce",9);
    parsing_table[19][WORD] = Action((char*)"reduce",11);
    parsing_table[19][MCPT] = Action((char*)"reduce",11);
    parsing_table[19][IF] = Action((char*)"reduce",11);
    parsing_table[19][WHILE] = Action((char*)"reduce",11);
    parsing_table[19][RETURN] = Action((char*)"reduce",11);
    parsing_table[20][SEMICOL] = Action((char*)"shift",36);
    parsing_table[20][COM] = Action((char*)"shift",37);
    parsing_table[21][SEMICOL] = Action((char*)"reduce",6);
    parsing_table[21][COM] = Action((char*)"reduce",6);
    parsing_table[22][THEN] = Action((char*)"shift",38);
    parsing_table[23][GT] = Action((char*)"shift",39);
    parsing_table[23][EQ] = Action((char*)"shift",40);
    parsing_table[24][GT] = Action((char*)"reduce",19);
    parsing_table[24][EQ] = Action((char*)"reduce",19);
    parsing_table[24][PLUS] = Action((char*)"shift",41);
    parsing_table[25][GT] = Action((char*)"reduce",21);
    parsing_table[25][EQ] = Action((char*)"reduce",21);
    parsing_table[25][PLUS] = Action((char*)"reduce",21);
    parsing_table[25][MUL] = Action((char*)"shift",42);
    parsing_table[26][GT] = Action((char*)"reduce",23);
    parsing_table[26][EQ] = Action((char*)"reduce",23);
    parsing_table[26][PLUS] = Action((char*)"reduce",23);
    parsing_table[26][MUL] = Action((char*)"reduce",23);
    parsing_table[27][GT] = Action((char*)"reduce",24);
    parsing_table[27][EQ] = Action((char*)"reduce",24);
    parsing_table[27][PLUS] = Action((char*)"reduce",24);
    parsing_table[27][MUL] = Action((char*)"reduce",24);
    parsing_table[28][WORD] = Action((char*)"reduce",10);
    parsing_table[28][MOPT] = Action((char*)"shift",44);
    parsing_table[28][MCPT] = Action((char*)"reduce",10);
    parsing_table[28][IF] = Action((char*)"reduce",10);
    parsing_table[28][WHILE] = Action((char*)"reduce",10);
    parsing_table[28][RETURN] = Action((char*)"reduce",10);
    parsing_table[28][BLOCK] = Action((char*)"goto",43);
    parsing_table[29][GT] = Action((char*)"shift",45);
    parsing_table[29][EQ] = Action((char*)"shift",46);
    parsing_table[30][WORD] = Action((char*)"shift",35);
    parsing_table[30][NUM] = Action((char*)"shift",34);
    parsing_table[30][EXPR] = Action((char*)"goto",47);
    parsing_table[30][TERM] = Action((char*)"goto",32);
    parsing_table[30][FACT] = Action((char*)"goto",33);
    parsing_table[31][SEMICOL] = Action((char*)"shift",48);
    parsing_table[32][SEMICOL] = Action((char*)"reduce",19);
    parsing_table[32][PLUS] = Action((char*)"shift",49);
    parsing_table[33][SEMICOL] = Action((char*)"reduce",21);
    parsing_table[33][PLUS] = Action((char*)"reduce",21);
    parsing_table[33][MUL] = Action((char*)"shift",50);
    parsing_table[34][SEMICOL] = Action((char*)"reduce",23);
    parsing_table[34][PLUS] = Action((char*)"reduce",23);
    parsing_table[34][MUL] = Action((char*)"reduce",23);
    parsing_table[35][SEMICOL] = Action((char*)"reduce",24);
    parsing_table[35][PLUS] = Action((char*)"reduce",24);
    parsing_table[35][MUL] = Action((char*)"reduce",24);
    parsing_table[36][WORD] = Action((char*)"reduce",4);
    parsing_table[36][INT] = Action((char*)"reduce",4);
    parsing_table[36][CHAR] = Action((char*)"reduce",4);
    parsing_table[36][IF] = Action((char*)"reduce",4);
    parsing_table[36][WHILE] = Action((char*)"reduce",4);
    parsing_table[36][RETURN] = Action((char*)"reduce",4);
    parsing_table[37][WORD] = Action((char*)"shift",51);
    parsing_table[38][MOPT] = Action((char*)"shift",53);
    parsing_table[38][ELSE] = Action((char*)"reduce",10);
    parsing_table[38][BLOCK] = Action((char*)"goto",52);
    parsing_table[39][WORD] = Action((char*)"shift",58);
    parsing_table[39][NUM] = Action((char*)"shift",57);
    parsing_table[39][EXPR] = Action((char*)"goto",54);
    parsing_table[39][TERM] = Action((char*)"goto",55);
    parsing_table[39][FACT] = Action((char*)"goto",56);
    parsing_table[40][WORD] = Action((char*)"shift",58);
    parsing_table[40][NUM] = Action((char*)"shift",57);
    parsing_table[40][EXPR] = Action((char*)"goto",59);
    parsing_table[40][TERM] = Action((char*)"goto",55);
    parsing_table[40][FACT] = Action((char*)"goto",56);
    parsing_table[41][WORD] = Action((char*)"shift",63);
    parsing_table[41][NUM] = Action((char*)"shift",62);
    parsing_table[41][TERM] = Action((char*)"goto",60);
    parsing_table[41][FACT] = Action((char*)"goto",61);
    parsing_table[42][WORD] = Action((char*)"shift",66);
    parsing_table[42][NUM] = Action((char*)"shift",65);
    parsing_table[42][FACT] = Action((char*)"goto",64);
    parsing_table[43][WORD] = Action((char*)"reduce",14);
    parsing_table[43][MCPT] = Action((char*)"reduce",14);
    parsing_table[43][IF] = Action((char*)"reduce",14);
    parsing_table[43][WHILE] = Action((char*)"reduce",14);
    parsing_table[43][RETURN] = Action((char*)"reduce",14);
    parsing_table[44][WORD] = Action((char*)"reduce",3);
    parsing_table[44][INT] = Action((char*)"reduce",3);
    parsing_table[44][CHAR] = Action((char*)"reduce",3);
    parsing_table[44][IF] = Action((char*)"reduce",3);
    parsing_table[44][WHILE] = Action((char*)"reduce",3);
    parsing_table[44][RETURN] = Action((char*)"reduce",3);
    parsing_table[44][DECLS] = Action((char*)"goto",67);
    parsing_table[45][WORD] = Action((char*)"shift",72);
    parsing_table[45][NUM] = Action((char*)"shift",71);
    parsing_table[45][EXPR] = Action((char*)"goto",68);
    parsing_table[45][TERM] = Action((char*)"goto",69);
    parsing_table[45][FACT] = Action((char*)"goto",70);
    parsing_table[46][WORD] = Action((char*)"shift",72);
    parsing_table[46][NUM] = Action((char*)"shift",71);
    parsing_table[46][EXPR] = Action((char*)"goto",73);
    parsing_table[46][TERM] = Action((char*)"goto",69);
    parsing_table[46][FACT] = Action((char*)"goto",70);
    parsing_table[47][SEMICOL] = Action((char*)"shift",74);
    parsing_table[48][WORD] = Action((char*)"reduce",16);
    parsing_table[48][MCPT] = Action((char*)"reduce",16);
    parsing_table[48][IF] = Action((char*)"reduce",16);
    parsing_table[48][WHILE] = Action((char*)"reduce",16);
    parsing_table[48][RETURN] = Action((char*)"reduce",16);
    parsing_table[49][WORD] = Action((char*)"shift",78);
    parsing_table[49][NUM] = Action((char*)"shift",77);
    parsing_table[49][TERM] = Action((char*)"goto",75);
    parsing_table[49][FACT] = Action((char*)"goto",76);
    parsing_table[50][WORD] = Action((char*)"shift",81);
    parsing_table[50][NUM] = Action((char*)"shift",80);
    parsing_table[50][FACT] = Action((char*)"goto",79);
    parsing_table[51][SEMICOL] = Action((char*)"reduce",5);
    parsing_table[51][COM] = Action((char*)"reduce",5);
    parsing_table[52][ELSE] = Action((char*)"shift",82);
    parsing_table[53][WORD] = Action((char*)"reduce",3);
    parsing_table[53][INT] = Action((char*)"reduce",3);
    parsing_table[53][CHAR] = Action((char*)"reduce",3);
    parsing_table[53][IF] = Action((char*)"reduce",3);
    parsing_table[53][WHILE] = Action((char*)"reduce",3);
    parsing_table[53][RETURN] = Action((char*)"reduce",3);
    parsing_table[53][DECLS] = Action((char*)"goto",83);
    parsing_table[54][THEN] = Action((char*)"reduce",17);
    parsing_table[55][THEN] = Action((char*)"reduce",19);
    parsing_table[55][PLUS] = Action((char*)"shift",84);
    parsing_table[56][THEN] = Action((char*)"reduce",21);
    parsing_table[56][PLUS] = Action((char*)"reduce",21);
    parsing_table[56][MUL] = Action((char*)"shift",85);
    parsing_table[57][THEN] = Action((char*)"reduce",23);
    parsing_table[57][PLUS] = Action((char*)"reduce",23);
    parsing_table[57][MUL] = Action((char*)"reduce",23);
    parsing_table[58][THEN] = Action((char*)"reduce",24);
    parsing_table[58][PLUS] = Action((char*)"reduce",24);
    parsing_table[58][MUL] = Action((char*)"reduce",24);
    parsing_table[59][THEN] = Action((char*)"reduce",18);
    parsing_table[60][GT] = Action((char*)"reduce",20);
    parsing_table[60][EQ] = Action((char*)"reduce",20);
    parsing_table[61][GT] = Action((char*)"reduce",21);
    parsing_table[61][EQ] = Action((char*)"reduce",21);
    parsing_table[61][MUL] = Action((char*)"shift",86);
    parsing_table[62][GT] = Action((char*)"reduce",23);
    parsing_table[62][EQ] = Action((char*)"reduce",23);
    parsing_table[62][MUL] = Action((char*)"reduce",23);
    parsing_table[63][GT] = Action((char*)"reduce",24);
    parsing_table[63][EQ] = Action((char*)"reduce",24);
    parsing_table[63][MUL] = Action((char*)"reduce",24);
    parsing_table[64][GT] = Action((char*)"reduce",22);
    parsing_table[64][EQ] = Action((char*)"reduce",22);
    parsing_table[64][PLUS] = Action((char*)"reduce",22);
    parsing_table[65][GT] = Action((char*)"reduce",23);
    parsing_table[65][EQ] = Action((char*)"reduce",23);
    parsing_table[65][PLUS] = Action((char*)"reduce",23);
    parsing_table[66][GT] = Action((char*)"reduce",24);
    parsing_table[66][EQ] = Action((char*)"reduce",24);
    parsing_table[66][PLUS] = Action((char*)"reduce",24);
    parsing_table[67][WORD] = Action((char*)"shift",14);
    parsing_table[67][INT] = Action((char*)"shift",16);
    parsing_table[67][CHAR] = Action((char*)"shift",17);
    parsing_table[67][IF] = Action((char*)"shift",12);
    parsing_table[67][WHILE] = Action((char*)"shift",13);
    parsing_table[67][RETURN] = Action((char*)"shift",15);
    parsing_table[67][DECL] = Action((char*)"goto",9);
    parsing_table[67][VTYPE] = Action((char*)"goto",11);
    parsing_table[67][SLIST] = Action((char*)"goto",87);
    parsing_table[67][STAT] = Action((char*)"goto",10);
    parsing_table[68][WORD] = Action((char*)"reduce",17);
    parsing_table[68][MOPT] = Action((char*)"reduce",17);
    parsing_table[68][MCPT] = Action((char*)"reduce",17);
    parsing_table[68][IF] = Action((char*)"reduce",17);
    parsing_table[68][WHILE] = Action((char*)"reduce",17);
    parsing_table[68][RETURN] = Action((char*)"reduce",17);
    parsing_table[69][WORD] = Action((char*)"reduce",19);
    parsing_table[69][MOPT] = Action((char*)"reduce",19);
    parsing_table[69][MCPT] = Action((char*)"reduce",19);
    parsing_table[69][IF] = Action((char*)"reduce",19);
    parsing_table[69][WHILE] = Action((char*)"reduce",19);
    parsing_table[69][RETURN] = Action((char*)"reduce",19);
    parsing_table[69][PLUS] = Action((char*)"shift",88);
    parsing_table[70][WORD] = Action((char*)"reduce",21);
    parsing_table[70][MOPT] = Action((char*)"reduce",21);
    parsing_table[70][MCPT] = Action((char*)"reduce",21);
    parsing_table[70][IF] = Action((char*)"reduce",21);
    parsing_table[70][WHILE] = Action((char*)"reduce",21);
    parsing_table[70][RETURN] = Action((char*)"reduce",21);
    parsing_table[70][PLUS] = Action((char*)"reduce",21);
    parsing_table[70][MUL] = Action((char*)"shift",89);
    parsing_table[71][WORD] = Action((char*)"reduce",23);
    parsing_table[71][MOPT] = Action((char*)"reduce",23);
    parsing_table[71][MCPT] = Action((char*)"reduce",23);
    parsing_table[71][IF] = Action((char*)"reduce",23);
    parsing_table[71][WHILE] = Action((char*)"reduce",23);
    parsing_table[71][RETURN] = Action((char*)"reduce",23);
    parsing_table[71][PLUS] = Action((char*)"reduce",23);
    parsing_table[71][MUL] = Action((char*)"reduce",23);
    parsing_table[72][WORD] = Action((char*)"reduce",24);
    parsing_table[72][MOPT] = Action((char*)"reduce",24);
    parsing_table[72][MCPT] = Action((char*)"reduce",24);
    parsing_table[72][IF] = Action((char*)"reduce",24);
    parsing_table[72][WHILE] = Action((char*)"reduce",24);
    parsing_table[72][RETURN] = Action((char*)"reduce",24);
    parsing_table[72][PLUS] = Action((char*)"reduce",24);
    parsing_table[72][MUL] = Action((char*)"reduce",24);
    parsing_table[73][WORD] = Action((char*)"reduce",18);
    parsing_table[73][MOPT] = Action((char*)"reduce",18);
    parsing_table[73][MCPT] = Action((char*)"reduce",18);
    parsing_table[73][IF] = Action((char*)"reduce",18);
    parsing_table[73][WHILE] = Action((char*)"reduce",18);
    parsing_table[73][RETURN] = Action((char*)"reduce",18);
    parsing_table[74][WORD] = Action((char*)"reduce",15);
    parsing_table[74][MCPT] = Action((char*)"reduce",15);
    parsing_table[74][IF] = Action((char*)"reduce",15);
    parsing_table[74][WHILE] = Action((char*)"reduce",15);
    parsing_table[74][RETURN] = Action((char*)"reduce",15);
    parsing_table[75][SEMICOL] = Action((char*)"reduce",20);
    parsing_table[76][SEMICOL] = Action((char*)"reduce",21);
    parsing_table[76][MUL] = Action((char*)"shift",90);
    parsing_table[77][SEMICOL] = Action((char*)"reduce",23);
    parsing_table[77][MUL] = Action((char*)"reduce",23);
    parsing_table[78][SEMICOL] = Action((char*)"reduce",24);
    parsing_table[78][MUL] = Action((char*)"reduce",24);
    parsing_table[79][SEMICOL] = Action((char*)"reduce",22);
    parsing_table[79][PLUS] = Action((char*)"reduce",22);
    parsing_table[80][SEMICOL] = Action((char*)"reduce",23);
    parsing_table[80][PLUS] = Action((char*)"reduce",23);
    parsing_table[81][SEMICOL] = Action((char*)"reduce",24);
    parsing_table[81][PLUS] = Action((char*)"reduce",24);
    parsing_table[82][WORD] = Action((char*)"reduce",10);
    parsing_table[82][MOPT] = Action((char*)"shift",44);
    parsing_table[82][MCPT] = Action((char*)"reduce",10);
    parsing_table[82][IF] = Action((char*)"reduce",10);
    parsing_table[82][WHILE] = Action((char*)"reduce",10);
    parsing_table[82][RETURN] = Action((char*)"reduce",10);
    parsing_table[82][BLOCK] = Action((char*)"goto",91);
    parsing_table[83][WORD] = Action((char*)"shift",14);
    parsing_table[83][INT] = Action((char*)"shift",16);
    parsing_table[83][CHAR] = Action((char*)"shift",17);
    parsing_table[83][IF] = Action((char*)"shift",12);
    parsing_table[83][WHILE] = Action((char*)"shift",13);
    parsing_table[83][RETURN] = Action((char*)"shift",15);
    parsing_table[83][DECL] = Action((char*)"goto",9);
    parsing_table[83][VTYPE] = Action((char*)"goto",11);
    parsing_table[83][SLIST] = Action((char*)"goto",92);
    parsing_table[83][STAT] = Action((char*)"goto",10);
    parsing_table[84][WORD] = Action((char*)"shift",96);
    parsing_table[84][NUM] = Action((char*)"shift",95);
    parsing_table[84][TERM] = Action((char*)"goto",93);
    parsing_table[84][FACT] = Action((char*)"goto",94);
    parsing_table[85][WORD] = Action((char*)"shift",99);
    parsing_table[85][NUM] = Action((char*)"shift",98);
    parsing_table[85][FACT] = Action((char*)"goto",97);
    parsing_table[86][WORD] = Action((char*)"shift",102);
    parsing_table[86][NUM] = Action((char*)"shift",101);
    parsing_table[86][FACT] = Action((char*)"goto",100);
    parsing_table[87][WORD] = Action((char*)"shift",14);
    parsing_table[87][MCPT] = Action((char*)"shift",103);
    parsing_table[87][IF] = Action((char*)"shift",12);
    parsing_table[87][WHILE] = Action((char*)"shift",13);
    parsing_table[87][RETURN] = Action((char*)"shift",15);
    parsing_table[87][STAT] = Action((char*)"goto",19);
    parsing_table[88][WORD] = Action((char*)"shift",107);
    parsing_table[88][NUM] = Action((char*)"shift",106);
    parsing_table[88][TERM] = Action((char*)"goto",104);
    parsing_table[88][FACT] = Action((char*)"goto",105);
    parsing_table[89][WORD] = Action((char*)"shift",110);
    parsing_table[89][NUM] = Action((char*)"shift",109);
    parsing_table[89][FACT] = Action((char*)"goto",108);
    parsing_table[90][WORD] = Action((char*)"shift",113);
    parsing_table[90][NUM] = Action((char*)"shift",112);
    parsing_table[90][FACT] = Action((char*)"goto",111);
    parsing_table[91][WORD] = Action((char*)"reduce",13);
    parsing_table[91][MCPT] = Action((char*)"reduce",13);
    parsing_table[91][IF] = Action((char*)"reduce",13);
    parsing_table[91][WHILE] = Action((char*)"reduce",13);
    parsing_table[91][RETURN] = Action((char*)"reduce",13);
    parsing_table[92][WORD] = Action((char*)"shift",14);
    parsing_table[92][MCPT] = Action((char*)"shift",114);
    parsing_table[92][IF] = Action((char*)"shift",12);
    parsing_table[92][WHILE] = Action((char*)"shift",13);
    parsing_table[92][RETURN] = Action((char*)"shift",15);
    parsing_table[92][STAT] = Action((char*)"goto",19);
    parsing_table[93][THEN] = Action((char*)"reduce",20);
    parsing_table[94][THEN] = Action((char*)"reduce",21);
    parsing_table[94][MUL] = Action((char*)"shift",115);
    parsing_table[95][THEN] = Action((char*)"reduce",23);
    parsing_table[95][MUL] = Action((char*)"reduce",23);
    parsing_table[96][THEN] = Action((char*)"reduce",24);
    parsing_table[96][MUL] = Action((char*)"reduce",24);
    parsing_table[97][THEN] = Action((char*)"reduce",22);
    parsing_table[97][PLUS] = Action((char*)"reduce",22);
    parsing_table[98][THEN] = Action((char*)"reduce",23);
    parsing_table[98][PLUS] = Action((char*)"reduce",23);
    parsing_table[99][THEN] = Action((char*)"reduce",24);
    parsing_table[99][PLUS] = Action((char*)"reduce",24);
    parsing_table[100][GT] = Action((char*)"reduce",22);
    parsing_table[100][EQ] = Action((char*)"reduce",22);
    parsing_table[101][GT] = Action((char*)"reduce",23);
    parsing_table[101][EQ] = Action((char*)"reduce",23);
    parsing_table[102][GT] = Action((char*)"reduce",24);
    parsing_table[102][EQ] = Action((char*)"reduce",24);
    parsing_table[103][WORD] = Action((char*)"reduce",9);
    parsing_table[103][MCPT] = Action((char*)"reduce",9);
    parsing_table[103][IF] = Action((char*)"reduce",9);
    parsing_table[103][WHILE] = Action((char*)"reduce",9);
    parsing_table[103][RETURN] = Action((char*)"reduce",9);
    parsing_table[104][WORD] = Action((char*)"reduce",20);
    parsing_table[104][MOPT] = Action((char*)"reduce",20);
    parsing_table[104][MCPT] = Action((char*)"reduce",20);
    parsing_table[104][IF] = Action((char*)"reduce",20);
    parsing_table[104][WHILE] = Action((char*)"reduce",20);
    parsing_table[104][RETURN] = Action((char*)"reduce",20);
    parsing_table[105][WORD] = Action((char*)"reduce",21);
    parsing_table[105][MOPT] = Action((char*)"reduce",21);
    parsing_table[105][MCPT] = Action((char*)"reduce",21);
    parsing_table[105][IF] = Action((char*)"reduce",21);
    parsing_table[105][WHILE] = Action((char*)"reduce",21);
    parsing_table[105][RETURN] = Action((char*)"reduce",21);
    parsing_table[105][MUL] = Action((char*)"shift",116);
    parsing_table[106][WORD] = Action((char*)"reduce",23);
    parsing_table[106][MOPT] = Action((char*)"reduce",23);
    parsing_table[106][MCPT] = Action((char*)"reduce",23);
    parsing_table[106][IF] = Action((char*)"reduce",23);
    parsing_table[106][WHILE] = Action((char*)"reduce",23);
    parsing_table[106][RETURN] = Action((char*)"reduce",23);
    parsing_table[106][MUL] = Action((char*)"reduce",23);
    parsing_table[107][WORD] = Action((char*)"reduce",24);
    parsing_table[107][MOPT] = Action((char*)"reduce",24);
    parsing_table[107][MCPT] = Action((char*)"reduce",24);
    parsing_table[107][IF] = Action((char*)"reduce",24);
    parsing_table[107][WHILE] = Action((char*)"reduce",24);
    parsing_table[107][RETURN] = Action((char*)"reduce",24);
    parsing_table[107][MUL] = Action((char*)"reduce",24);
    parsing_table[108][WORD] = Action((char*)"reduce",22);
    parsing_table[108][MOPT] = Action((char*)"reduce",22);
    parsing_table[108][MCPT] = Action((char*)"reduce",22);
    parsing_table[108][IF] = Action((char*)"reduce",22);
    parsing_table[108][WHILE] = Action((char*)"reduce",22);
    parsing_table[108][RETURN] = Action((char*)"reduce",22);
    parsing_table[108][PLUS] = Action((char*)"reduce",22);
    parsing_table[109][WORD] = Action((char*)"reduce",23);
    parsing_table[109][MOPT] = Action((char*)"reduce",23);
    parsing_table[109][MCPT] = Action((char*)"reduce",23);
    parsing_table[109][IF] = Action((char*)"reduce",23);
    parsing_table[109][WHILE] = Action((char*)"reduce",23);
    parsing_table[109][RETURN] = Action((char*)"reduce",23);
    parsing_table[109][PLUS] = Action((char*)"reduce",23);
    parsing_table[110][WORD] = Action((char*)"reduce",24);
    parsing_table[110][MOPT] = Action((char*)"reduce",24);
    parsing_table[110][MCPT] = Action((char*)"reduce",24);
    parsing_table[110][IF] = Action((char*)"reduce",24);
    parsing_table[110][WHILE] = Action((char*)"reduce",24);
    parsing_table[110][RETURN] = Action((char*)"reduce",24);
    parsing_table[110][PLUS] = Action((char*)"reduce",24);
    parsing_table[111][SEMICOL] = Action((char*)"reduce",22);
    parsing_table[112][SEMICOL] = Action((char*)"reduce",23);
    parsing_table[113][SEMICOL] = Action((char*)"reduce",24);
    parsing_table[114][ELSE] = Action((char*)"reduce",9);
    parsing_table[115][WORD] = Action((char*)"shift",119);
    parsing_table[115][NUM] = Action((char*)"shift",118);
    parsing_table[115][FACT] = Action((char*)"goto",117);
    parsing_table[116][WORD] = Action((char*)"shift",122);
    parsing_table[116][NUM] = Action((char*)"shift",121);
    parsing_table[116][FACT] = Action((char*)"goto",120);
    parsing_table[117][THEN] = Action((char*)"reduce",22);
    parsing_table[118][THEN] = Action((char*)"reduce",23);
    parsing_table[119][THEN] = Action((char*)"reduce",24);
    parsing_table[120][WORD] = Action((char*)"reduce",22);
    parsing_table[120][MOPT] = Action((char*)"reduce",22);
    parsing_table[120][MCPT] = Action((char*)"reduce",22);
    parsing_table[120][IF] = Action((char*)"reduce",22);
    parsing_table[120][WHILE] = Action((char*)"reduce",22);
    parsing_table[120][RETURN] = Action((char*)"reduce",22);
    
    parsing_table[121][WORD] = Action((char*)"reduce",23);
    parsing_table[121][MOPT] = Action((char*)"reduce",23);
    parsing_table[121][MCPT] = Action((char*)"reduce",23);
    parsing_table[121][IF] = Action((char*)"reduce",23);
    parsing_table[121][WHILE] = Action((char*)"reduce",23);
    parsing_table[121][RETURN] = Action((char*)"reduce",23);
    
    parsing_table[122][WORD] = Action((char*)"reduce",24);
    parsing_table[122][MOPT] = Action((char*)"reduce",24);
    parsing_table[122][MCPT] = Action((char*)"reduce",24);
    parsing_table[122][IF] = Action((char*)"reduce",24);
    parsing_table[122][WHILE] = Action((char*)"reduce",24);
    parsing_table[122][RETURN] = Action((char*)"reduce",24);
}
