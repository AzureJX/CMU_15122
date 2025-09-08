#include <stdlib.h>
#include <stdio.h>
#include "lib/xalloc.h"
#include "lib/boardutil.h"
#include "lib/bitvector.h"

char **initializeMatrix(index_t width, index_t height) {
    index_t num_cell = width * height; // num of cells on the board
    char ** M = xcalloc(num_cell,sizeof(char*));
    for (index_t i=0; i<num_cell; i++) {
        M[i] = xcalloc(num_cell+1,sizeof(char));
    }
    for (index_t j=0; j<num_cell; j++) {
        M[j][j] = 1; // diagonal = 1
        if (j % width < width - 1 && j + 1 < num_cell)
            M[j+1][j] = 1;
        if (j % width > 0 && j - 1 >= 0)
            M[j-1][j] = 1;
        if (j + width < num_cell)
            M[j+width][j] = 1;
        if (j >= width)
            M[j-width][j] = 1;
    }
    return M;
}

void addRow(char **M, index_t r1, index_t r2, index_t side_len) { // add r1 to r2, r1 unchanged
    for (index_t i=0; i<side_len+1; i++)
        M[r2][i] = M[r2][i] ^ M[r1][i];
}

void swapRow(char **M, index_t r1, index_t r2) {
    char *tmp = M[r1];
    M[r1] = M[r2];
    M[r2] = tmp;
}

void freeMatrix(char **M, index_t side_len) {
    for (index_t i=0; i<side_len; i++) {
        free(M[i]);
    }
    free(M);
}

void printMatrix(char **M, index_t side_len) {
    for (index_t i=0;i<side_len;i++) {
        for (index_t j=0;j<side_len+1;j++) {
            printf("%d",M[i][j]);
        }
        printf("\n");
    }
}

void swapToOne(char **M, index_t side_len, index_t col) {
    // row is the same as col
    for (index_t i=col+1;i<side_len;i++) {
        if (M[i][col]) {
            swapRow(M,i,col);
            return;
        }
    }
}

void addBitToM(char **M, index_t side_len, bitvector B) {
    for (index_t i=0;i<side_len;i++) {
        M[i][side_len] = bitvector_get(B,i);
    }
}

void solveMatrix(char **M, index_t side_len) {
    for (index_t i=0;i<side_len;i++) {
        if (!M[i][i]) swapToOne(M,side_len,i);
        for (index_t j=0;j<side_len;j++) {
            if (i==j) continue;
            if (M[j][i]) addRow(M, i, j, side_len);
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: lightsout <board name>\n");
        return EXIT_FAILURE;
    }
    char *board_filename = argv[1];
    bitvector bvec;
    index_t width;
    index_t height;
    bool bo = file_read(board_filename, &bvec, &width, &height);
    if (!bo) {
        bitvector_free(bvec);
        fprintf(stderr, "File read fails\n");
        return EXIT_FAILURE;
    }
    if (!is_valid_boardsize(width, height)) {
        bitvector_free(bvec);
        fprintf(stderr, "Not valid boardsize\n");
        return EXIT_FAILURE;
    }
    
    index_t n = width * height;
    char ** M = initializeMatrix(width, height);

    addBitToM(M, n, bvec);
    solveMatrix(M,n);
    printMatrix(M,n);

    for (index_t i=0;i<n;i++) {
        if ((!M[i][i])&&(M[i][n])) {
            fprintf(stderr, "board could not be solved\n");
            freeMatrix(M,n);
            bitvector_free(bvec);
            return 0;
        }
    }
    fprintf(stderr, "board could be solved\n");
    for (index_t i=0;i<n;i++) {
        if (M[i][n]) {
            printf("%u:%u\n",i/width,i%width); // i to row & col
        }
    }

    freeMatrix(M,n);
    bitvector_free(bvec);

    return 0;
}