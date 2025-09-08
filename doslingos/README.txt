15-122 Principles of Imperative Computation
Doslingos

==========================================================

Files you will modify:
   doslingos-test.c0    - test count_vocab and sort_by_freq

Files you won't modify:
   lib/int_arrayutil.o0     - A version of arrayutil.c0 for ints
   lib/string_arrayutil.o0  - A version of arrayutil.c0 for strings
   lib/readfile.o0          - File reading library (Part 2, page 4)
   lib/stringsearch.o0      - String searching library (Part 2, pages 4-5)
   doslingos-awful.c0       - Badly broken implementation
   echo.c0                  - Example of using the C0 args library

Files that don't exist yet:
   doslingos.c0         - Code for tasks 1 and 2
   analysis.c0          - Using the DosLingos code to answer questions

Data: (described on page 4 of the handout)
   texts/news_vocab.txt
   texts/small_vocab.txt
   texts/scott_tweet.txt
   texts/sonnets.txt
   texts/shakespeare.txt

   You can create more data files if you would like to use them in
   your tests: just hand these in along with your other files.

==========================================================

Displaying the library interfaces
   % cc0 -i lib/int_arrayutil.o0
   % cc0 -i lib/string_arrayutil.o0
   % cc0 -i lib/readfile.o0
   % cc0 -i lib/stringsearch.o0

Loading all the libraries in coin to play with them:
   % coin lib/*.o0

Compiling doslingos.c0 and tests:
   % cc0 -d -W -w -o doslingos lib/*.o0 doslingos.c0 doslingos-test.c0
   % ./doslingos

Compiling doslingos.c0 and your own tests for binsearch and no_dupes:
   % <fill in the required compilation command>

Compiling doslingos-awful.c0 and tests:
   % cc0 -d -w -o doslingos-bad lib/*.o0 doslingos-awful.c0 doslingos-test.c0
   % ./doslingos-bad

Compiling analysis.c0:
   % cc0 -W -w -o analysis lib/*.o0 doslingos.c0 analysis.c0
   % ./analysis texts/small_vocab.txt texts/scott_tweet.txt
   % ./analysis texts/news_vocab.txt texts/shakespeare.txt

==========================================================

Submitting from the command line on andrew (WITHOUT additional files):
   % autolab122 handin doslingos doslingos.c0 doslingos-test.c0 analysis.c0
then display autolab's feedback by running:
   % autolab122 feedback

Submitting from the command line on andrew (WITH one additional file):
   % autolab122 handin doslingos doslingos.c0 doslingos-test.c0 analysis.c0 texts/my_file.txt
(if you need to submit more than one additional file, append them to
the handin line in the same way)
then display autolab's feedback by running:
   % autolab122 feedback

Creating a tarball to submit with autolab.andrew.cmu.edu web interface:
   % tar -czvf handin.tgz doslingos.c0 doslingos-test.c0 analysis.c0
