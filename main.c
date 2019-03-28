#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "4linha.h"
#include "minmax.h"
#include "alphabeta.h"


char piece() {
  /* Function to have the player pick the piece he wants to play with [X/O].*/
  char piece;
  printf("* Pick your piece! [X/O]\n");
  scanf(" %c", &piece);
  while (!(piece == 'X' || piece == 'O')) {
    printf("* Wrong choice! Only X or O are playable pieces.\n");
    printf("* Pick your piece! [X/O]\n");
    scanf(" %c", &piece);
  }
  printf("**************************\n");
  printf("* You've picked %c as your piece. Let's begin. Good luck.\n", piece);
  printf("**************************\n");
  return piece;
}


int main(){
  int algorithm;
  printf("* Let's play Connect Four!\n");
  printf("**************************\n");

  /* Picking the algorithm. */
  printf("* Which algorithm would you like to play against?\n");
  printf(" 1 - MinMax\n 2 - Alpha-beta\n 3 - Monte Carlo\n");
  scanf(" %d", &algorithm);

  while (!(algorithm == 1 || algorithm == 2 || algorithm == 3 || algorithm == 4)) {
      printf("* Wrong choice! The only algorithm choices are 1, 2 or 3.\n");
      scanf(" %d", &algorithm);
    }
  if (algorithm == 1) {
      /* The player picked the MinMax algorithm. */
      BOARD b = new_board(NULL, 0, piece());
      minmax(b);
  }
  else if (algorithm == 2) {
      /* The player picked the Alpha-beta algorithm. */
      BOARD b = new_board(NULL, 0, piece());
      alphabeta(b);
  }

  else if (algorithm == 3) {

  }

  else if (algorithm == 4){
      min_vs_alpha();
  }
}
