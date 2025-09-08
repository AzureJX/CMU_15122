m15-122 Principles of Imperative Computation
Lights Out

==========================================================

Files you won't modify:
   lib/contracts.h           - Contracts for C
   lib/xalloc.h              - NULL-checking allocation
   lib/boardutil.{c,h}       - Useful Lights-Out relevant functions
   lib/hdict.h               - Dictionaries, implemented as hash tables
   lib/queue.h               - Queues
   lib/*.o                   - machine-specific object files
   Makefile                  - Utility for building this project

Files you may modify for testing and bonus, but SHOULD NOT SUBMIT:
   lib/bitvector.h           - Interface to bit vectors

Files you may extend:
   bitvector.c               - Bit vector implementation
   board-ht.h                - Interface to hashtables keyed by boards
   bitvector-test.c          - Your unit tests for bitvector.c (Optional)
   board-ht-test.c           - Your unit tests for board-ht.c (Optional)

Files that don't exist yet:
   board-ht.c                - Bit vector hashtable wrapper implementation
   lightsout.c               - Lights out implementation (needs a main() function)
   bitvector-large.c         - Bit vector implementation for large boards (Bonus)
   boards/my-large-board.txt - Some large board (Bonus)

==========================================================

Compiling your bitvector unit tests (with -DDEBUG)
   % make bitvector-test
   % ./bitvector-test

Compiling your board-ht unit tests (with -DDEBUG)
   % make board-ht-test
   % ./board-ht-test

Compiling and running your lights out solver (with -DDEBUG)
   % make
   % ./lightsout-d boards/2x2-0.txt

Compiling and running your lights out solver (without -DDEBUG)
   % make
   % ./lightsout boards/2x2-0.txt

Compiling and running your lights out solver for large boards
   % make large
   % ./lightsout-large boards/my-large-board.txt

==========================================================

Submitting from the command line on andrew:
   % autolab122 handin lightsout lightsout.c board-ht.h board-ht.c bitvector.c bitvector-large.c
then display autolab's feedback by running:
   % autolab122 feedback

Creating a tarball to submit with autolab.andrew.cmu.edu web interface:
   % tar -czvf handin.tgz lightsout.c board-ht.h board-ht.c bitvector.c bitvector-large.c

You may omit bitvector-large.c until you do the associated task.
