#include <stdio.h>
#include <stdlib.h>

#include "4linha.h"

int main(){
    BOARD b = new_board(NULL,4,4);
    print_board(b);
    printf("\n");
    BOARD b1 = new_board(NULL,6,6);
    print_board(b1);
    move(b, 2, 1);
    printf("\n");
    print_board(b);
    move(b, 1, -1);
    printf("\n");
    print_board(b);
    return 1;
}