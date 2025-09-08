/**************************************************************************/
/*              COPYRIGHT Carnegie Mellon University 2025                 */
/* Do not post this file or any derivative on a public site or repository */
/**************************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "lib/contracts.h"
#include "lib/xalloc.h"
#include "lib/bitvector.h"
#include "board-ht.h"

// You are welcome to define helper functions for your tests

int main() {
  // Create a few struct board_data
  struct board_data *DAT1 = calloc(1, sizeof(struct board_data));
  DAT1->board = bitvector_new();
  DAT1->board = bitvector_flip(DAT1->board, 21);
  DAT1->board = bitvector_flip(DAT1->board, 10);

  struct board_data *DAT2 = calloc(1, sizeof(struct board_data));
  DAT2->board = bitvector_new();
  DAT2->board = bitvector_flip(DAT2->board, 21);
  DAT2->board = bitvector_flip(DAT2->board, 10);
  DAT2->board = bitvector_flip(DAT2->board, 5);
  
  // Using them, test the functions you wrote in file board-ht.c
  bitvector B1 = bitvector_new();
  B1 = bitvector_flip(B1, 21);
  B1 = bitvector_flip(B1, 10);

  bitvector B2 = bitvector_new();
  B2 = bitvector_flip(B2, 21);
  B2 = bitvector_flip(B2, 5);
  B2 = bitvector_flip(B2, 10);

  bitvector B3 = bitvector_new();
  B3 = bitvector_flip(B3, 21);
  B3 = bitvector_flip(B3, 5);

  hdict_t H = ht_new(10);
  struct board_data *res1 = ht_lookup(H, B1);
  assert(res1==NULL); // do not exist

  ht_insert(H, DAT1);
  struct board_data *res2 = ht_lookup(H, B1);
  assert(res2==DAT1);

  // bitvector b1 = DAT1->board;
  // bitvector b2 = DAT2->board;
  // printf("%u %u %u %u\n", b1, b2, B1, B2);

  ht_insert(H, DAT2);
  struct board_data *res3 = ht_lookup(H, B2);
  assert(res3==DAT2);
  
  struct board_data *res4 = ht_lookup(H, B3);
  assert(res4==NULL); // do not exist

  // it will fail the precondition of insert:
  // ht_insert(H, DAT1);

  hdict_free(H);
  // no need to free DAT b/c it was freed as an entry

  printf("All tests passed!\n");
  return 0;
}
