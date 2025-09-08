/**************************************************************************/
/*              COPYRIGHT Carnegie Mellon University 2025                 */
/* Do not post this file or any derivative on a public site or repository */
/**************************************************************************/
/*
 * Bit vectors - fixed-width vectors of bits w/ a toggle function
 *
 * Both implementations and clients should allow for different
 * BITVECTOR_LIMIT values.
 *
 * 15-122 Principles of Imperative Computation */

#include <stdbool.h>
#include <stdint.h>

#ifndef BITVECTOR_H
#define BITVECTOR_H

// type of indices into bit vectors
typedef uint8_t index_t;

// largest possible value of the type index_t
#define MAX_INDEX_VALUE UINT8_MAX

// typedef _______ bitvector;
// typedef uint32_t bitvector;
typedef char* bitvector;
// typedef char* bitvector;

// Number of bits of the bit vector (from the client perspective)
// should be <= MAX_INDEX_VALUE and <= the number of bits in bitvector
// #define BITVECTOR_LIMIT 25
#define BITVECTOR_LIMIT 100

/* Get a new bitvector with everything set to 'false'. */
bitvector bitvector_new();

/* Get the ith bit of the bitvector n. */
bool bitvector_get(bitvector B, index_t i)
  /*@requires 0 <= i < BITVECTOR_LIMIT; @*/ ;

/* Toggle the ith bit of the bitvector n, returning a bitvector which has
   that position flipped */
bitvector bitvector_flip(bitvector B, index_t i)
  /*@requires 0 <= i < BITVECTOR_LIMIT; @*/ ;

/* Compare two bitvectors for equality. */
bool bitvector_equal(bitvector B1, bitvector B2);

/* Frees memory associated with the bitvector (if any) */
void bitvector_free(bitvector B);

#endif
