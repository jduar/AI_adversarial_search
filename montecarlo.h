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
    ucb = child_reward_sum(node) + UCBCONSTANT * (sqrt((2*log(node_get_visits(node->parent)))/node_get_visits(node)));
    return ucb;
}

NODE select_best(NODE node) {
    double max = 0;
    NODE best;
    for (int i=0; i<7; i++) {
	if (node->children[i] != NULL) {
	    double temp = ucb(node);
	    if (temp > max) {
		max = temp;
		best = node->children[i];
	    }
	}
    }
    return best;
}

NODE expand_node(NODE node) {
    for (int i=0; i<7; i++) {
	if (node->children[i] == NULL) {
	    NODE new = create_node(move(node_get_board(node), random_number(), 1), node);
	    add_child(node, new);
	    return new;
	}
    }
}

int rollout(NODE node) {
    /* Should return 1 for a player win and 0 for a computer
       win or a draw. */
    int last_player = 1;
    BOARD b;
    int counter = 0;
    while (counter < 10000) {
	counter++;
	/* The last move was made by the computer.
	   It's now the player's turn. */
	if (last_player == 1) {
	    int column = random_number();
	    if(move(b, column, -1) == NULL){
		continue;
	    }
	    /* Making a move and changing player. */
	    b = move(b, column, -1);
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

int montecarlo(BOARD b) {
    /* Intializes random number generator */
    time_t t;
    srand((unsigned) time(&t));
    
    TREE tree = create_tree();
    NODE root = create_node(b, NULL);
    tree_set_root(tree, root);

    node_set_visits(root, node_get_visits(root) + 1);
    NODE cur = root;
    
    while (node_is_leaf(cur) == 0) {
	cur = select_best(cur);
	node_set_visits(cur, node_get_visits(cur) + 1);
    }
    
    NODE new_child = expand_node(cur);
    node_set_visits(new_child, node_get_visits(new_child) + 1);

    int value = rollout(new_child);
    printf("%d\n");
}
