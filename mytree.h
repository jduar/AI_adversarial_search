#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/* Print tree. */
void print_tree(NODE node, char* indent, int last);

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

void print_tree(NODE node, char* indent, int last) {
    /* Implementation based on
       https://stackoverflow.com/questions/5901181/c-string-append
       - indent is a string that increases in size the further the current
       node is away from the root node;
       - last represents whether the current node is the last child; */
    char new_str[64] = "";
    printf("%s", indent);
    /* If we're at the last child, we increase the indent string. */
    if (last == 1) {
	strcat(new_str, indent);
	strcat(new_str, "  ");
	printf("\\-");
    }
    /* If we're not at the last child, we'll print with the same
       indentation we printed the last node (a sibling). */
    else {
	printf("|- ");
	strcat(new_str, indent);
	strcat(new_str, "| ");
    }
    /* To represent each node, we print its reward and visits values. */
    printf("[%d,%d]\n", node_get_reward(node), node_get_visits(node));

    /* We count the children nodes so we know when we're at the last child. */
    int counter = 0;
    for (int i=0; i<7; i++) {
	if (node->children[i] != NULL) {
	    counter++;
	}
    }
    for (int i=0; i<7; i++) {
	if (node->children[i] != NULL && i==counter-1) {
	    print_tree(node->children[i], new_str, 1);	   
	}
	else if (node->children[i] != NULL && i!=counter-1) {
	    print_tree(node->children[i], new_str, 0);
	}
    }
}

#endif
