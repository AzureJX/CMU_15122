#include <stdbool.h>
#include <stdlib.h>
#include "lib/bitvector.h"
#include "lib/contracts.h"
#include "lib/xalloc.h"

bitvector bitvector_new() {
    bitvector B = xcalloc(1,sizeof(char)*BITVECTOR_LIMIT);
    // bitvector B = xcalloc(1,sizeof(bool)*BITVECTOR_LIMIT);
    return B;
}

bool bitvector_get(bitvector B, index_t i) {
    REQUIRES(i < BITVECTOR_LIMIT);
    return (B[i]!=0);
}

bitvector bitvector_flip(bitvector B, index_t i) {
    REQUIRES(i < BITVECTOR_LIMIT);
    bitvector C = bitvector_new();
    for(index_t j=0; j<BITVECTOR_LIMIT; j++) {
        C[j] = B[j];
    }
    C[i] = !C[i];
    return C; // allocate new memory and B is not freed
}

bool bitvector_equal(bitvector B1, bitvector B2) {
    for(index_t i=0; i<BITVECTOR_LIMIT; i++) {
        if (B1[i] != B2[i]) return false;
    }
    return true;
}

void bitvector_free(bitvector B) {
    free(B);
}