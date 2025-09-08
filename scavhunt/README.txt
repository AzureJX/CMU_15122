15-122 Principles of Imperative Computation
Scavenger Hunt

==========================================================

Files you will modify:
   scavhunt.c0       - tasks 1-4 and 7
   scavhunt-main.c0  - testing the greet function
   compilation.c0    - identifying and fixing compilation errors
   buggy.c0          - fixing the bugs
   puzzle.c0         - puzzle functions
   puzzle-test.c0    - testing the puzzle functions

==========================================================

Files you will not modify:
   compilation-backup.c0  - backup copy of compilation.c0 -- just in case
   compilation-test.c0    - main function for compilation.c0
   buggy-backup.c0        - backup copy of buggy.c0 -- just in case

==========================================================

Compiling and running:
   % cc0 -d -W -o scavhunt scavhunt.c0 scavhunt-main.c0
   % ./scavhunt

   % cc0 -d -W compilation.c0 compilation-test.c0
   % ./a.out

   % coin -d buggy.c0

   % cc0 -d -W -o puzzle puzzle.c0 puzzle-test.c0
   % ./puzzle

==========================================================

Submitting from the command line on andrew:
   % autolab122 handin scavhunt scavhunt.c0 compilation.c0 buggy.c0 puzzle.c0
then display autolab's feedback by running:
   % autolab122 feedback

Creating a tarball to submit with autolab.andrew.cmu.edu web interface:
   % tar -czvf handin.tgz scavhunt.c0 compilation.c0 buggy.c0 puzzle.c0
