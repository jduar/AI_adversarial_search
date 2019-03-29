#include <math.h>

#include "mytree.h"

#define UCBCONSTANT 1

int random_number() {      
   /*
   for (int i=0; i<100; i++) {
       printf("%d\n", rand() % 7);
       } */
   
   return(rand() % 7);
}

int child_reward_sum(NODE node) {
    int sum = 0;
    for (int i=0; i<7; i++) {
	if (node->children[i] != NULL) {
	    sum = sum +
		node_get_reward(node->children[i]) +
		child_reward_sum(node->children[i]);
	}
    }
    return sum;
}

double ucb(NODE node) {
    double ucb;
    if (node->parent != NULL) {
	ucb = child_reward_sum(node) + UCBCONSTANT * (sqrt((2*log(node_get_visits(node->parent)))/node_get_visits(node)));
	return ucb;
    }
    else {
	ucb = child_reward_sum(node) + UCBCONSTANT * (sqrt((2/node_get_visits(node))));
	return ucb;
    }
}

NODE select_best(NODE node) {
    double max = -1;
    NODE best = NULL;
    for (int i=0; i<7; i++) {
	if (node->children[i] != NULL) {
	    double temp = ucb(node);
	    assert(temp>=0);
	    if (temp > max) {
		max = temp;
		best = node->children[i];
	    }
	}
    }
    assert(best);
    return best;
}

NODE expand_node(NODE node) {
    for (int i=0; i<7; i++) {
	if (node->children[i] == NULL) {
	    BOARD movement;
	    /* VERIFICAR */
	    do {
		movement = move(node_get_board(node), random_number(), 1);
	    } while(!movement);
	    NODE new = create_node(movement, node);
	    add_child(node, new);
	    return new;
	}
    }
}

int rollout(NODE node) {
    /* Should return 1 for a player win and 0 for a computer
       win or a draw. */
    int last_player = 1;
    BOARD b = node->board;
    int counter = 0;
    while (counter < 10000) {
	counter++;
	/* The last move was made by the computer.
	   It's now the player's turn. */
	if (last_player == 1) {
	    int column = random_number();
	    if (move(b, column, -1) == NULL){
		continue;
	    }
	    /* Making a move and changing player. */
	    b = move(b, column, -1);
	    //print_board(b);
	    last_player = -1;
	    if(score(b, -1) == -512) {
		return 1;
	    }
	    /*
	    if(score(b, 1) == 512) {
		return 0;
		}*/
	}
	/* The last move was made by the player.
	   It's now the computer's turn. */
	else if (last_player == -1) {
	    int column = random_number();
	    if(move(b, column, 1) == NULL){
		continue;
	    }
	    /* Making a move and changing player. */
	    b = move(b, column, 1);
	    last_player = 1;
	    /*
	    if(score(b, -1) == -512) {
		return 1;
		}*/
	    if(score(b, 1) == 512) {
		return 0;
	    }
	}
    }
    return 0;
}

void backpropagate(NODE node, int value, TREE tree) {
    node_set_reward(node, value);
    while ((node = node->parent) != NULL) {
	node_set_visits(node, node_get_visits(node) + 1);
    }
}

int montecarlo(BOARD b) {
    /* Intializes random number generator */
    time_t t;
    srand((unsigned) time(&t));
    
    TREE tree = create_tree();
    NODE root = create_node(b, NULL);
    tree_set_root(tree, root);

    for (int i=0; i<100; i++) {
	NODE cur = tree_get_root(tree);

	while (node_is_leaf(cur) == 0) {
	    cur = select_best(cur);
	    node_set_visits(cur, node_get_visits(cur) + 1);
	}

	NODE new_child = expand_node(cur);
	node_set_visits(new_child, node_get_visits(new_child) + 1);

	int value = rollout(new_child);
	backpropagate(new_child, value, tree);
    }
}

int game() {
    int first = -1;
    /* Deciding who moves first. */
    printf("Who will be playing first? (1 for PC, 0 for player)\n");
    scanf("%d", &first);
    while(!(first == 0 || first == 1)){
	printf("Who will be playing first? (1 for PC, 0 for player)\n");
	scanf("%d", &first);
    }
    if(first){
	b = 
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
	b = 
	if(score(b, 1) == 512){
	    print_board(b);
	    printf("**************************\n");
	    printf("Perdeu!\n");
	    return 1;
	}
    }
    return 0;
}
