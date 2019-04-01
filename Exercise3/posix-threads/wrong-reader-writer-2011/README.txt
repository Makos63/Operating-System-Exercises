INTRODUCTION AND WARNING

This package contains a program which is intentionally WRONG!!

This illustrates an INCORRECT (but multithreaded) "solution" to 
the Reader/Writer Problem.  No semaphores are used, so the writers 
create problems which the readers detect.

This is part of the Betriebssystem Praktikum at the 
Darmstadt University of Applied Sciences.
 
CONTENTS

You should have received the following files:

(1)	Makefile				<-- A Makefile, with comments in German (mostly).

	Header Files

(2) randomness.h
(3)	reader-writer-utils.h
(4) time-killer.h

	Source Code Files

(5)	randomness.c            <-- source code for random numbers
(6)	reader-writer-utils.c   <-- source code for reader & writer threads
                                & database read & write utilities
(7)	reader-writer.c         <-- includes main()

(8) time-killer.c           <-- source code for measuring time


	Other Files

(9)	This file - "README";
(10) inputFile.txt            <-- Test Input (consider making a backup copy).


INSTALLATION and EXECUTION

Consider the following transcript (lines entered by the user start with $,
lines that do not start with $ are output from the shell):
(Try the commands yourself - you should get similar, but not identical
results).

---------------%< Begin Transcript %< ---------------
$ make clean
$ make
cc    -c -o randomness.o randomness.c
cc    -c -o reader-writer.o reader-writer.c
cc    -c -o reader-writer-utils.o reader-writer-utils.c
cc    -c -o time-killer.o time-killer.c
gcc -o reader-writer randomness.o reader-writer.o reader-writer-utils.o time-killer.o -lpthread
$ ./reader-writer
Usage: ./reader-writer numSeconds numReaders numWriters
$ ./reader-writer 1 1 1
In ./reader-writer, seconds = 1, writers = 1, readers = 1, ready to go...
Writer 0 starting...
Finished creating all threads...
Reader 0 starting 0...
READER 0: Finished test 1, sleeping 2 seconds.
WRITER 0: Finished test 1, sleeping 1 seconds.
WRITER 0: Finished. Returning 1 tests.
READER 0: Finished. Returning 1 tests.
Final Result from ./reader-writer: 1 read events, 1 write events...
Final Status - Everything OK.
$ time ./reader-writer 10 10 10 >sampleOutput.txt

real	0m12.100s
user	0m6.300s
sys	0m0.787s
$ head sampleOutput.txt 
In ./reader-writer, seconds = 10, writers = 10, readers = 10, ready to go...
Writer 0 starting...
Finished creating all threads...
Writer 9 starting...
Reader 0 starting 0...
READER 0: Finished test 1, sleeping 0 seconds.
READER 0: Finished test 2, sleeping 0 seconds.
READER 0: Finished test 3, sleeping 2 seconds.
Reader 1 starting 1...
READER 1: Finished test 1, sleeping 2 seconds.
$ tail sampleOutput.txt 
READER 1: Finished. Returning 8 tests.
WRITER 3: Finished. Returning 10 tests.
READER 0: Finished. Returning 11 tests.
READER 7: Finished. Returning 13 tests.
READER 8: Finished. Returning 9 tests.
WRITER 7: Finished. Returning 10 tests.
WRITER 9: Finished. Returning 14 tests.
WRITER 1: Finished. Returning 8 tests.
Final Result from ./reader-writer: 103 read events, 88 write events...
Final Status - Everything NOT OK!
--------------->% End Transcript >% ---------------

(If you're unfamiliar with the commands time, head or tail, 
look them up with "man time", "man head" and "man tail").

CONCLUSION

Please do not hesitate to contact me if you have questions.

(Prof. Dr. Ronald Moore - FBI - H-DA.DE)
