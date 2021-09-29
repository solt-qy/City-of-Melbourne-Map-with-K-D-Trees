#ifndef OUTPUTH
#define OUTPUTH

#include "data.h"
#include "distance_search.h"
#include <stdio.h>
#include <stdlib.h>

#define KEY_LENGTH 128

/*
    output all the records of business that are in the given tree
    within the radius of a given coordinate (input from stdin)
*/
void output_pt_in_radius(FILE *stream, struct node *tree_root);

/*
    Format and print the output record
*/
void output_radius_record(char *x_coordinate, char *y_coordinate, char *radius,
    struct node* record, FILE* stream);
/*
    Output all the records of businesses that are closest
    to the given coordinate (input from stdin)
*/
void output_nearest_pt(FILE *stream, struct node *tree_root);

/*
    Format and print the output record
*/
void output_near_record(char *x_coordinate, char *y_coordinate,
     struct node* record, FILE* stream);

#endif
