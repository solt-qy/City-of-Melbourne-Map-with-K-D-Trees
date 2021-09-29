#ifndef TREEH
#define TREEH

#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>


#define EPSILON 1e-9

/*
    The function will read all data from the file and
    and insert them into a KD_tree with the root as tree_root
*/
void read_data(FILE* stream, struct node* tree_root);

/*
    A recursive function that take pointers of node pointer and
    correctly place the new_node in the corresponding position in
    the tree.
*/
void insert(struct node **prev_node, struct node **new_node);

/*
    compare both node's x and y coordinates, return 1
    if their coordinates are exact duplicates
*/
int equal_coordinates(struct node *prev_node, struct node *new_node);

/*
    The function will free all the allocated
    memory for the KD tree
*/
void free_tree(struct node* dict_head);

#endif
