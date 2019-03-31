#include <stdio.h>
#include <stdlib.h>

#include "4linha.h"

#ifndef TREE_H
#define TREE_H

typedef struct node {
    struct node *parent;
    struct node *children[7];
    
    BOARD board;
    int reward;
    int visits;
} *NODE;

typedef struct tree {
    NODE root;
} *TREE;

/* ##### IMPLEMENTATION ##### */
/* Creates a node from a board. */
NODE create_node(BOARD b, NODE parent);

/* Returns a node's board. */
BOARD node_get_board(NODE node);

/* Returns a node's UCB. */
int node_get_reward(NODE node);

/* Sets the node's reward. */
void node_set_reward(NODE node, int reward);

/* Returns the number of times a node's been visited. */
int node_get_visits(NODE node);

/* Sets a node's number of times visited. */
void node_set_visits(NODE node, int visits);

/* Check if a node is a leaf. [1-true; 0-false] */
int node_is_leaf(NODE node);

/* Returns a new TREE. */
TREE create_tree();

/* Sets a tree's root. */
void tree_set_root(TREE tree, NODE node);

/* Returns a tree's root. */
NODE tree_get_root(TREE tree);

/* Adds a child node to another. */
void add_child(NODE node, NODE child);

/* Destroys a subtree. */
void destroy_subtree(NODE node);

/* Destroys a tree. */
void destroy_tree(TREE tree);

/*
IMPLEMENTATION
*/

/*
NODE FUNCTIONS
*/
NODE create_node(BOARD b, NODE parent) {
    NODE node = malloc(sizeof(struct node));
    node->board = b;
    node->reward = 0;
    node->visits = 0;
    node->parent = parent;
    for (int i=0; i<7; i++) {
	node->children[i] = NULL;
    }

    return node;
}

BOARD node_get_board(NODE node) {
    return node->board;
}

int node_get_reward(NODE node) {
    return node->reward;
}

void node_set_reward(NODE node, int reward) {
    node->reward = reward;
}

int node_get_visits(NODE node) {
    return node->visits;
}

void node_set_visits(NODE node, int visits) {
    node->visits = visits;
}

int node_is_leaf(NODE node) {
    for (int i=0; i<7; i++) {
	if (node->children[i] != NULL) {
	    return 0;
	}
    }
    return 1;
}

/*
TREE FUNCTIONS
*/
TREE create_tree() {
    TREE tree = malloc(sizeof(TREE));
    tree->root = NULL;
    return tree;
}

void tree_set_root(TREE tree, NODE node) {
    tree->root = node;
}

NODE tree_get_root(TREE tree) {
    return tree->root;
}

void add_child(NODE node, NODE child) {
    for (int i=0; i<7; i++) {
	if (node->children[i] == NULL) {
	    node->children[i] = child;
	    node->children[i]->parent = node;
	    break;
	}
    }
}

void destroy_subtree(NODE node) {
    for (int i=0; i<7; i++) {
	if (node->children[i] != NULL) {
	    destroy_subtree(node->children[i]);
	}
    }
    free(node);
}

void destroy_tree(TREE tree) {
    destroy_subtree(tree_get_root(tree));
    free(tree);
}

#endif
