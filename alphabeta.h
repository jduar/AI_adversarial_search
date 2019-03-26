#include <stdio.h>

#include "4linha.h"

int alphabeta(BOARD b) {
    int first = -1;
    /* Deciding who moves first. */
    printf("Who will be playing first? (1 for PC, 0 for player)\n");
    scanf("%d", &first);
    while(!(first == 0 || first == 1)){
	printf("Who will be playing first? (1 for PC, 0 for player)\n");
	scanf("%d", &first);
    }
    if(first){
	b = move(b, ab_decision(b), 1);
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
	b = move(b, ab_decision(b), 1);
	if(score(b, 1) == 512){
	    print_board(b);
	    printf("**************************\n");
	    printf("Perdeu!\n");
	    return 1;
	}
    }
    return 0;
}
