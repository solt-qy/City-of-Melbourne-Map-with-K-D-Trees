#include "tree.h"
#include "data.h"
#include "output.h"

#define REQUIRED_ARGUMENTS 3
#define DATA 1
#define OUTPUT 2

int main(int argc, char **argv){

    if(argc < REQUIRED_ARGUMENTS){
        printf("Error: Insufficent arguments provided.\n");
        return 0;
    }

    struct node* tree_root = (struct node*) malloc(sizeof(struct node));
    assert(tree_root != NULL);

    FILE *fp1, *fp2;
    fp1 = fopen(argv[DATA], "r");
    fp2 = fopen(argv[OUTPUT], "w");
    assert(fp1 != NULL);
    assert(fp2 != NULL);

    read_data(fp1, tree_root);
    output_pt_in_radius(fp2, tree_root);
    free_tree(tree_root);
    fclose(fp1);
    fclose(fp2);
}
