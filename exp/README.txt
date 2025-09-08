15-122 Principles of Imperative Computation
Clac and EXP

==========================================================

Files you won't modify:
   lib/stack_of_int.o0           - Stacks containing integers (istack_t)
   lib/stack_of_string.o0        - Stacks containing strings (stack_t)
   lib/queue_of_string.o0        - Queues containing strings (queue_t)
   lib/stack_of_string_stacks.o0 - Stacks containing stacks of strings (sstack_t)
   lib/utils.o0                  - Library for populating queues of strings
   clac-main.c0                  - Runs clac read-eval-print loop (REPL)
   exp-main.c0                   - Runs EXP read-eval-print loop (REPL)

Files that don't exist yet
   clac.c0               - Clac interpreter
   parse.c0              - Parser for turning EXP programs into Clac

Files you will modify:
   dict.c0               - Precedence dictionary implementation
   exp-defs.clac         - Clac definitions for missing EXP operations

   clac-test.c0          - Testing the Clac implementation (Optional)
   dict-test.c0          - Testing the dict implementation (Optional)
   is_prectstack-test.c0 - Testing the is_prectstack implementation (Optional)
   exp-test.c0           - Testing the EXP implementation (Optional)

==========================================================

Running the reference implementation of the Claculator (Andrew Linux only):
   Run without tracing, but with the exp-defs.clac definitions loaded
   % clac-ref -trace exp-defs.clac
   clac>> 8 5 ==
   clac>> 4 3 * 7 5 + == 1 && 1 ==

   Run with tracing, without the exp-defs.clac definitions loaded
   % clac-ref -trace
   clac>> 8 5 4 - + dup
   clac>> print print
   clac>> quit

Displaying the library interfaces
   % cc0 -i lib/stack_of_int.o0
   % cc0 -i lib/stack_of_string.o0
   % cc0 -i lib/queue_of_string.o0
   % cc0 -i lib/stack_of_string_stacks.o0
   % cc0 -i lib/utils.o0

Compiling and running the Claculator:
   % cc0 -d -W -w -o clac lib/*.o0 clac.c0 clac-main.c0
   % ./clac

Compiling and running Clac test cases:
   % cc0 -d -W -w -o clac-test lib/*.o0 clac.c0 clac-test.c0
   % ./clac-test

Compiling and running the dictionary and provided tests:
   % cc0 -d -W -w -o dict-test lib/*.o0 dict.c0 dict-test.c0
   % ./dict-test

Compiling and running your tests for is_precstack
   % cc0 -d -W -w -o is_precstack-test lib/*.o0 dict.c0 parse.c0 is_precstack-test.c0
   % ./is_precstack-test

Compiling and running the parser:
   % cc0 -d -W -w -o exp lib/*.o0 clac.c0 dict.c0 parse.c0 exp-main.c0
   % ./exp
   EXP>> 1 + 3 * 4 == 13
   % ./exp -x
   EXP>> 1 + -3 * 4 / -2 ** 3

Compiling and running the parser tests:
   % cc0 -d -W -w -o exp-test lib/*.o0 clac.c0 dict.c0 parse.c0 exp-test.c0
   % ./exp-test

==========================================================

Submitting from the command line on andrew:
   % autolab122 handin exp clac.c0 dict.c0 parse.c0 exp-defs.clac
then display autolab's feedback by running:
   % autolab122 feedback

Creating a tarball to submit with autolab.andrew.cmu.edu web interface:
   % tar -czvf handin.tgz clac.c0 dict.c0 parse.c0 exp-defs.clac
