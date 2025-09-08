/**************************************************************************/
/*              COPYRIGHT Carnegie Mellon University 2025                 */
/* Do not post this file or any derivative on a public site or repository */
/**************************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "lib/contracts.h"
#include "lib/bitvector.h"

// You are welcome to define helper functions for your tests

int main() {
  // Create a few bitvectors
  bitvector B = bitvector_new();
  // Using them, test the functions you wrote in file bitvector.c
  
  B = bitvector_flip(B, 12);
  assert(bitvector_get(B,12));
  assert(!bitvector_get(B,11));
  assert(!bitvector_get(B,10));
  B = bitvector_flip(B,22);

  bitvector C = bitvector_new();
  C = bitvector_flip(C,22);
  C = bitvector_flip(C,12);
  C = bitvector_flip(C,17);
  C = bitvector_flip(C,17);
  assert(!bitvector_get(B, 17));
  // printf("%d %d\n", B,C);
  assert(bitvector_equal(B, C));

  bitvector D = bitvector_new();
  D = bitvector_flip(D,0);
  D = bitvector_flip(D,1);
  D = bitvector_flip(D,2);
  D = bitvector_flip(D,3);
  assert(bitvector_get(D,3));
  assert(bitvector_get(D,0));
  assert(bitvector_get(D,1));
  assert(bitvector_get(D,2));
  D = bitvector_flip(D,2);
  D = bitvector_flip(D,3);
  assert(!bitvector_get(D,2));
  assert(!bitvector_get(D,3));

  printf("All tests passed!\n");
  return 0;
}
