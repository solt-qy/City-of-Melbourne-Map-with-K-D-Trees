#include "tree.h"

void read_data(FILE *stream, struct node *tree_root){

    char *line = NULL;
    size_t lineBufferLength = 0;
    struct node *new_node;
    struct node **prev_node;

    //Remove the first line of data (categories)
    getline(&line, &lineBufferLength, stream);
    //fill the tree root
    if(getline(&line, &lineBufferLength, stream) != -1){
        add_data(line, tree_root);
        tree_root -> comparing_key = 'x';
        tree_root -> left = NULL;
        tree_root -> right = NULL;
        tree_root -> next = NULL;
    }
    while(getline(&line, &lineBufferLength, stream) != -1){
        prev_node = &tree_root;
        new_node = (struct node*) malloc(sizeof(struct node));
        assert(new_node != NULL);
        new_node -> left = NULL;
        new_node -> right = NULL;
        new_node -> next = NULL;
        add_data(line, new_node);
        insert(prev_node, &new_node);
    }
    free(line);
}

void insert(struct node **prev_node, struct node **new_node){
    if(equal_coordinates(*prev_node, *new_node)){
        while((*prev_node) -> next != NULL){
            prev_node = &((*prev_node)->next);
        }
        (*prev_node) -> next = *new_node;
        return;
    } else if((*prev_node)->comparing_key == 'x'){
        if((*new_node)->x_coordinate < (*prev_node)->x_coordinate){
            if((*prev_node)->left == NULL){
                (*prev_node)->left = *new_node;
                (*new_node)->comparing_key = 'y';
            } else {
                prev_node = &((*prev_node)->left);
                insert(prev_node, new_node);
            }
        } else {
            if((*prev_node)->right == NULL){
                (*prev_node)->right = *new_node;
                (*new_node)->comparing_key = 'y';
            } else {
                prev_node = &((*prev_node)->right);
                insert(prev_node, new_node);
            }
        }
    } else {
        if((*new_node)->y_coordinate < (*prev_node)->y_coordinate){
            if((*prev_node)->left == NULL){
                (*prev_node)->left = *new_node;
                (*new_node)->comparing_key = 'x';
            } else {
                prev_node = &((*prev_node)->left);
                insert(prev_node, new_node);
            }
        } else {
            if((*prev_node)->right == NULL){
                (*prev_node)->right = *new_node;
                (*new_node)->comparing_key = 'x';
            } else {
                prev_node = &((*prev_node)->right);
                insert(prev_node, new_node);
            }
        }
    }
}

int equal_coordinates(struct node *prev_node, struct node *new_node){
    return fabs(new_node->x_coordinate - prev_node->x_coordinate) < EPSILON
    && fabs(new_node->y_coordinate - prev_node->y_coordinate) < EPSILON;
}

void free_tree(struct node* tree_root){

    struct node* temp;

    if(tree_root != NULL){
      free_tree(tree_root -> left);
      free_tree(tree_root -> right);
    while(tree_root != NULL){
        temp = tree_root;
        tree_root = tree_root -> next;
        free(temp -> census_year);
        free(temp -> block_id);
        free(temp -> property_id);
        free(temp -> base_id);
        free(temp -> clue);
        free(temp -> trading_name);
        free(temp -> industry_code);
        free(temp -> industry_description);
        free(temp -> location);
        free(temp);
    }
  }
}
