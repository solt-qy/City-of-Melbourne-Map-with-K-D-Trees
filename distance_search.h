#ifndef DISTANCE_SEARCHH
#define DISTANCE_SEARCHH

#include "data.h"
#include "output.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define SQUARE 2
/*
    Find the nearest point to the given coordinate.
    Starting from the root of a KD-tree, it will also print
    the number of comparison to stdout
    Return the node that is closest to the coordinate
*/
struct node *nearest_pt_search(struct node *tree_root,
    char *x_coordinate, char *y_coordinate);

/*
    Recursive function that finds the distance between the
    current node and the given coordinate, update the closest
    distance, and will traverse down the tree to compare further
    according to the comparison rules specified in the assignment
    Return the current closest node
*/
struct node **compare_distance(struct node **current_node, coord_t query_coord,
        struct node **closest_node, double *distance, int *counter);

/*
    Find all the points that are within the radius around a Coordinate
    and print all the results to the given stream
*/
void radius_search(struct node *tree_root,
    char *x_coordinate, char *y_coordinate, char *radius, FILE *stream);

/*
    Recursive function that check that compare nodes in the
    k_d tree with the given coordinate and check if they are within
    the radius
*/
void compare_radius(struct node **current_node, char *x, char *y,
        char* radius, int *counter, int *pt_within_radius, FILE *stream);

/*
    finds the distance between the current node
    and the given coordinate
*/
double check_distance(struct node *current_node, coord_t query_coord);

#endif
