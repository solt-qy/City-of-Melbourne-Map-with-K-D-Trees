#ifndef DATAH
#define DATAH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define COMMA ','
#define QUOTATION_MARK '\"'
#define TERMINATING_CHAR '\0'
#define NEW_LINE '\n'
#define COORDINATE_POSITION 10
#define TEMP_LENGTH 2
#define QUOTATION_COMMA_LENGTH 2
#define CENSUS_YEAR 0
#define BLOCK_ID 1
#define PROPERTY_ID 2
#define BASE_ID 3
#define CLUE 4
#define TRADING_NAME 5
#define INDUSTRY_CODE 6
#define INDUSTRY_DESCRIPTION 7
#define X_COORDINATE 8
#define Y_COORDINATE 9
#define LOCATION 10

/*
    node structure for the KD tree
    next is a pointer to the next duplicate
*/
struct node{
    char* census_year;
    char* block_id;
    char* property_id;
    char* base_id;
    char* clue;
    char* trading_name;
    char* industry_code;
    char* industry_description;
    double x_coordinate;
    double y_coordinate;
    char* location;
    char comparing_key;
    struct node* left;
    struct node* right;
    struct node* next;
};

//struct for the query coordinate
typedef struct{
    double x;
    double y;
}coord_t;

/*
    The fuction will add a line of data to a node
    in a specific dictionary
*/
void add_data(char *line, struct node *record);

/*
    The function will add the given token to the
    corresponding component of the node
*/
void add_token_data(char *token, struct node* record, int position);

/*
The function will copy the token string into the given dest string
*/
char *copy_data(char *token);

#endif
