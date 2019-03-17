#include <stdio.h>
#include <stdlib.h>

#include "4linha.h"

int main(){
    BOARD b = new_board(NULL,0);
    while(TRUE){
        print_board(b);
        int i=-1;
        while(i<1 || i>7){
            printf("Coluna: ");
            scanf("%d", &i);    
        }
        if(move(b,i-1,-1)==NULL){
            continue;
        }
        b=move(b,i-1,-1);
        
        if(score(b)==-512){
            print_board(b);
            printf("Ganhou\n");
            return 1;
        }
        b=move(b,minimax_decision(b),1);
        printf("%d\n",score(b));
        if(score(b)==512){
            print_board(b);
            printf("Perdeu\n");
            return 1;
        }
    }
    return 0;

}