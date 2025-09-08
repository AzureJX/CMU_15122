/**************************************************************************/
/*              COPYRIGHT Carnegie Mellon University 2025                 */
/* Do not post this file or any derivative on a public site or repository */
/**************************************************************************/
/*
 * Board utilities
 *
 * 15-122 Principles of Imperative Computation  */

#include <stdbool.h>
#include <stdint.h>
#include "bitvector.h"

#ifndef BOARDUTIL_H
#define BOARDUTIL_H

/* Check whether a width and height are valid boards,
 * representable as bit vectors */
bool is_valid_boardsize(index_t width, index_t height);

/* Check whether row and column are valid boards for the given width
 * and height
 */
bool is_valid_pos(index_t row, index_t col, index_t width, index_t height)
  /*@requires is_valid_boardsize(width, height); @*/ ;

/* Get the index for a position (standard row-major ordering used in
 * the image and lightsout assignments)
 */
index_t get_index(index_t row, index_t col, index_t width, index_t height)
  /*@requires is_valid_boardsize(width, height); @*/
  /*@requires is_valid_pos(row, col, width, height); @*/ ;

/* Tries to read a lightboard from the file 'path'
 * Failure: returns false
 * Success: writes the vector of bits into 'vec_out'
 *          writes the width into 'width_out'
 *          writes the height into 'height_out'
 *
 * Requires: All non-NULL pointers, path must be a string
 * Ensures: !\result || is_valid_boardsize(*width_out, *height_out) */
bool file_read(char *path,
               bitvector *vec_out,
               index_t *width_out,
               index_t *height_out)
  /*@requires path != NULL && vec_out != NULL; @*/
  /*@requires width_out != NULL && height_out != NULL; @*/
  /*@ensures !\result || is_valid_boardsize(*width_out, *height_out); @*/ ;

/* Prints a representation of the board to standard error
 */
void print_board(bitvector vec, index_t width, index_t height)
  /*@requires is_valid_boardsize(width, height); @*/ ;

#endif