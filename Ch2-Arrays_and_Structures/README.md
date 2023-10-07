# Usage

### 1. Make the file
```bash
make
```

### 2. Fill in the sparse terms in input_a.txt and input_b.txt
The format of input_x.txt is:
```
5 7 11
0 0 1
0 1 2
0 5 1
1 3 1
1 4 2
2 1 -1
3 2 4
3 4 0
3 6 2
4 4 1
4 6 2
```
The first line is the number of rows, columns and non-zero terms. \
The following lines are the row, column and value of each non-zero term.

### 3. Apply sparse matrix transpsoe
```bash
./sparse_matrix_transpose
```
The answer should save in output_b_transpsoe.txt and visualize on terminal.

### 4. Apply sparse matrix multiplication
```bash
./sparse_matrix_multiplication
```
The answer should save in output_cd.txt and visualize on terminal.
