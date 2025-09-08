#include <stdbool.h>
#include <stdlib.h>
#include "board-ht.h"
#include "lib/contracts.h"
#include "lib/xalloc.h"
#include "lib/bitvector.h"

hdict_key entry_key(hdict_entry e) {  // e is void *
    struct board_data *BD = (struct board_data*) e;
    bitvector *res = &(BD->board);
    return (void*)res;
}

bool key_equal(hdict_key k1, hdict_key k2) {
    bitvector bitvector1 = *((bitvector*)k1);
    bitvector bitvector2 = *((bitvector*)k2);
    return bitvector_equal(bitvector1,bitvector2);
}

size_t key_hash(hdict_key k) {
    bitvector bv = *((bitvector*)k);
    size_t h = 1;
    size_t b = 1;
    for (index_t i = 0; i < BITVECTOR_LIMIT; i++) {
        h = h + bitvector_get(bv, i)*b;
        b++;
    }
    return h;
}

void entry_free(hdict_entry e) {
    struct board_data *BD = (struct board_data*) e;
    bitvector_free(BD->board);
    free(BD);
}

hdict_t ht_new(size_t capacity) {
    return hdict_new(capacity, &entry_key, &key_equal,
                     &key_hash, &entry_free); // or NULL
}

struct board_data *ht_lookup(hdict_t H, bitvector B) {
    bitvector *p = &B;
    hdict_entry res = hdict_lookup(H, (void*)p);
    if (res==NULL) return NULL;
    return (struct board_data*)res;
}

void ht_insert(hdict_t H, struct board_data *DAT) {
    REQUIRES(ht_lookup(H,DAT->board)==NULL);
    hdict_entry e = (hdict_entry)DAT;
    hdict_entry old = hdict_insert(H, e);
    assert(old==NULL);
}