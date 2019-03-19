#include <stdio.h>
#include <stdlib.h>

typedef enum {FALSE,TRUE} BOOL;

typedef struct board{
    int* board;
    int depth;
  char piece; // X or O
} *BOARD;

BOARD new_board (int* board, int d, char piece);
void print_board(BOARD b);
BOARD move(BOARD b,int c, int jogada);
int score(BOARD b);
int min_value(BOARD b, int depth);
int max_value(BOARD b, int depth);
int minimax_decision(BOARD b);


BOARD new_board (int* board, int d, char piece){
  /* The board is represented by a matrix, in which
     1 stands for a bot move, -1 for a player move and
     0 represents an empty position.
     piece represents the pieces the player has chosen
     to play with (X or O).
  */
    BOARD b = (BOARD) malloc(sizeof(struct board));
    b->board = (int*) malloc(6*7 * sizeof(int));
    if (board == NULL){
        for (int i=0; i<6*7; i++){
            b->board[i] = 0;
        }
    }
    else{
        for (int i = 0; i<6*7; i++){
            b->board[i] = board[i];
        }
    }
    b->depth = d;
    b->piece = piece;
    return b;
}

void print_board(BOARD b){
    for(int i=0; i<6; i++){
        for(int j=0; j<7; j++){
            if (b->board[i*7+j] == 0){
	      // 0 is an empty cell.
	      printf("- ");
            }
            else if (b->board[i*7+j] == 1){
	      // 1 is a cell played by the bot.
	      // TODO: Improve piece behaviour so a if-else isn't needed.
	      if (b->piece == 'X') {
		printf("O ");
	      }
	      else {
                printf("X ");
	      }
            }
            else{
	      // -1 is a cell played by the player.
	      if (b->piece == 'X') {
		printf("X ");
	      }
	      else {
                printf("O ");
	      }
            }
        }
        printf("\n");
    }
}

/* Pick column from 0 to 6. 1 is a bot play, -1 is a user play. */
BOARD move(BOARD b,int c, int jogada){
  BOARD aux = new_board(b->board, b->depth, b->piece);
    // Returns 1 for a valid move, 0 for an invalid move.
    // Example: playing in a filled collumn returns an invalid move.
    for (int i=6-1; i>=0; i--){
        if(aux->board[i*7+c] == 0){
            aux->board[i*7+c] = jogada;
            aux->depth++;
            return aux;
        }
    }
    return NULL;
}

int score(BOARD b){
    int res = 0;
    int bot, player; // Counters for each players' points.
    //linhas
    for(int i=0; i<6;i++){
        for(int j=0; j<4; j++){
            bot = 0;
            player = 0;
            for(int k=0; k<4; k++){
                if(b->board[i*7+j+k] == 1){
		  bot++;
		}
                else if(b->board[i*7+j+k] == -1){
		  player++;
		}
            }
            if((bot>0 && player>0) || (bot==0 && player==0)){continue;}
            else if(bot == 1){res += 1;}
            else if(bot == 2){res += 10;}
            else if(bot == 3){res += 50;}
            else if(bot == 4){return 512;}
            else if(player == 1){res -= 1;}
            else if(player == 2){res -= 10;}
            else if(player == 3){res -= 50;}
            else if(player == 4){return -512;}
        }
    }
    //colunas
    for(int i=0; i<7; i++){
        for(int j=0; j<3; j++){
            bot = 0;
            player = 0;
            for(int k=0; k<4; k++){
                if(b->board[i+(j+k)*7] == 1){
		  bot++;
		}
                else if(b->board[i+(j+k)*7] == -1){
		  player++;
		}
            }
            if((bot>0 && player>0) || (bot==0 && player==0)){continue;}
            else if(bot == 1){res += 1;}
            else if(bot == 2){res += 10;}
            else if(bot == 3){res += 50;}
            else if(bot == 4){return 512;}
            else if(player == 1){res -= 1;}
            else if(player == 2){res -= 10;}
            else if(player == 3){res -= 50;}
            else if(player == 4){return -512;}
        }
    }
    //diagonais
    for(int i=3; i<6; i++){
        for(int j=0; j<4; j++){
            bot = 0;
            player = 0;
            for(int k=0; k<4; k++){
                if(b->board[(i-k)*7+j+k] == 1){
		  bot++;
		}
                else if(b->board[(i-k)*7+j+k]==-1){
		  player++;
		}
            }
            if((bot > 0 && player > 0) || (bot == 0 && player == 0)){continue;}
            else if(bot == 1){res += 1;}
            else if(bot == 2){res += 10;}
            else if(bot == 3){res += 50;}
            else if(bot == 4){return 512;}
            else if(player == 1){res -= 1;}
            else if(player == 2){res -= 10;}
            else if(player == 3){res -= 50;}
            else if(player == 4){return -512;}
        }
    }
    for(int i=3; i<6; i++){
        for(int j=3; j<7; j++){
            bot = 0;
            player = 0;
            for(int k=0; k<4; k++){
                if(b->board[(i-k)*7+j-k] == 1){
		  bot++;
		}
                else if(b->board[(i-k)*7+j-k] == -1){
		  player++;
		}
            }
            if((bot > 0 && player > 0) || (bot == 0 && player == 0)){continue;}
            else if(bot == 1){res += 1;}
            else if(bot == 2){res += 10;}
            else if(bot == 3){res += 50;}
            else if(bot == 4){return 512;}
            else if(player == 1){res -= 1;}
            else if(player == 2){res -= 10;}
            else if(player == 3){res -= 50;}
            else if(player == 4){return -512;}
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
