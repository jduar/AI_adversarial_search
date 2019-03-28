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

NODE select_best(NODE node) {
    double max = 0;
    NODE best;
    for (int i=0; i<7; i++) {
	if (node->children[i] != NULL) {
	    if (node_get_ucb(node->children[i]) > max) {
		max = node_get_ucb(node->children[i]);
		best = node->children[i];
	    }
	}
    }
    return best;
}

NODE expand_node(NODE node) {
    for (int i=0; i<7; i++) {
	if (node->children[i] == NULL) {
	    NODE new = create_node(move(node_get_board(node), 0, 1), node);
	    add_child(node, new);
	    return new;
	}
    }
}

int montecarlo(BOARD b) {
    TREE tree = create_tree();
    NODE root = create_node(b, NULL);
    tree_set_root(tree, root);

    node_set_visits(root, node_get_visits(root) + 1);
    NODE cur = root;
    
    while (node_is_leaf(cur) == 0) {
	cur = select_best(cur);
	node_set_visits(cur, node_get_visits(cur) + 1);
    }

    NODE new_child = expand(node);
    node_set_visits(new_child, node_get_visits(new_child) + 1);

    
}
