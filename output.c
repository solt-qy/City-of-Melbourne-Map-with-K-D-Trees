#include "output.h"

void output_pt_in_radius(FILE *stream, struct node *tree_root){

    char search_key[KEY_LENGTH];

    while(scanf("%[^\n]%*c", search_key) == 1){
        char *x_coordinate = strtok(search_key, " ");
        char *y_coordinate = strtok(NULL, " ");
        char *radius = strtok(NULL, " ");
        radius_search(tree_root, x_coordinate, y_coordinate, radius, stream);
    }
}

void output_radius_record(char *x_coordinate, char *y_coordinate, char *radius,
    struct node* record, FILE* stream){
    fprintf(stream, "%s %s %s --> Census year: %s || Block ID: %s || Property"
                " ID: %s || Base property ID: %s || CLUE small area: %s ||"
                " Trading Name: %s || Industry (ANZSIC4) code: %s || Industry "
                "(ANZSIC4) description: %s || x coordinate: %.4f || y "
                "coordinate: %.4f || Location: %s || \n",
                x_coordinate, y_coordinate, radius, record->census_year,
                record->block_id, record->property_id, record->base_id,
                record->clue, record->trading_name, record->industry_code,
                record->industry_description, record->x_coordinate,
                record->y_coordinate, record->location);
}

void output_nearest_pt(FILE* stream, struct node *tree_root){

    char search_key[KEY_LENGTH];
    struct node *closest_node;

    while(scanf("%[^\n]%*c", search_key) == 1){
        char *x_coordinate = strtok(search_key, " ");
        char *y_coordinate = strtok(NULL, " ");
        closest_node = nearest_pt_search(tree_root, x_coordinate, y_coordinate);
        output_near_record(x_coordinate, y_coordinate, closest_node, stream);
        while(closest_node->next){
            closest_node = closest_node->next;
            output_near_record(x_coordinate, y_coordinate, closest_node,stream);
        }
    }
}

void output_near_record(char *x_coordinate, char *y_coordinate,
     struct node* record, FILE* stream){
    fprintf(stream, "%s %s --> Census year: %s || Block ID: %s || Property ID: "
                    "%s || Base property ID: %s || CLUE small area: %s ||"
                    " Trading Name: %s || Industry (ANZSIC4) code: %s || "
                     "Industry (ANZSIC4) description: %s || x coordinate: %.4f "
                     "|| y coordinate: %.4f || Location: %s || \n",
                    x_coordinate, y_coordinate, record->census_year,
                    record->block_id, record->property_id, record->base_id,
                    record->clue, record->trading_name, record->industry_code,
                    record->industry_description, record->x_coordinate,
                    record->y_coordinate, record->location);
}
