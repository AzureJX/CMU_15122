15-122 Principles of Imperative Computation
String Buffers

==========================================================

Files you won't modify:
   lib/cstring.o0  - C0 implementation of some of the C string.h library
   strbuf.h        - Interface to string buffers
   lib/contracts.h - Contracts for C
   lib/xalloc.h    - NULL-checking allocation

   Include the contracts and xalloc library interfaces in your C code
   by writing:
   #include "lib/contracts.h"
   #include "lib/xalloc.h"

Files you may extend:
   strbuf.c0       - Implementation of string buffers (C0)
   strbuf-test.c0  - Testing for strbuf.c0

Files that don't exist yet:
   strbuf.c        - Implementation of string buffers (C)
   strbuf-test.c   - Testing for strbuf.c

==========================================================

Displaying the library interfaces
   % cc0 -i lib/cstring.o0

Compiling C0 code with contracts:
   % cc0 -d -W -w lib/*.o0 strbuf.c0 strbuf-test.c0
   % ./a.out

Compiling C0 code without contracts:
   % cc0 -W -w lib/*.o0 strbuf.c0 strbuf-test.c0
   % ./a.out

Compiling C code with contracts:
   % gcc -DDEBUG -fsanitize=undefined -g -Wall -Wextra -Werror -Wshadow -std=c99 -pedantic strbuf.c strbuf-test.c
   % ./a.out

Compiling C code without contracts:
   % gcc -g -Wall -Wextra -Werror -Wshadow -std=c99 -pedantic strbuf.c strbuf-test.c
   % ./a.out

==========================================================

Submitting from the command line on andrew:
   % autolab122 handin strbuf strbuf.c strbuf.c0 strbuf-test.c strbuf-test.c0
then display autolab's feedback by running:
   % autolab122 feedback

Creating a tarball to submit with autolab.andrew.cmu.edu web interface:
   % tar -czvf handin.tgz strbuf.c strbuf.c0 strbuf-test.c strbuf-test.c0
