#include "data.h"

void add_data(char *line, struct node *record){

    /*token will be used to get each piece of information from the line*/
    char *token;
    int i,j, position = 0, token_length;
    /*temp will be used to eliminate one extra double quotes using strcat*/
    char temp[TEMP_LENGTH];
    temp[1] = TERMINATING_CHAR;

    for(i = 0; i<strlen(line);i++){
        /*the situation when only the location component
         is left in the line string*/
        if(position == COORDINATE_POSITION){
            /*starting from the first character and end before
            the final quotation mark*/
            line = line + 1;
            for(j = 1; j < strlen(line); j++){
                if(line[strlen(line)-j] == QUOTATION_MARK){
                    token_length = strlen(line) - j;
                }
            }
            token = (char *) calloc(token_length+1, sizeof(char));
            assert(token != NULL);
            strncpy(token,line,token_length);
            add_token_data(token, record, position);
            /*information retrieval is complete*/
            break;
        }
        /*when the component starts with a quotation mark*/
        else if(line[i] == QUOTATION_MARK){
            /*The while loop will get the position of the ending
            quotation mark */
            j = i + 1;
            while(line[j] != QUOTATION_MARK || line[j+1] != COMMA){
                j++;
            }
            token_length = j - i - 1;
            token = (char *) calloc(token_length+1, sizeof(char));
            /*starting from the first component of the string again
              iterate to check the presence of extra quotation marks*/
            for(j = i + 1; line[j] != QUOTATION_MARK
                              || line[j+1] != COMMA; j++){
                if(line[j] != QUOTATION_MARK){
                    temp[0] = line[j];
                } else {
                    /*Spot extra quotation mark, skip
                    the current one and get the next one*/
                    temp[0] = QUOTATION_MARK;
                    j++;
                }
                /*concat each character to the token string*/
                strcat(token, temp);
            }
            add_token_data(token, record, position);
            i = 0;
            /*line string now starts from the character
              after the comma*/
            line = line + j + QUOTATION_COMMA_LENGTH;
            position++;
        } else if(line[i] == COMMA){
            /*get all the content before the comma*/
            token_length = i;
            token = (char *) calloc(token_length + 1, sizeof(char));
            assert(token != NULL);
            strncpy(token,line,token_length);
            if(line[i+1] == QUOTATION_MARK){
                line = line + i;
            }else {
                line = line + i + 1;
            }
            i = 0;
            add_token_data(token, record, position);
            position++;
            /*Only the location component is left,
            skip the quotation mark of the location component*/
            if(position == COORDINATE_POSITION){
                line = line + 1;
            }
        }
    }
}

void add_token_data(char *token, struct node* record, int position){
    char *data = copy_data(token);
    switch(position){
        case CENSUS_YEAR:
            record -> census_year = data;
            break;
        case BLOCK_ID:
            record -> block_id = data;
            break;
        case PROPERTY_ID:
            record -> property_id = data;
            break;
        case BASE_ID:
            record -> base_id = data;
            break;
        case CLUE:
            record -> clue = data;
            break;
        case TRADING_NAME:
            record -> trading_name = data;
            break;
        case INDUSTRY_CODE:
            record -> industry_code = data;
            break;
        case INDUSTRY_DESCRIPTION:
            record -> industry_description = data;
            break;
        case X_COORDINATE:
            record -> x_coordinate = atof(data);
            free(data);
            break;
        case Y_COORDINATE:
            record -> y_coordinate = atof(data);
            free(data);
            break;
        case LOCATION:
            record -> location = data;
            break;
    }
    free(token);
}

char *copy_data(char *token){
    char *dest = (char *) calloc(strlen(token) + 1, sizeof(char));
    assert(dest != NULL);
    strncpy(dest, token, strlen(token));
    return dest;
}
