#include "distance_search.h"


struct node *nearest_pt_search(struct node *tree_root,
    char *x_coordinate, char *y_coordinate){

    struct node **closest_node = &tree_root;
    coord_t coord;
    coord.x = atof(x_coordinate);
    coord.y = atof(y_coordinate);
    double distance = check_distance(*closest_node, coord);
    int counter = 0;
    closest_node = compare_distance(&tree_root, coord,
                                closest_node, &distance, &counter);
    printf("%s %s --> %d \n", x_coordinate, y_coordinate, counter);
    return *closest_node;
}

struct node **compare_distance(struct node **current_node, coord_t query_coord,
    struct node **closest_node, double *distance, int *counter){

    if(!(*current_node)){
        return closest_node;
    }

    *counter = *counter + 1;
    double current_distance = check_distance(*current_node, query_coord);

    //closest node is the the current node that is closest to the searched coordinate
    if(current_distance < *distance){
        closest_node = &(*current_node);
        *distance = current_distance;
    }

    //At each layer of the tree, different key will be used for comparison
    if((*current_node)->comparing_key == 'x'){
        //Comparion whether distance between x_coordinates is larger than closest distance
        //If so, the search will only proceed to one side of the node
        if(pow(query_coord.x - (*current_node)->x_coordinate, SQUARE)> *distance){
            if((*current_node) -> x_coordinate < query_coord.x){
                closest_node = compare_distance(&((*current_node) -> right),
                                query_coord, closest_node, distance, counter);
            } else {
                closest_node = compare_distance(&((*current_node) -> left),
                                query_coord, closest_node, distance, counter);
            }
        } 
        //distance between x_coordinates is smaller than closest distance
        //proceed to both branch of the node
        else {
            closest_node = compare_distance(&((*current_node) -> right),
                                query_coord, closest_node, distance, counter);
            closest_node = compare_distance(&((*current_node) -> left),
                                query_coord, closest_node, distance, counter);
        }
    } 
    //similar logic applies to the comparison of y_coordinates
    else {
        if(pow(query_coord.y - (*current_node)->y_coordinate, SQUARE)> *distance){
            if((*current_node) -> y_coordinate < query_coord.y){
                closest_node = compare_distance(&((*current_node) -> right),
                                query_coord, closest_node, distance, counter);
            } else {
                closest_node = compare_distance(&((*current_node) -> left),
                                query_coord, closest_node, distance, counter);
            }
        } else {
            closest_node = compare_distance(&((*current_node) -> right),
                                query_coord, closest_node, distance, counter);
            closest_node = compare_distance(&((*current_node) -> left),
                                query_coord, closest_node, distance, counter);
        }
    }
    return closest_node;
}

void radius_search(struct node *tree_root,
    char *x_coordinate, char *y_coordinate, char *radius, FILE *stream){


    int counter = 0;
    int pt_within_radius = 0;
    coord_t query_coord;
    query_coord.x = atof(x_coordinate);
    query_coord.y = atof(y_coordinate);
    compare_radius(&tree_root, query_coord, radius,
                    &counter, &pt_within_radius, stream);
    printf("%s %s %s --> %d \n", x_coordinate, y_coordinate, radius, counter);
    if(!pt_within_radius){
        fprintf(stream, "%s %s %s --> NOTFOUND",
                            x_coordinate, y_coordinate, radius);
    }
}

void compare_radius(struct node **current_node, coord_t query_coord,
            char* radius, int *counter, int *pt_within_radius, FILE *stream){

    if(!(*current_node)){
        return;
    }


    double r = atof(radius);
    *counter = *counter + 1;

    if(check_distance(*current_node, query_coord) <= r*r){
        struct node **output_node = current_node;
        while((*output_node)->next){
            output_node = &((*output_node)->next);
        }
        *pt_within_radius = *pt_within_radius + 1;
    }

    if((*current_node)->comparing_key == 'x'){
        if(fabs(query_coord.x - (*current_node) -> x_coordinate) > r){
            if((*current_node) -> x_coordinate < query_coord.x){
                compare_radius(&((*current_node) -> right), query_coord,
                                radius, counter, pt_within_radius, stream);
            } else {
                compare_radius(&((*current_node) -> left), query_coord,
                                radius, counter, pt_within_radius, stream);
            }
        } else {
            compare_radius(&((*current_node) -> right), query_coord,
                            radius, counter, pt_within_radius, stream);
            compare_radius(&((*current_node) -> left), query_coord,
                            radius, counter, pt_within_radius, stream);
        }
    } else {
        if(fabs(query_coord.y - (*current_node) -> y_coordinate) > r){
            if((*current_node) -> y_coordinate < query_coord.y){
                compare_radius(&((*current_node) -> right), query_coord,
                                radius, counter, pt_within_radius, stream);
            } else {
                compare_radius(&((*current_node) -> left), query_coord,
                                radius, counter, pt_within_radius, stream);
            }
        } else {
            compare_radius(&((*current_node) -> right), query_coord,
                            radius, counter, pt_within_radius, stream);
            compare_radius(&((*current_node) -> left), query_coord,
                            radius, counter, pt_within_radius, stream);
        }
    }
}

double check_distance(struct node *current_node, coord_t query_coord){
    return pow(current_node -> x_coordinate - query_coord.x, SQUARE) +
                pow(current_node -> y_coordinate - query_coord.y, SQUARE);
}
