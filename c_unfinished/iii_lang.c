//UNFINISHED, I was bored
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Token{
    int func;
    char data[5];
    struct Token* next_token;
} Token;

typedef struct TokenList{
    struct Token* next_token;
} TokenList;
init_token_list(TokenList* token_list){
    token_list->next_token=NULL;
}
typedef struct Node{
    char val[10];
    int func;
    struct Node* left;
    struct Node* right;
}
typedef struct AST {
    struct Node* left;
    struct Node* right;
} AST;

#define MEM_LENGTH 420
typedef struct memory{
    int memlist[MEM_LENGTH];
    int ptr_index;
} memory;
memory* global_mem=NULL;
void init_memory(){
    global_mem=(memory*) malloc(sizeof(memory));
    global_mem-> memlist={0};
    global_mem-> ptr_index=0;
}
void move_pointer(int amm){
    amm=amm%REGISTER_SIZE;
    reg_pointer+=amm;
    if(reg_pointer<0){
        reg_pointer+=amm;
    }
}

int build_ast(char str[]){

}

int tokenize(TokenList* token_list,char str[]){
    int i=0;
    char cur_command[5]=""; //4 iter
    int c_index=0;
    while(str[i]!='\0'){
        if(str[i]=='|'){
            cur_command[4]='\0';
            append_token(token_list,cur_command);
            cur_command="";
            c_index=0;
        } else {
            cur_command[c_index]=str[i];
            c_index++;
        }
        i++;
    }

}
void append_token(TokenList* token_list,char tkn[]){
    Token* newtoken=(Token*) malloc(sizeof(Token));
    newtoken->next_token=NULL;
    newtoken->func=0;
    newtoken->data="";
    strcpy(newtoken->data,tkn);
    switch(tkn){
        case "IIII":
            newtoken.func=1;
            break;
        case "Illl":
            newtoken.func=2; //move pointer to left
            break;
        case "lllI":
            newtoken.func=3; //move pointer to right
            break;
        case "llll":
            newtoken.func=4; //print data in ihelding
            break;
        case "IllI":
            newtoken.func=5; //start of cycle, when the current mem is not 0 jump to this
            break;
        case "lIIl":
            newtoken.func=6; //End of cycle
            break;
    }

    if(token_list->next_token==NULL){
        token_list->next_token=newtoken;
    } else {
        Token* current=token_list->next_token;
        while(current!=NULL){
            current=current->next_token;
        }
        current=newtoken;
    }
}
int main(void) {
    char ex="";    
    return 0;
}