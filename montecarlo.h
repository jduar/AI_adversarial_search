/* Monte-Carlo implementation */

#include <math.h>

#include "mytree.h"

/* Constant present on UCB's calculation. */
#define UCBCONSTANT 2

/* Returns a random number from 0 to 6. */
int random_number() {      
   return(rand() % 7);
}

/* Returns the sum of all child (and child's children, etc) nodes' rewards. */
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

/* Returns a node's upper confidence bound. */
double ucb(NODE node) {
    double ucb = 0;
    if (node->parent != NULL) {
	if (node == NULL) {
	    printf("\n");
	}
	ucb = child_reward_sum(node) +
	    ( UCBCONSTANT * (sqrt((2*log(node_get_visits(node->parent))) / (node_get_visits(node) + 1))) );
	//printf("%d %d\n", node_get_visits(node->parent), node_get_visits(node));
	//printf("withparent: %lf\n", ucb);
	return ucb;
    }
    else {
	ucb = child_reward_sum(node) +
	    ( UCBCONSTANT * (sqrt((2 / (node_get_visits(node) + 1)))) );	
	//printf("without: %lf\n", ucb);
	return ucb;
    }
}

NODE select_best(NODE node) {
    double max = -1;
    NODE best = NULL;
    for (int i=0; i<7; i++) {
	if (node->children[i] != NULL) {
	    double temp = ucb(node->children[i]);
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

NODE expand_node(NODE node, int player) {
    for (int i=0; i<7; i++) {
	if (node->children[i] == NULL && player == 0) {
	    BOARD movement;
	    /* VERIFICAR */
	    /*
	    do {
		movement = move(node_get_board(node), random_number(), 1);
	    } while(!movement);
	    */
	    movement = move(node_get_board(node), random_number(), 1);
	    NODE new = create_node(movement, node);
	    add_child(node, new);
	    return new;
	}
	else if (node->children[i] == NULL && player == 1) {
	    BOARD movement;
	    /*
	    do {
		movement = move(node_get_board(node), random_number(), -1);
	    } while(!movement);
	    */
	    movement = move(node_get_board(node), random_number(), -1);
	    NODE new = create_node(movement, node);
	    add_child(node, new);
	    return new;
	}
    }
    return NULL;
}

void expand_node_2_electric_boogaloo(NODE node) {
    for (int i=0; i<7; i++) {
	BOARD movement;
	do {
	    movement = move(node_get_board(node), i, 1);
	} while(!movement);
	//BOARD movement = move(node_get_board(node), i, 1);
	NODE new = create_node(movement, node);
	add_child(node, new);
    }
}

int rollout(NODE node) {
    /* Should return 1 for a player win and 0 for a computer
       win or a draw. */
    int last_player = 1;
    BOARD b = node->board;
    int counter = 0;
    while (counter < 1000) {
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
	    if(score(b, 1) == 512) {
		return 0;
	    }
	}
    }
    return 0;
}

void backpropagate(NODE node, int value, TREE tree) {
    /* We update the value of the current node and then the nodes above. */
    node_set_reward(node, value);
    while ((node = node->parent) != NULL) {
	node_set_reward(node, child_reward_sum(node));
	//node_set_visits(node, node_get_visits(node) + 1);
    }
}

BOARD montecarlo(BOARD b) {
    TREE tree = create_tree();
    NODE root = create_node(b, NULL);
    tree_set_root(tree, root);

    /* Creating the first two levels. */
    for (int i=0; i<7; i++) {
	BOARD movement = move(b, i, 1);
	NODE new = create_node(movement, root);
	add_child(root, new);
	for (int j=0; j<7; j++) {
	    BOARD movement_child = move(movement, j, -1);
	    NODE new_child = create_node(movement_child, new);
	    add_child(new, new_child);
	}
    }

    for (int i=0; i<10; i++) {
	NODE cur = tree_get_root(tree);

	while (node_is_leaf(cur) == 0) {
	    //cur = select_best(cur);
	    node_set_visits(cur, node_get_visits(cur) + 1);
	    cur = select_best(cur);
	}
	/* *** */
	/*
	NODE new_child = expand_node(cur);
	node_set_visits(new_child, node_get_visits(new_child) + 1);

	int value = rollout(new_child);
	backpropagate(new_child, value, tree);
	*/

	int value = 0;
	int children = 0;
	while (value == 0 && children < 7) {
	    NODE new_child = expand_node(cur, i%2);
	    if (node_get_board(new_child) == NULL) {
		destroy_subtree(new_child);
		break;
	    }
	    node_set_visits(new_child, node_get_visits(new_child) + 1);

	    int value = rollout(new_child);
	    backpropagate(new_child, value, tree);
	    children++;
	}
	
	
	/* *** */
	/*
	expand_node_2_electric_boogaloo(cur);
	for (int i=0; i<7; i++) {
	    node_set_visits(cur->children[i],
			    node_get_visits(cur->children[i]) + 1);
	    int value = rollout(cur->children[i]);
	    backpropagate(cur->children[i], value, tree);
	    }
	*/
    }
    b = select_best(root)->board;
    //printf("eeheheheehh\n");
    //print_board(b);
    print_tree(tree->root, "", 1);
    destroy_tree(tree);
    return b;
}

int mc_game_loop(BOARD b) {
    /* Intializes random number generator */
    time_t t;
    srand((unsigned) time(&t));
    
    /* Deciding who moves first. */
    int first = -1;
    printf("Who will be playing first? (1 for PC, 0 for player)\n");
    scanf("%d", &first);
    while (!(first == 0 || first == 1)) {
	printf("Who will be playing first? (1 for PC, 0 for player)\n");
	scanf("%d", &first);
    }

    /* Starting the game loop. */
    if (first == 1) {
	b = montecarlo(b);
    }
    
    while (TRUE) {
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
	b = montecarlo(b);
	if(score(b, 1) == 512){
	    print_board(b);
	    printf("**************************\n");
	    printf("Perdeu!\n");
	    return 1;
	}
    }
    return 0;
}
