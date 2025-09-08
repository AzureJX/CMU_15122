/**************************************************************************/
/*              COPYRIGHT Carnegie Mellon University 2025                 */
/* Do not post this file or any derivative on a public site or repository */
/**************************************************************************/
/*
 * Board utilities
 *
 * 15-122 Principles of Imperative Computation
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "contracts.h"
#include "bitvector.h"
#include "boardutil.h"

/* Valid board dimensions */
bool is_valid_boardsize(index_t width, index_t height) {
  if (width == 0) return false;
  if (height == 0) return false;
  if (!(width <= MAX_INDEX_VALUE / height)) return false;
  if (!(width*height <= BITVECTOR_LIMIT)) return false;
  return true;
}

bool is_valid_pos(index_t row, index_t col, index_t width, index_t height) {
  REQUIRES(is_valid_boardsize(width, height));
  return row < height && col < width;
}


/* Read from a file, but ignore whitespace */
static inline int read_non_space(FILE *F) {
  int c;
  do c = fgetc(F);
  while (isspace(c));
  return c;
}

/* Interprets a char as a digit, returns -1 if it isn't one */
static inline int digit(int c) {
  if ('0' <= c && c <= '9')
    return c - '0';
  return -1;
}

/* Reads the width, height, and bitvector out of a file */
/* Returns true if successful, false otherwise */
bool file_read(char *path,
               bitvector *vec_out,
               index_t *width_out,
               index_t *height_out) {
  REQUIRES(path != NULL);
  REQUIRES(vec_out != NULL && width_out != NULL && height_out != NULL);

  bitvector board = bitvector_new();

  /* Open a file for reading */
  FILE *F = fopen(path, "r");
  if (F == NULL) {
    fprintf(stderr, "file_read: unable to open file %s", path);
    bitvector_free(board);
    return false;
  }

  /* Read width x height from file, return 'false' if invalid */
  int c;
  index_t width = 0;
  while(digit(c = read_non_space(F)) != -1)
  {
    //Overflow check
    if(width > (MAX_INDEX_VALUE - digit(c)) / 10)
    {
      fprintf(stderr, "file_read: width too large for index_t type in file %s\n", path);
      fclose(F);
      bitvector_free(board);
      return false;
    }
    width = width * 10 + digit(c);
  }
  if (width <= 0) {
    fprintf(stderr, "file_read: bad width in file %s\n", path);
    fclose(F);
    bitvector_free(board);
    return false;
  }
  if (c != 'x') {
    fprintf(stderr, "file_read: invalid size spec in %s\n", path);
    fclose(F);
    bitvector_free(board);
    return false;
  }
  index_t height = 0;
  while(digit(c = read_non_space(F)) != -1)
  {
    //Overflow check
    if(height > (MAX_INDEX_VALUE - digit(c)) / 10)
    {
      fprintf(stderr, "file_read: height too large for index_t type in file %s\n", path);
      fclose(F);
      bitvector_free(board);
      return false;
    }
    height = height * 10 + digit(c);
  }
  if (height <= 0) {
    fprintf(stderr, "file_read: bad height in file %s\n", path);
    fclose(F);
    bitvector_free(board);
    return false;
  }
  /* Board too big for this implementation of bitvectors */
  if (!is_valid_boardsize(width, height)) {
    fprintf(stderr, "file_read: board in %s is too big\n", path);
    fclose(F);
    bitvector_free(board);
    return false;
  }
  /* Read the board contents, toggle all the '#' spaces. */
  for (index_t i = 0; i < width * height; i++) {
    if (c == '#') {
      bitvector new_board = bitvector_flip(board, i);
      if(new_board != board) {
        bitvector_free(board);
      }
      board = new_board;
    }
    else if (c != 'O') {
      if (c == EOF) {
        fprintf(stderr, "file_read: board in %s is smaller than spec\n", path);
      } else {
        fprintf(stderr, "file_read: invalid character %c in %s\n", c, path);
      }
      fclose(F);
      bitvector_free(board);
      return false;
    }
    c = read_non_space(F);
  }

  // Check that we're at the end of the file
  fclose(F);
  if (EOF != c) {
    fprintf(stderr, "file_read: board in %s is larger than spec\n", path);
    bitvector_free(board);
    return false;
  }

  ENSURES(is_valid_boardsize(width, height));
  *width_out = width;
  *height_out = height;
  *vec_out = board;
  return true;
}

void print_board(bitvector vec, index_t width, index_t height) {
  REQUIRES(is_valid_boardsize(width, height));

  for (index_t row = 0; row < height; row++) {
    for (index_t col = 0; col < width; col++) {
      index_t i = row * width + col;
      if (bitvector_get(vec, i)) fprintf(stderr, "#");
      else fprintf(stderr, "O");
    }
    fprintf(stderr, "\n");
  }
}

/* Index lookup */
index_t get_index(index_t row, index_t col, index_t width, index_t height) {
  REQUIRES(is_valid_boardsize(width, height));
  REQUIRES(is_valid_pos(row, col, width, height));

  (void)height;

  return row*width + col;
}
