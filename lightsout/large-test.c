/**************************************************************************/
/*              COPYRIGHT Carnegie Mellon University 2025                 */
/* Do not post this file or any derivative on a public site or repository */
/**************************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "lib/xalloc.h"
#include "lib/contracts.h"
#include "lib/bitvector.h"
#include "board-ht.h"


// You are welcome to define helper functions for your tests

bitvector press_button(bitvector B, index_t i) {
    bitvector new = bitvector_flip(B, i);
    // we shouldn't free B: the original board
        bitvector C = new;
        new = bitvector_flip(new, i+1);
        bitvector_free(C);

        bitvector D = new;
        new = bitvector_flip(new, i+2);
        bitvector_free(D);
    
        bitvector E = new;
        new = bitvector_flip(new, i+3);
        bitvector_free(E);
    
        bitvector F = new;
        new = bitvector_flip(new, i+4);
        bitvector_free(F);
    // free all byproduct during flip!!!
    return new;
}

int main() {
    bitvector R = bitvector_new();
    struct board_data *DAT = xmalloc(sizeof(struct board_data));
    DAT->board = R;
    DAT->row = 2;
    DAT->col = 2;
    hdict_t H = ht_new(10);
    ht_insert(H,DAT);
    assert(ht_lookup(H,R)!=NULL);
    hdict_free(H);
    
    
    
    
    // bitvector T = bitvector_new();
    // bitvector tmp = T;
    // assert(tmp==T);
    // T = bitvector_flip(T,52); // T becomes a new vector
    // bitvector_free(tmp); // tmp is the old T

    // bitvector new = press_button(T,3);
    // assert(bitvector_get(new,5));

    // bitvector_free(T);
    // bitvector_free(new);

    // bitvector B = bitvector_new();  
    // B = bitvector_flip(B, 12);
    // assert(bitvector_get(B,12));
    // assert(!bitvector_get(B,11));
    // assert(!bitvector_get(B,10));
    // B = bitvector_flip(B,22);

    // bitvector C = bitvector_new();
    // C = bitvector_flip(C,22);
    // C = bitvector_flip(C,12);
    // C = bitvector_flip(C,17);
    // C = bitvector_flip(C,17);
    // assert(!bitvector_get(B, 17));
    // // printf("%d %d\n", B,C);
    // assert(bitvector_equal(B, C));

    // bitvector D = bitvector_new();
    // D = bitvector_flip(D,0);
    // D = bitvector_flip(D,1);
    // D = bitvector_flip(D,2);
    // D = bitvector_flip(D,3);
    // assert(bitvector_get(D,3));
    // assert(bitvector_get(D,0));
    // assert(bitvector_get(D,1));
    // assert(bitvector_get(D,2));
    // D = bitvector_flip(D,2);
    // D = bitvector_flip(D,3);
    // assert(!bitvector_get(D,2));
    // assert(!bitvector_get(D,3));

    // bitvector_free(B);
    // bitvector_free(C);
    // bitvector_free(D);

    // // large board
    // bitvector L = bitvector_new(); // 56 66
    // L = bitvector_flip(L, 56);
    // L = bitvector_flip(L, 42);
    // L = bitvector_flip(L, 37);
    // L = bitvector_flip(L, 66);
    // L = bitvector_flip(L, 37);
    // L = bitvector_flip(L, 42);
    // assert(!bitvector_get(L, 37));
    // assert(bitvector_get(L, 66));

    // bitvector A = bitvector_new();
    // A = bitvector_flip(A, 66);
    // A = bitvector_flip(A, 56);

    // assert(bitvector_equal(L, A));
    // bitvector_free(L);
    // bitvector_free(A);

    printf("All tests passed!\n");
    return 0;
}