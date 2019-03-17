#include <stdio.h>
#include <stdlib.h>

typedef enum {FALSE,TRUE} BOOL;

typedef struct board{
    int* board;
    int depth;
} *BOARD;

BOARD new_board (int* board, int d);
void print_board(BOARD b);
BOARD move(BOARD b,int c, int jogada);
int score(BOARD b);
int min_value(BOARD b, int depth);
int max_value(BOARD b, int depth);
int minimax_decision(BOARD b);

BOARD new_board (int* board, int d){
    BOARD b = (BOARD) malloc(sizeof(struct board));
    b->board = (int*) malloc(6*7 * sizeof(int));
    if (board==NULL){
        for (int i = 0; i<6*7; i++){
            b->board[i]=0;
        }
    }
    else{
        for (int i = 0; i<6*7; i++){
            b->board[i]=board[i];
        }
    }
    b->depth=d;
    return b;
}

void print_board(BOARD b){
    for(int i =0; i< 6; i++){
        for(int j = 0; j < 7; j++){
            if (b->board[i*7+j]==0){
                //0 vai ser celula por jogar
                printf("- ");
            }
            else if (b->board[i*7+j]==1){
                // X vai ser inteiro 1
                printf("X ");
            }
            else{
                // O vai ser inteiro -1
                printf("O ");
            }
        }
        printf("\n");
    }
}

/* escolher coluna de 0 a 6, e jogada 1 para X e -1 para 0*/
BOARD move(BOARD b,int c, int jogada){
    BOARD aux = new_board(b->board, b->depth);
    //return 1 se fogada for valida, 0 se for invalida (Exemplo: coluna cheia!)
    for (int i = 6-1; i>=0; i--){
        if(aux->board[i*7+c]==0){
            aux->board[i*7+c]=jogada;
            aux->depth++;
            return aux;
        }
    }
    return NULL;
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
            else if(o==4){return -512;}
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
            else if(o==4){return -512;}
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
            else if(o==4){return -512;}
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
            else if(o==4){return -512;}
        }
    }
    
    return res;
}

int min_value(BOARD b, int depth){
    BOARD aux;
    int s_aux;
    int utility = score(b);
    if (utility>=512 || utility <=-512 || (utility==0 && b->depth>40) || b->depth>depth+5){
        return utility;
    }
    int v=600;
    for (int i=0; i<7; i++){
        aux=move(b, i, -1);
        if (aux!=NULL){
            s_aux=max_value(aux, depth);
            if (v>s_aux){
                v=s_aux;
            }
        }
    }
    return v;
}

int max_value(BOARD b, int depth){
    BOARD aux;
    int s_aux;
    int utility = score(b);
    if (utility>=512 || utility <=-512 || (utility==0 && b->depth>40) || b->depth>depth+5){
        return utility;
    }
    int v=-600;
    for (int i=0; i<7; i++){
        aux=move(b, i, 1);
        if (aux!=NULL){
            s_aux=min_value(aux, depth);
            if (v<s_aux){
                v=s_aux;
            }
        }
    }
    return v;
}

int minimax_decision(BOARD b){
    int v=-600, s_aux, jogada, depth=b->depth;
    BOARD aux;
    for (int i=0; i<7; i++){
        aux=move(b, i, 1);
        
        if (aux!=NULL){
            if (score(aux)==512){
                return i;
            }
            s_aux=min_value(aux, depth);
            if (v<s_aux){
                v=s_aux;
                jogada=i;
            }
        }
    }
    return jogada;
}