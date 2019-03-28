#include <stdio.h>

#include "4linha.h"


/**
 * Choses who will be playing first, and implements the minimax algorithm
 * */
int minmax(BOARD b) {
    int first = -1;
    /* Deciding who moves first. */
    printf("Who will be playing first? (1 for PC, 0 for player)\n");
    scanf("%d", &first);
    while(!(first == 0 || first == 1)){
	printf("Who will be playing first? (1 for PC, 0 for player)\n");
	scanf("%d", &first);
    }
    if(first){
	b = move(b, minimax_decision(b), 1);
    }
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
        
	if(score(b, -1) == -512){
	    print_board(b);
	    printf("**************************\n");
	    printf("Ganhou!\n");
	    return 1;
	}
	b = move(b, minimax_decision(b), 1);
	if(score(b, 1) == 512){
	    print_board(b);
	    printf("**************************\n");
	    printf("Perdeu!\n");
	    return 1;
	}
    }
    return 0;
}

char piecema() {
  char piece;
  printf("Welcome to our surprise!!!!\nWe will put Minimax vs Alpha_Beta neck'a'neck. Place your bets\n* Pick Minimax's piece! [X/O]\n");
  scanf(" %c", &piece);
  while (!(piece == 'X' || piece == 'O')) {
    printf("* Wrong choice! Only X or O are playable pieces.\n");
    printf("* Pick Minimax's piece! [X/O]\n");
    scanf(" %c", &piece);
  }
  printf("**************************\n");
  printf("* You've picked %c as Minimax's piece. Let's begin. Good luck.\n", piece);
  printf("**************************\n");
  return piece;
}

int min_vs_alpha(){
	BOARD b = new_board(NULL, 0, piecema());
	int first = -1;
	printf("Who will be playing first? (0 for Minimax, 1 for Alpha_Beta)\n");
    scanf("%d", &first);
    while(!(first == 0 || first == 1)){
	printf("Who will be playing first? (0 for Minimax, 1 for Alpha_Beta)\n");
	scanf("%d", &first);
    }
    if(first){
	b = move(b, ab_decision(b), 1);
	print_board(b); 
    }
    while(TRUE){
	
	b = move(b, minimax_decision(b), -1);
    print_board(b);    
	if(score(b, -1) == -512){
	    printf("**************************\n");
	    printf("Ganhou o minimax!\n");
	    return 1;
	}
	b = move(b, ab_decision(b), 1);
	print_board(b);
	if(score(b, 1) == 512){
	    printf("**************************\n");
	    printf("Ganhou o Alpha beta!\n");
	    return 1;
	}
    }
    return 0;
}

