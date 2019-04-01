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

	Source Code Files

(2) database.cpp
(3) database.h              <-- Source code for the database singleton class

(4) reader-writer-threads.cpp
(5) reader-writer-threads.h <-- Souce code for the reader & writer agents (threads)

(6) reader-writer.cpp       <-- Souce code for "main" (the program itself).

(7) stopwatch.h             <-- Source code for measuring elapsed time. 
                                Note that there is NO stopwatch.cpp file!


	Other Files

(9)	This file - "README";
(9) inputFile.txt           <-- Test Input (please make a backup copy!).


INSTALLATION and EXECUTION

Consider the following transcript (lines entered by the user start with $,
lines that do not start with $ are output from the shell).

(If you're unfamiliar with the commands time, head or tail, 
look them up with "man time", "man head" and "man tail").

).

---------------%< Begin Transcript %< ---------------
$ make
clang++ -c -g -std=c++11 -Wall -MMD -fmessage-length=0 -o database.o database.cpp
clang++ -c -g -std=c++11 -Wall -MMD -fmessage-length=0 -o reader-writer-threads.o reader-writer-threads.cpp
clang++ -c -g -std=c++11 -Wall -MMD -fmessage-length=0 -o reader-writer.o reader-writer.cpp
clang++ -o reader-writer database.o reader-writer-threads.o  reader-writer.o  -lpthread
touch outputFile.txt

$ ./reader-writer
Usage: ./reader-writer numSeconds numReaders numWriters

$ time ./reader-writer 1 1 1
In ./reader-writer, seconds = 1, writers = 1, readers = 1, ready to go...
Writer 0 starting...
Finished creating all threads...
Reader 0 starting...
READER 0 Finished test 1, result = 1, sleeping 0 seconds 
READER 0 Finished test 2, result = 1, sleeping 2 seconds 
WRITER 0 Finished test 1, result = 1, sleeping 1 seconds 
WRITER 0Finished. Returning after 1 tests.
READER 0Finished. Returning after 2 tests.
Database Statistics 
--------------------
 Readers: number of read operations  = 2
          average read time          = 0.000547214
 Writers: number of write operations = 1
          average write time         = 0.359043
Simulation finished! Database is OK!
./reader-writer 1 1 1  0.04s user 0.26s system 14% cpu 2.010 total

$ time ./reader-writer 10 4 4 >sampleOutput.txt
3.26s user 5.54s system 74% cpu 11.852 total

$ head -20 sampleOutput.txt 
Writer 0 starting...
Writer 1 starting...
Writer 2 starting...
Writer 3 starting...
Reader 0 starting...
Finished creating all threads...
Reader 1 starting...
READER 0 Finished test 1, result = 1, sleeping 1 seconds 
READER 1 Finished test 1, result = 1, sleeping 1 seconds 
Reader 3 starting...
READER 3 Finished test 1, result = 1, sleeping 0 seconds 
READER 3 Finished test 2, result = 1, sleeping 0 seconds 
READER 3 Finished test 3, result = 1, sleeping 2 seconds 
Reader 2 starting...
READER 2 Finished test 1, result = 1, sleeping 2 seconds 
READER 0: Problem - "SpardisOrtsparteigruppe/N" and "Ortsparteiobmann/EFSTs" are not correctly ordered!
READER 1: Problem - "SpardisOrtsparteigruppe/N" and "Ortsparteiobmann/EFSTs" are not correctly ordered!
READER 0: Problem - "Spiegelr�cPapachen/S" and "Papagallo/S" are not correctly ordered!
READER 1: Problem - "Spiegelr�cPapachen/S" and "Papagallo/S" are not correctly ordered!

$ tail -20 sampleOutput.txt 
READER 3: Problem - "Zeitungsindustrie/N" and "Z" are not correctly ordered!
READER 3 Finished test 11, result = 0, sleeping 0 seconds 
READER 3 Finished test 12, result = 0, sleeping 0 seconds 
READER 3 Finished test 13, result = 0, sleeping 2 seconds 
WRITER 0 Finished test 5, result = 0, sleeping 2 seconds 
WRITER 1Finished. Returning after 4 tests.
WRITER 2Finished. Returning after 6 tests.
READER 0Finished. Returning after 11 tests.
WRITER 3Finished. Returning after 5 tests.
READER 1Finished. Returning after 11 tests.
READER 2Finished. Returning after 10 tests.
READER 3Finished. Returning after 13 tests.
WRITER 0Finished. Returning after 5 tests.
Database Statistics 
--------------------
 Readers: number of read operations  = 33
          average read time          = 0.0324377
 Writers: number of write operations = 20
          average write time         = 0.69645
Simulation finished! Database is NOT OK!!!


--------------->% End Transcript >% ---------------

Now please try the commands yourself - you should get similar, but not identical
results. 

Also experiment with different values for numSeconds, numReaders and numWriters

CONCLUSION

The program has been tested for with the clang compiler, version 3.3, 
and with g++, version 4.8.2 on a 64 bit Linux.  

It might work with some other versions, but it needs a compiler that 
understands C++11 in any case.

Please do not hesitate to contact me if you have questions.

(Prof. Dr. Ronald Moore - FBI - H-DA.DE - <ronald.moore@h-da.de>)
