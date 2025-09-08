#include <stdio.h>         // printf
#include <stdlib.h>        // standard C library: free, NULL
#include <stdbool.h>       // standard bool type
#include <string.h>        // C version of lib/cstring.o0
#include <assert.h>        // assert() function
#include "lib/contracts.h" // Our contracts library
#include "lib/xalloc.h"    // Our allocation library
#include "strbuf.h"        // The string buffer interface

bool new_is_strbuf(strbuf *sb) {
  if (!(sb != NULL && sb->len < sb->limit))
    return false;
  if (sb->buf == NULL) return false;
  if (sb->buf[sb->len] != '\0') return false;
  for (size_t i=0; i < sb->len; i++)
    if (sb->buf[i] == '\0') return false;
  return true;
}

int main() {
  // bad strbuf
  strbuf *sb = xmalloc(sizeof(strbuf));
  // assert(!is_strbuf(sb)); undefined behavior
  size_t limit = 5;
  sb->limit = limit;
  sb->len = 3; // wrong length
  sb->buf = xmalloc(sizeof(char)*limit);
  sb->buf[0] = 'a'; sb->buf[2] = 'd';
  sb->buf[1] = '\0'; sb->buf[3] = 'n';
  sb->buf[4] = '1';
  /* need to define buf[3]: is_strbuf will access buf[3]
  I used xmalloc instead of calloc to create sb->buf
  so no default value for each cell */
  assert(!is_strbuf(sb));
  free(sb->buf);
  free(sb); 
  // can't use strbuf_free because sb is not real sb
  
  strbuf *sb11 = xmalloc(sizeof(strbuf));
  // assert(!is_strbuf(sb11)); undefined behavior
  size_t limit11 = 6;
  sb11->limit = 2;  // too big limit
  sb11->len = 3;
  sb11->buf = xmalloc(sizeof(char)*limit11);
  sb11->buf[0] = 'a'; sb11->buf[1] = 'd';
  sb11->buf[2] = '6'; sb11->buf[3] = '\0';
  assert(!is_strbuf(sb11));
  free(sb11->buf);
  free(sb11); 
  
  strbuf *sb22 = xmalloc(sizeof(strbuf));
  sb22->limit = 10;
  sb22->len = 5;
  sb22->buf = NULL;
  assert(!is_strbuf(sb22));
  free(sb22);

  // autograde undefined on no NUL sb
  // strbuf *sb22 = xmalloc(sizeof(strbuf));
  // size_t limit22 = 12;
  // sb22->limit = limit22;
  // sb22->len = 3;
  // sb22->buf = xmalloc(sizeof(char)*limit22);
  // sb22->buf[0] = 'h'; sb22->buf[1] = '2';
  // sb22->buf[2] = 'o'; sb22->buf[3] = 'l';
  // // need to define buf[3]: is_strbuf will access buf[3]
  // assert(!is_strbuf(sb22));
  // free(sb22->buf);
  // free(sb22); 

  strbuf *sb33 = xmalloc(sizeof(strbuf));
  size_t limit33 = 12;
  sb33->limit = limit33;
  sb33->len = 3;
  sb33->buf = xmalloc(sizeof(char)*limit33);
  sb33->buf[0] = 'b'; sb33->buf[1] = 'c';
  sb33->buf[2] = '\0'; sb33->buf[3] = '\0';
  assert(!is_strbuf(sb33));
  free(sb33->buf);
  free(sb33); 

  // 0
  strbuf *sb0 = strbuf_new(1);
  assert(new_is_strbuf(sb0));
  assert(is_strbuf(sb0));
  assert(sb0->buf[0] == '\0');
  char *string0 = strbuf_free(sb0);
  assert(strlen(string0)==0);
  free(string0);

  // 1
  strbuf *sb1 = strbuf_new(3);
  assert(new_is_strbuf(sb1));
  assert(is_strbuf(sb1));
  assert(sb1->buf[0] == '\0');
  char str1[] = "ab";
  
  strbuf_add(sb1, str1, 2); // "ab"
  assert(new_is_strbuf(sb1));
  assert(is_strbuf(sb1));
  assert(strlen(sb1->buf)==2);
  assert(sb1->buf[0] == 'a');
  assert(sb1->buf[1] == 'b');
  assert(sb1->buf[2] == '\0');
  assert(sb1->limit == 3); // no resize

  char *str11 = strbuf_str(sb1);
  assert(str11!=NULL);
  assert(strlen(str11)==2);
  assert(str11 != sb1->buf);
  assert(str11[0] == 'a');
  assert(str11[1] == 'b');
  assert(str11[2] == '\0');
  free(str11);

  strbuf_addstr(sb1, str1); // "abab"
  assert(new_is_strbuf(sb1));
  assert(is_strbuf(sb1));
  assert(strlen(sb1->buf)==4);
  assert(sb1->buf[0] == 'a');
  assert(sb1->buf[1] == 'b');
  assert(sb1->buf[2] == 'a');
  assert(sb1->buf[3] == 'b');
  assert(sb1->buf[4] == '\0');
  assert(sb1->limit > 3); // resize

  char *str21 = strbuf_str(sb1);
  assert(str21!=NULL);
  assert(strlen(str21)==4);
  assert(str21 != sb1->buf);
  assert(str21[0] == 'a');
  assert(str21[1] == 'b');
  assert(str21[2] == 'a');
  assert(str21[3] == 'b');
  assert(str21[4] == '\0');
  free(str21); // strbuf_str uses xmalloc

  // char *tmp = sb1->buf;
  char *string1 = strbuf_free(sb1);
  assert(string1 != NULL);
  // assert(string1==tmp); 
  // tmp might be freed by wrong implementation of strbuf_free
  assert(strlen(string1)==4);
  assert(string1[0] == 'a');
  assert(string1[3] == 'b');
  assert(string1[4] == '\0');
  // free(tmp); double free!!!
  free(string1);
  
  // 2
  strbuf *sb2 = strbuf_new(9);
  assert(new_is_strbuf(sb2));
  assert(sb2->buf[0] == '\0');
  char *s_stack = "0b3j7";
  char *str2 = xmalloc(sizeof(char)*10); // larger than needed
  strcpy(str2, s_stack);

  strbuf_addstr(sb2, str2);
  assert(new_is_strbuf(sb2));
  assert(is_strbuf(sb2));
  assert(sb2->buf[0] == '0');
  assert(sb2->buf[2] == '3');
  assert(sb2->buf[4] == '7');
  assert(strlen(sb2->buf)==5);
  assert(sb2->limit == 9); // no resize

  strbuf_add(sb2, str2, 5);
  assert(new_is_strbuf(sb2));
  assert(is_strbuf(sb2));
  assert(sb2->buf[3] == 'j');
  assert(sb2->buf[1] == 'b');
  assert(sb2->buf[5] == '0');
  assert(sb2->buf[7] == '3');
  assert(sb2->buf[9] == '7');
  assert(strlen(sb2->buf)==10);
  assert(sb2->limit > 9); // resize

  char *str22 = strbuf_str(sb2);
  assert(str22!=NULL);
  assert(strlen(str22)==10);
  assert(str22 != sb2->buf);
  assert(str22[0] == '0');
  assert(str22[2] == '3');
  assert(str22[4] == '7');
  assert(str22[6] == 'b');
  assert(str22[8] == 'j');
  assert(str22[10] == '\0');
  free(str22); // strbuf_str uses xmalloc

  free(str2);

  char *string2 = strbuf_free(sb2);
  assert(string2 != NULL);
  assert(strlen(string2)==10);
  assert(string2[0] == '0');
  assert(string2[2] == '3');
  assert(string2[4] == '7');
  assert(string2[6] == 'b');
  assert(string2[8] == 'j');
  assert(string2[10] == '\0');
  free(string2);
  // free(tmp2); double free!!!

  // 3 Free - copy or alias?
  strbuf *sb3 = strbuf_new(6);
  assert(new_is_strbuf(sb3));
  sb3->buf[0] = 'k';
  sb3->buf[1] = '\0';
  sb3->len = 1;
  sb3->buf[2] = '7';
  sb3->buf[5] = '4';

  char *tmp = sb3->buf;
  char *string3 = strbuf_free(sb3);
  assert(string3[2] == '7');
  assert(string3[5] == '4');
  assert(tmp==string3);
  free(string3);

  // 4 Free
  // strbuf *sb4 = strbuf_new(5);
  // assert(new_is_strbuf(sb4));
  // sb4->buf[0] = 'k';
  // sb4->buf[1] = 's';
  // sb4->buf[2] = '\0';
  // sb4->len = 2;
  // char *tmp = sb4->buf;

  // char *string4 = strbuf_free(sb4);
  // assert(tmp==string4);
  // free(string4);

  printf("All tests passed!\n");
  return 0;
}