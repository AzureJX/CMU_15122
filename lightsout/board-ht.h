/**************************************************************************/
/*              COPYRIGHT Carnegie Mellon University 2025                 */
/* Do not post this file or any derivative on a public site or repository */
/**************************************************************************/
/*
 * Hash tables wrapper
 *
 * 15-122 Principles of Imperative Computation */

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "lib/bitvector.h"
#include "lib/hdict.h"

#ifndef BOARD_HASHTABLE_H
#define BOARD_HASHTABLE_H

struct board_data {
  // Ignore this field (but don't remove it or change its type)
  index_t test;

  // This part of the struct acts like the key
  bitvector board;
  index_t row;
  index_t col;
  // You can add more fields to this struct
  // in order to help you implement the later tasks.
};

/* IMPORTANT: You must respect the hash set interface in hdict.h when
 * writing your implementation of these functions! */

/* Initializes a new hash table with the given capacity */
hdict_t ht_new(size_t capacity)
  /*@requires capacity > 0; @*/
  /*@ensures \result != NULL; @*/ ;

/* ht_lookup(H,B) returns
 * NULL if no struct containing the board B exists in H
 * A struct containing the board B if one exists in H.
 */
struct board_data *ht_lookup(hdict_t H, bitvector B)
  /*@requires H != NULL; @*/ ;

/* ht_insert(H,e) has no return value, because it should have as
 * a precondition that no struct currently in the hashtable contains
 * the same board as DAT->board.
 */
void ht_insert(hdict_t H, struct board_data *DAT)
  /*@requires H != NULL; @*/ ;

#endif
