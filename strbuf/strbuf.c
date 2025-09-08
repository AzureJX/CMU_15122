#include <stdlib.h>        // standard C library: free, NULL
#include <stdbool.h>       // standard bool type
#include <string.h>        // C version of lib/cstring.o0
#include "lib/contracts.h" // Our contracts library
#include "lib/xalloc.h"    // Our allocation library
#include "strbuf.h"        // The string buffer interface

/*** Implementation ***/
bool is_strbuf(strbuf *sb) {
  if (!(sb != NULL && sb->len < sb->limit))
    return false;
  if (sb->buf == NULL) return false;
  if (sb->buf[sb->len] != '\0') return false;
  for (size_t i=0; i < sb->len; i++)
    if (sb->buf[i] == '\0') return false;
  return true;
}

strbuf *strbuf_new(size_t init_limit)
{
  strbuf *sb = xmalloc(sizeof(strbuf));
  sb->limit = init_limit;
  sb->len = 0;
  sb->buf = xmalloc(sizeof(char)*init_limit);
  sb->buf[0] = '\0';
  ENSURES(is_strbuf(sb));
  return sb;
}

char *strbuf_str(strbuf *sb)
{
  REQUIRES(is_strbuf(sb));
  char *res = xmalloc(sizeof(char) * (sb->len + 1));
  for (size_t i=0; i < sb->len+1; i++)
    res[i] = sb->buf[i];
  ENSURES(res!=NULL);
  ENSURES(res[sb->len] == '\0');
  ENSURES(strlen(res)==sb->len);
  return res;
}

void resize (strbuf *sb, size_t len) // string length
{
  REQUIRES(is_strbuf(sb));
  size_t new_limit = sb->limit * 2 + len;
  ASSERT(sb->len + len < new_limit);
  char *tmp = xmalloc(sizeof(char)*new_limit);
  for (size_t i=0; i<=sb->len; i++)
    tmp[i] = sb->buf[i];
  sb->limit = new_limit;
  free(sb->buf);
  sb->buf = tmp; // tmp disappears in stack when func return
  ENSURES(is_strbuf(sb));
}

void strbuf_add(strbuf *sb, char *str, size_t len)
{
  REQUIRES(str!=NULL);
  REQUIRES(str[len]=='\0'); // no iscstring for c
  REQUIRES(strlen(str)==len);
  REQUIRES(is_strbuf(sb));
  if (sb->len + len > sb->limit - 1) resize(sb, len);
  ASSERT(sb->len + len < sb->limit); // < new buf length
  for (size_t i=0; i<=len; i++) // reach NUL at i == len
    sb->buf[sb->len+i] = str[i];
  sb->len += len;
  ENSURES(is_strbuf(sb));
}

void strbuf_addstr(strbuf *sb, char *str)
{
  REQUIRES(str!=NULL);
  REQUIRES(is_strbuf(sb));
  size_t len = strlen(str);
  strbuf_add(sb, str, len);
  ENSURES(is_strbuf(sb));
}

char *strbuf_free(strbuf *sb)
{
  REQUIRES(is_strbuf(sb));
  char *tmp = sb->buf;
  free(sb);
  ENSURES(tmp!=NULL);
  return tmp;
}

// bad free function
// char *strbuf_free(strbuf *sb) {
//     char *tmp = xmalloc(sizeof(char)*sb->limit);
//     for (size_t i=0; i<=sb->len; i++)
//         tmp[i] = sb->buf[i];
//     free(sb->buf);
//     free(sb);
//     return tmp;
// }