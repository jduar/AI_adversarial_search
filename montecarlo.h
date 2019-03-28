#include <math.h>

#include "mytree.h"

#define UCBCONSTANT 1

double child_reward_sum(NODE node) {
    double sum = 0;
    for (int i=0; i<7; i++) {
	if (node->children[i] != NULL) {
	    sum = sum +
		node_get_ucb(node->children[i]) +
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

int montecarlo(BOARD b) {
    TREE tree = create_tree();
    NODE root = create_node(b, NULL);
    tree_set_root(tree, root);

    node_set_visits(root) = node_get_visits(root) + 1;
    cur = root;
    
    while (node_is_leaf(cur) == 0) {
	cur = select_best();
	node_set_visits(cur) = node_get_visits(cur) + 1;
    }

    

    
}
