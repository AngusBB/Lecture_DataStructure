/* implementation of sparse matrix multiplication */ 

#include "function.h"

int main(){
	FILE *input_a;
    FILE *input_b;
	FILE *output_d;

	term a[MAX_TERMS];
    term b[MAX_TERMS];
    term d[MAX_TERMS];

    {
        input_a = fopen("input_a.txt", "r");
        if(input_a == NULL){
            printf("open input_a.txt file failed!\n");
            exit(0);
        }

        input_b = fopen("input_b.txt", "r");
        if(input_b == NULL){
            printf("open input_b.txt file failed!\n");
            exit(0);
        }

        int32_t i = 0;
        while(fscanf(input_a, "%d %d %d", &a[i].row, &a[i].col, &a[i].value) != EOF){
            i++;
            if (i >= MAX_TERMS)
                exit(0);
        }
        i = 0;
        while(fscanf(input_b, "%d %d %d", &b[i].row, &b[i].col, &b[i].value) != EOF){
            i++;
            if (i >= MAX_TERMS)
                exit(0);
        }
    }

    /* visualize a */
    printf( "┌-------------------------------------┐\n"
            "|   a   |  row  |  col  |    value    |\n"
            "|-------+-------+-------+-------------|\n");
    for(int32_t i = 0; i <= a[0].value; i++)
        printf("| %5d |  %3d  |  %3d  |  %10d |\n", i, a[i].row, a[i].col, a[i].value);
    printf( "└-------------------------------------┘\n\n");

	mmult(a, b, d);

    /* visualize d */
    printf( "┌-------------------------------------┐\n"
            "|   d   |  row  |  col  |    value    |\n"
            "|-------+-------+-------+-------------|\n");
    for(int32_t i = 0; i <= d[0].value; i++)
        printf("| %5d |  %3d  |  %3d  |  %10d |\n", i, d[i].row, d[i].col, d[i].value);
    printf( "└-------------------------------------┘\n\n");

    {
        output_d = fopen("output_d.txt", "w+"); 
        if(output_d == NULL){
            printf("open output_d.txt file failed!\n");
            exit(0);
        }

        for(int32_t i = 0; i <= d[0].value; i++){
            fprintf(output_d, "%d %d %d\n", d[i].row, d[i].col, d[i].value);
        }
    }
    
	fclose(input_a);
    fclose(input_b);
    fclose(output_d);

    return 0;
}