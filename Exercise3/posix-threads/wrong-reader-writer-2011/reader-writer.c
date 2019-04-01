#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <assert.h>

#include "randomness.h"
#include "reader-writer-utils.h"

const int maxThreads = 1024;

/********************************************* * main entry point *********************************************/ 
int main(int argc, char *argv[])
{
	
    setup_randoms(); // see random.h
    
    if ( argc != 4 ) {
    	printf("Usage: %s numSeconds numReaders numWriters\n", argv[0] );
    	exit( 1 );
    }
    
    numSeconds = atoi( argv[1] );
    assert( (0 < numSeconds) && (numSeconds < (60*60*24)) ); // max 1 day
    numReaders = atoi( argv[2] );
    assert( (0 <= numReaders) && (numReaders < maxThreads) );
    numWriters = atoi( argv[3] );
    assert( (0 <= numWriters) && (numWriters < maxThreads) );
    
	pthread_t rThread[ numReaders ];
	pthread_t wThread[ numWriters ];
    long int r, w, numTests;
    
    printf("In %s, seconds = %d, writers = %d, readers = %d, ready to go...\n",
    		argv[0], numSeconds, numWriters, numReaders );
    
    // create writer threads
	for ( w = 0; w < numWriters; w++) {
		// printf("Creating writer thread %ld\n", w );
		long int ret = pthread_create( &wThread[w], NULL, writer, (void *)w );
		if (ret) {
			printf("ERROR; return code from pthread_create() is %ld\n", ret);
			exit(-1);
		}
	};

	// create reader threads
	for ( r = 0; r < numReaders; r++) {
		// printf("Creating reader thread %d\n", r );
		long int ret = pthread_create( &rThread[r], NULL, reader, (void *)r );
		if (ret) {
			printf("ERROR; return code from pthread_create() is %ld\n", ret);
			exit(-1);
		}
	};
	printf( "Finished creating all threads...\n" );

	// number of read events
	long int numReads = 0;

	// number of writer events
	long int numWrites = 0;


	// Wait for all reader threads
	for ( r = 0; r < numReaders; r++) {
		long int ret = pthread_join(rThread[r], (void **)&numTests );
		if (ret) {
			printf("ERROR return code from pthread_join( reader %ld ) is %ld\n", 
					r, ret);
			exit(-1);
		}
		numReads += numTests;
	};
	// printf( "Finished waiting for finished readers...\n" );

	// Wait for all writer threads
	for ( w = 0; w < numWriters; w++) {
		long int ret = pthread_join(wThread[w], (void **)&numTests);
		if (ret) {
			printf("ERROR return code from pthread_join( writer %ld ) is %ld\n", 
					w, ret);
			exit(-1);
		}
		numWrites += numTests;
	}

    printf( "Final Result from %s: %ld read events, %ld write events.\n", 
    		argv[0], numReads, numWrites );
    printf( "Final Status - Everything %s\n", 
    		( everything_ok ? "OK." : "NOT OK!" ) );
    		
    return( 0 );
}

