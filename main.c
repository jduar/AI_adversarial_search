#include <stdio.h>
#include <stdlib.h>

#include "4linha.h"

int main(){
  char piece;
  printf("* Let's play Connect Four!\n");
  printf("**************************\n");
  printf("* Pick your piece! [X/O]\n");
  scanf("%c", &piece);
  while (!(piece == 'X' || piece == 'O')) {
    printf("* Wrong choice! Only X or O are playable pieces.\n");
    printf("* Pick your piece! [X/O]\n");
    scanf(" %c", &piece);
  }
  printf("**************************\n");
  printf("* You've picked %c as your piece. Let's begin. Good luck.\n", piece);
  printf("**************************\n");

  
  BOARD b = new_board(NULL, 0, piece);
    while(TRUE){
        print_board(b);
        int i = -1;
        while(i<1 || i>7){
            printf("Coluna: ");
            scanf("%d", &i);    
        }
        if(move(b, i-1, -1) == NULL){
	    continue;
        }
        b = move(b, i-1, -1);
        
        if(score(b) == -512){
            print_board(b);
            printf("Ganhou\n");
            return 1;
        }
        b = move(b, minimax_decision(b), 1);
        printf("%d\n", score(b));
        if(score(b) == 512){
            print_board(b);
            printf("Perdeu\n");
            return 1;
        }
    }
    return 0;

}
