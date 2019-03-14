#include <stdio.h>
#include <stdlib.h>

typedef enum {FALSE,TRUE} BOOL;

typedef struct board{
    int* board;
} *BOARD;

BOARD new_board (int* board){
    BOARD b = (BOARD) malloc(sizeof(struct board));
    b->board = (int*) malloc(6*7 * sizeof(int));
    if (board==NULL){
        for (int i = 0; i<6*7; i++){
            b->board[i]=0;
        }
    }
    else{
        b->board = board;
    }
    return b;
}

void print_board(BOARD b){
    for(int i =0; i< 6; i++){
        for(int j = 0; j < 7; j++){
            if (b->board[i*7+j]==0){
                //0 vai ser celula por jogar
                printf("-");
            }
            else if (b->board[i*7+j]==1){
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

/* escolher coluna de 0 a 6, e jogada 1 para X e -1 para 0*/
int move(BOARD b,int c, int jogada){
    //return 1 se fogada for valida, 0 se for invalida (Exemplo: coluna cheia!)
    for (int i = 6-1; i>=0; i--){
        if(b->board[i*7+c]==0){
            b->board[i*7+c]=jogada;
            return 1;
        }
    }
    return 0;
}

int score(BOARD b){
    int res=0;
    int x, o;
    //linhas
    for(int i=0; i<6;i++){
        for(int j=0; j<4; j++){
            x=0;
            o=0;
            for(int k=0; k<4; k++){
                if(b->board[i*7+j+k] ==1){x++;}
                else if(b->board[i*7+j+k]==-1){o++;}
            }
            if((x>0 && o>0) || (x==0 && o==0)){continue;}
            else if(x==1){res+=1;}
            else if(x==2){res+=10;}
            else if(x==3){res+=50;}
            else if(x==4){return 512;}
            else if(o==1){res-=1;}
            else if(o==2){res-=10;}
            else if(o==3){res-=50;}
            else if(0==4){return -512;}
        }
    }
    //colunas
    for(int i=0; i<7;i++){
        for(int j=0; j<3; j++){
            x=0;
            o=0;
            for(int k=0; k<4; k++){
                if(b->board[i+(j+k)*7] ==1){x++;}
                else if(b->board[i+(j+k)*7]==-1){o++;}
            }
            if((x>0 && o>0) || (x==0 && o==0)){continue;}
            else if(x==1){res+=1;}
            else if(x==2){res+=10;}
            else if(x==3){res+=50;}
            else if(x==4){return 512;}
            else if(o==1){res-=1;}
            else if(o==2){res-=10;}
            else if(o==3){res-=50;}
            else if(0==4){return -512;}
        }
    }
    //diagonais
    for(int i=3; i<6; i++){
        for(int j=0; j<4; j++){
            x=0;
            o=0;
            for(int k=0; k<4; k++){
                if(b->board[(i-k)*7+j+k] ==1){x++;}
                else if(b->board[(i-k)*7+j+k]==-1){o++;}
            }
            if((x>0 && o>0) || (x==0 && o==0)){continue;}
            else if(x==1){res+=1;}
            else if(x==2){res+=10;}
            else if(x==3){res+=50;}
            else if(x==4){return 512;}
            else if(o==1){res-=1;}
            else if(o==2){res-=10;}
            else if(o==3){res-=50;}
            else if(0==4){return -512;}
        }
    }
    for(int i=3; i<6; i++){
        for(int j=3; j<7; j++){
            x=0;
            o=0;
            for(int k=0; k<4; k++){
                if(b->board[(i-k)*7+j-k] ==1){x++;}
                else if(b->board[(i-k)*7+j-k]==-1){o++;}
            }
            if((x>0 && o>0) || (x==0 && o==0)){continue;}
            else if(x==1){res+=1;}
            else if(x==2){res+=10;}
            else if(x==3){res+=50;}
            else if(x==4){return 512;}
            else if(o==1){res-=1;}
            else if(o==2){res-=10;}
            else if(o==3){res-=50;}
            else if(0==4){return -512;}
        }
    }
    
    return res;
}