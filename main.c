#include <stdio.h>
#include <stdlib.h>

#include "4linha.h"

int main(){
    BOARD b = new_board(NULL);
    move(b, 6, 1);
    move(b, 1, -1);
    move(b, 2, -1);
    move(b, 2, -1);
    move(b, 4, 1);
    move(b, 6, 1);
    move(b, 5, -1);
    print_board(b);
    printf("\n");

    printf("%d\n",score(b));
    return 1;
}