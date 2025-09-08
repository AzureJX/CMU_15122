#include <stdlib.h>
#include <stdio.h>
#include "lib/xalloc.h"
#include "lib/boardutil.h"
#include "lib/bitvector.h"
#include "board-ht.h" // hdict
#include "lib/queue.h"
#include "lib/contracts.h"

bitvector press_button(bitvector B, index_t row, index_t col, index_t w, index_t h) {
    if (is_valid_pos(row, col, w, h)) {
        B = bitvector_flip(B, get_index(row, col, w, h));
    }
    if (is_valid_pos(row+1, col, w, h)) {
        B = bitvector_flip(B, get_index(row+1, col, w, h));
    }
    if (is_valid_pos(row, col+1, w, h)) {
        B = bitvector_flip(B, get_index(row, col+1, w, h));
    }
    if (row > 0) {
        B = bitvector_flip(B, get_index(row-1, col, w, h));
    }
    if (col > 0) {
        B = bitvector_flip(B, get_index(row, col-1, w, h));
    }
    return B;
}

int main() {
    bitvector B = bitvector_flip(B, 1);
    B = press_button(B,0,0,2,2);
    print_board(B,2,2);
    return 0;
}