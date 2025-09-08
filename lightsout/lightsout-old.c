#include <stdlib.h>
#include <stdio.h>
#include "lib/xalloc.h"
#include "lib/boardutil.h"
#include "lib/bitvector.h"
#include "board-ht.h" // hdict
#include "lib/queue.h"
#include "lib/contracts.h"

bitvector press_button(bitvector B, index_t row, index_t col, index_t w, index_t h) {
    ASSERT(is_valid_pos(row, col, w, h));
    bitvector new = bitvector_flip(B, get_index(row, col, w, h));
    // we shouldn't free B: the original board
    if (is_valid_pos(row+1, col, w, h)) {
        bitvector C = new;
        new = bitvector_flip(new, get_index(row+1, col, w, h));
        bitvector_free(C);
    }
    if (is_valid_pos(row, col+1, w, h)) {
        bitvector D = new;
        new = bitvector_flip(new, get_index(row, col+1, w, h));
        bitvector_free(D);
    }
    if (row > 0) {
        bitvector E = new;
        new = bitvector_flip(new, get_index(row-1, col, w, h));
        bitvector_free(E);
    }
    if (col > 0) {
        bitvector F = new;
        new = bitvector_flip(new, get_index(row, col-1, w, h));
        bitvector_free(F);
    } // free all byproduct during flip!!!
    return new;
}

void print_solution(bitvector newboard, index_t width, index_t height, index_t row, 
               index_t col, hdict_t H, bitvector original) {
    // index_t step = 1;
    printf("%u:%u\n", row, col);
    // fprintf(stderr, "%u:%u\n", row, col);
    // char*: current and newboard are alias
    bitvector current = press_button(newboard,row,col,width,height);
    while (!bitvector_equal(current, original)) {
        struct board_data *BOD = ht_lookup(H, current);
        printf("%u:%u\n",BOD->row,BOD->col);
        // fprintf(stderr, "%u:%u\n", row, col);
        // step++;
        bitvector tmp = current;
        current = press_button(current,BOD->row,BOD->col,width,height);
        bitvector_free(tmp);
    }
    bitvector_free(current);
    // fprintf(stderr, "%u\n", step);
}

bool solved(bitvector B, index_t w, index_t h) {
    for (index_t i=0; i<w*h; i++) {
        if (bitvector_get(B, i)) // have true
            return false;
    }
    return true;
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
    if (solved(bvec, width, height)) {
        bitvector_free(bvec);
        fprintf(stderr, "board could be solved\n");
        return EXIT_SUCCESS;
    }
    // fprintf(stderr, "original board\n");
    // print_board(bvec, width, height);
    queue_t Q = queue_new();
    hdict_t H = ht_new(width*height*width*height);

    struct board_data *DAT = xmalloc(sizeof(struct board_data));
    DAT->board = bvec; // original board
    enq(Q, (void*)DAT);
    ht_insert(H,DAT); // put the original to H

    while (!queue_empty(Q)) {
        struct board_data *boardData = (struct board_data*)deq(Q);
        // Consider all the moves
        for (index_t row = 0; row < height; row++) { 
            for (index_t col = 0; col < width; col++) {
                bitvector newboard = press_button(boardData->board, row, col, width, height);
                if (solved(newboard, width, height)) { 
                    print_solution(newboard,width, height, row, col, H, bvec);
                    bitvector_free(newboard);
                    queue_free(Q, NULL);
                    hdict_free(H); // and free its entries
                    fprintf(stderr, "board could be solved\n");
                    return EXIT_SUCCESS;
                }
                if (ht_lookup(H, newboard)==NULL) { // not solved, not in H
                    struct board_data *newBoardData = xmalloc(sizeof(struct board_data));
                    newBoardData->board = newboard;
                    newBoardData->row = row;
                    newBoardData->col = col;
                    enq(Q, (void*)newBoardData);
                    ht_insert(H,newBoardData);
                } else { // already had copy in H
                    bitvector_free(newboard);
                }
            }
        }
    }
    queue_free(Q, NULL);
    hdict_free(H);
    fprintf(stderr, "board could not be solved\n");
    return EXIT_FAILURE;
}