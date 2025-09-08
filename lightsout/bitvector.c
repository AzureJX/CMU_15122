/**************************************************************************/
/*              COPYRIGHT Carnegie Mellon University 2025                 */
/* Do not post this file or any derivative on a public site or repository */
/**************************************************************************/
#include <stdbool.h>
#include <stdlib.h>
#include "lib/bitvector.h"
#include "lib/contracts.h"
#include "lib/xalloc.h"

bitvector bitvector_new()
{
  bitvector B = (bitvector)0;
  return B;
}

bool bitvector_get(bitvector B, index_t i)
{
  REQUIRES(i < BITVECTOR_LIMIT);
  bitvector B1 = B >> i;
  return ((((bitvector)1) & B1) == 1);
}

bitvector bitvector_flip(bitvector B, index_t i)
{
  REQUIRES(i < BITVECTOR_LIMIT);
  bitvector mask = ((bitvector)1) << i;
  bitvector C = B ^ mask;
  // bitvector_free(B); // unused B
  return C; // new bitvector
}

bool bitvector_equal(bitvector B1, bitvector B2)
{
  return B1==B2;
}

void bitvector_free(bitvector B)
{
  // (void) var; is used to silence gcc's unused variable warning
  (void) B;     // DELETE ME ONCE DONE
}
