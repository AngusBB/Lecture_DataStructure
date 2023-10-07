#include "function.h"

// --------------------------------------------------------------
void fast_sparse_transpose(term b[],term b_transpose[]){

    /* the transpose of b is placed in b_transpose */

    /*
        +------+-----+-----+-------+
        |   b  | row | col | value |
        +------+-----+-----+-------+
        | b[0] |  6  |  6  |   8   |
        | b[1] |  0  |  0  |   15  |
        | b[2] |  0  |  3  |   22  |
        | b[3] |  0  |  5  |   -15 |
        | b[4] |  1  |  1  |   11  |
        | b[5] |  1  |  2  |   3   |
        | b[6] |  2  |  3  |   -6  |
        | b[7] |  4  |  0  |   91  |
        | b[8] |  5  |  2  |   28  |
        +------+-----+-----+-------+

        +-----+-----------+-----------------------+
        |  i  | row_terms | starting_row_position |
        +-----+-----------+-----------------------+
        |  0  |     2     |           1           |
        |  1  |     1     |           3           |
        |  2  |     2     |           4           |
        |  3  |     2     |           6           |
        |  4  |     0     |           8           |
        |  5  |     1     |           8           |
        +-----+-----------+-----------------------+
    
    */

	int32_t row_terms[MAX_TERMS]    = {0};
    int32_t starting_pos[MAX_TERMS] = {0};

    int32_t num_rows  = b[0].row;
    int32_t num_cols  = b[0].col;
    int32_t num_terms = b[0].value;

	b_transpose[0].row   = num_cols;
    b_transpose[0].col   = num_rows;
	b_transpose[0].value = num_terms;

	if(num_terms > 0){

        /* The reset in the original book is moved to the definition. */
		// for(int32_t i = 0; i < num_cols; i++)
		//     row_terms[i] = 0;

        /* calculate the amount of row_terms */
		for(int32_t i = 1; i <= num_terms; i++){
			row_terms[b[i].col]++;
		}

        /* calculate the starting position of each row */
		starting_pos[0] = 1;
		for(int32_t i = 1; i < num_cols; i++){
			starting_pos[i] = starting_pos[i-1] + row_terms[i-1];
		}

        /* transpose the matrix */
        int32_t j = 0;
		for(int32_t i = 1; i <= num_terms; i++){
			j = starting_pos[b[i].col]++;
			b_transpose[j].row   = b[i].col;
            b_transpose[j].col   = b[i].row;
			b_transpose[j].value = b[i].value;
		}

        /* visualize b */
        printf( "┌-------------------------------------┐\n"
                "|   b   |  row  |  col  |    value    |\n"
                "|-------+-------+-------+-------------|\n");
        for(int32_t i = 0; i <= b[0].value; i++)
            printf("| %5d |  %3d  |  %3d  |  %10d |\n", i, b[i].row, b[i].col, b[i].value);
        printf( "└-------------------------------------┘\n\n");

        /* visualize row_terms */
        printf( "┌-------------------------------------------┐\n"
                "|   b   | row_terms | starting_row_position |\n"
                "|-------+-----------+-----------------------|\n");
        for(int32_t i = 0; i < num_cols; i++)
            printf("| %5d |  %7d  |           %d           |\n", i, row_terms[i], starting_pos[i]);
        printf( "└-------------------------------------------┘\n\n");

        /* visualize b_transpose */
        printf( "┌-------------------------------------┐\n"
                "|  b_tr |  row  |  col  |    value    |\n"
                "|-------+-------+-------+-------------|\n");
        for(int32_t i = 0; i <= b_transpose[0].value; i++)
            printf("| %5d |  %3d  |  %3d  |  %10d |\n", i, b_transpose[i].row, b_transpose[i].col, b_transpose[i].value);
        printf( "└-------------------------------------┘\n\n");

	}
}

// --------------------------------------------------------------
void store_sum(term d[], int32_t *totald, int32_t row, int32_t column, int32_t *sum){

    /* if *sum != 0, then it along with its row and 
        column position is stored as the *totald+1 entry in d */

    if(*sum){
        if(*totald < MAX_TERMS){
            d[++*totald].row = row;
            d[*totald].col = column;
            d[*totald].value = *sum;
            *sum = 0;
        }
        else{
            fprintf(stderr, "Numbers of terms in product exceeds %d\n", MAX_TERMS);
            exit(1);
        }
    }
}
// --------------------------------------------------------------
void mmult(term a[], term b[], term d[]){

    /* multiply two sparse matrices a and b, and store the result in d */

    int32_t column;
    int32_t totala = a[0].value, totalb = b[0].value, totald = 0;
    int32_t rows_a = a[0].row, cols_a = a[0].col;
    int32_t rows_b = b[0].row, cols_b = b[0].col;
    int32_t row_begin = 1, row = a[1].row, sum = 0;
    term b_transpose[MAX_TERMS];

    if(cols_a != rows_b){
        fprintf(stderr, "Incompatible matrices\n");
        exit(1);
    }

    fast_sparse_transpose(b, b_transpose);

    /* set boundary condition */
    a[totala+1].row = rows_a;
    b_transpose[totalb+1].row = cols_b;
    b_transpose[totalb+1].col = 0;

    for(int32_t i = 1; i <= totala; ){ 
        column = b_transpose[1].row;

        sum = 0; // 原文書裡沒有這行，但是我覺得應該要有，不然會有錯誤

        for (int32_t j = 1; j <= totalb+1; ){

            /* multiply row of a by column of b */
            
            if(a[i].row != row){
                store_sum(d, &totald, row, column, &sum);
                i = row_begin;
                while(b_transpose[j].row == column)
                    j++; // 等價於 for(; b_transpose[j].row == column; j++);
                column = b_transpose[j].row;
            }
            else if(b_transpose[j].row != column){
                store_sum(d, &totald, row, column, &sum);
                i = row_begin;
                column = b_transpose[j].row;
            }
            else
                switch(COMPARE(a[i].col, b_transpose[j].col)){
                    case -1: // go to next term in a
                        i++;
                        break;
                    case 0: // add terms, go to next term in a and b
                        sum += (a[i++].value * b_transpose[j++].value);
                        break;
                    case 1: // advance to next term in b
                        j++;
            }
        } // end of for j <= totalb+1

        while(a[i].row == row)
            i++; // 等價於 for(; a[i].row == row; i++);
        row_begin = i;
        row = a[i].row;
    } // end of for i <= totala
    
    d[0].row = rows_a;
    d[0].col = cols_b;
    d[0].value = totald;
}