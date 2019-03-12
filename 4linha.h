#include <stdio.h>
#include <stdlib.h>

typedef enum {FALSE,TRUE} BOOL;

typedef struct board{
    int linhas, colunas;
    int* board;
} *BOARD;

BOARD new_board (int* board, int l, int c){
    BOARD b = (BOARD) malloc(sizeof(struct board));
    b->linhas = l;
    b->colunas = c;
    b->board = (int*) malloc(l*c * sizeof(int));
    if (board==NULL){
        for (int i = 0; i<l*c; i++){
            b->board[i]=0;
        }
    }
    else{
        b->board = board;
    }
    return b;
}

void print_board(BOARD b){
    for(int i =0; i< b->linhas; i++){
        for(int j = 0; j < b->colunas; j++){
            if (b->board[i*b->linhas+j]==0){
                //0 vai ser celula por jogar
                printf("-");
            }
            else if (b->board[i*b->linhas+j]==1){
                // X vai ser inteiro 1
                printf("X");
            }
            else{
                // O vai ser inteiro -1
                printf("O");
            }
        }
        printf("\n");
    }
}


int move(BOARD b,int c, int jogada){
    //return 1 se fogada for valida, 0 se for invalida (Exemplo: coluna cheia!)
    for (int i = b->linhas-1; i>=0; i--){
        if(b->board[i*b->linhas+c-1]==0){
            b->board[i*b->linhas+c-1]=jogada;
            return 1;
        }
    }
    return 0;
}
