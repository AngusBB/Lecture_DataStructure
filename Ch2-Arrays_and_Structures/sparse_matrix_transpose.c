/* implementation of sparse matrix transpose */

#include "function.h"

int main(){
    FILE *input_b;
    FILE *output_b_transpose;

    term b[MAX_TERMS];
    term b_transpose[MAX_TERMS];

    int32_t i = 0;

    {
        input_b = fopen("input_b.txt", "r");
        if(input_b == NULL){
            printf("open input_b.txt file failed!\n");
            exit(0);
        }

        while(fscanf(input_b, "%d %d %d", &b[i].row, &b[i].col, &b[i].value) != EOF){
            i++;
            if (i >= MAX_TERMS)
                exit(0);
        }
    }

    fast_sparse_transpose(b, b_transpose);

    {
        output_b_transpose = fopen("output_b_transpose.txt", "w+");
        if(output_b_transpose == NULL){
            printf("open output_b_transpose.txt file failed!\n");
            exit(0);
        }

        for(i = 0; i <= b_transpose[0].value; i++){
            fprintf(output_b_transpose, "%d %d %d\n", b_transpose[i].row, b_transpose[i].col, b_transpose[i].value);
        }
    }

    fclose(output_b_transpose);

    return 0;
}