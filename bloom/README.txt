15-122 Principles of Imperative Computation
Bloom Filters

==========================================================

Files you won't modify:
   bloom-worst.o0     - Fully non-commital Bloom filter
   bloom-expensive.o0 - Memory and time expensive "perfect" Bloom filter
   bt.o0              - Bool table library
   hashes.c0          - Common hash functions in C0
   data/*             - Test data for the hash function visualizer and for
                        the password checker

Files that don't exist yet
   my-bmk-test.c      - Bloom maker test (optional, Task 2)
   string-duo.c1      - Bloom filter with mult-31 and lcg (Task 3)
   string-worst.c1    - Bloom filter that always return true (Task 4)

Files you will modify:
   string-test.c0     - Unit tests, performance test (Task 1)
   bloommaker.c1      - Bloom maker library (Task 2)
   meeting-lcgplus.c1 - Bloom filter for meetings (Task 4)
   bt-bit.c0          - Bool table library with bits representing true/false
   pw.c0              - Password checker (Task 7)
   test-pw.c0         - Test for the password checker (optional, Task 7)

==========================================================

Running your test cases against the various implementations:
   % cc0 -d -W -w -x bloom-worst.o0 string-test.c0
   % cc0 -d -W -w -x bloom-expensive.o0 string-test.c0

Testing your Bloom maker and your Bloom filters:
   % cc0 -d -W -w -x bt.o0 bloommaker.c1 my-bmk-test.c0
   % cc0 -d -W -w -x bt.o0 bloommaker.c1 string-duo.c1 string-test.c0
   % cc0 -d -W -w -x bt.o0 bloommaker.c1 string-worst.c1 string-test.c0
   % cc0 -d -W -w -x bt.o0 bloommaker.c1 meeting-lcgplus.c1 meeting-test.c0

Testing bt-bit.c0:
   % cc0 -d -W -w -x bt-bit.c0 bloommaker.c1 string-duo.c1 string-test.c0
   % cc0 -d -W -w -x bt-bit.c0 bloommaker.c1 string-worst.c1 string-test.c0
   % cc0 -d -W -w -x bt-bit.c0 bloommaker.c1 meeting-lcgplus.c1 meeting-test.c0

Testing your password checker
   % cc0 -d -W -w -x bt.o0 bloommaker.c1 string-duo.c1 pw.c0 test-pw.c0

==========================================================

Submitting to the unofficial test case checker from the command line on andrew:
   % autolab122 handin bloomtests string-test.c0
then display autolab's feedback by running:
   % autolab122 feedback bloomtests

Submitting officially from the command line on andrew:
   % autolab122 handin bloom string-test.c0 bloommaker.c1 string-duo.c1 string-worst.c1 meeting-lcgplus.c1 bt-bit.c0 pw.c0
then display autolab's feedback by running:
   % autolab122 feedback bloom

Creating a tarball to submit with autolab.andrew.cmu.edu web interface:
   % tar -czvf handin.tgz string-test.c0 bloommaker.c1 string-duo.c1 string-worst.c1 meeting-lcgplus.c1 bt-bit.c0 pw.c0
