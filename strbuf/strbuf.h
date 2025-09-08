/**************************************************************************/
/*              COPYRIGHT Carnegie Mellon University 2025                 */
/* Do not post this file or any derivative on a public site or repository */
/**************************************************************************/
/*
 * String Buffer Library
 *
 * 15-122 Principles of Imperative Computation
 * This version exposes the externals, requires
 * discipline from client! */

#include <stdbool.h>
#include <stdlib.h>

#ifndef STRBUF_H
#define STRBUF_H

struct strbuf_header {
  size_t limit;   /* limit > 0, bytes allocated for buf */
  size_t len;     /* len < limit */
  char *buf;      /* buf != NULL, buf[len] == '\0', strlen(buf) == len */
};
typedef struct strbuf_header strbuf;

bool is_strbuf(strbuf *sb);

strbuf *strbuf_new(size_t init_limit);
char *strbuf_free(strbuf *sb);
char *strbuf_str(strbuf *sb);

void strbuf_add(strbuf *sb, char *str, size_t len);
void strbuf_addstr(strbuf *sb, char *str);
char *strbuf_free(strbuf *sb);

#endif
