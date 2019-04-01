#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include "reader-writer-utils.h"

#include "randomness.h"
#include "time-killer.h"

// ******** global variables ******** 

// was reading always successful?
int everything_ok = 1;  // == TRUE

// number of seconds
int numSeconds = 0;

// number of reader threads
int numReaders = 0;

// number of writer threads
int numWriters = 0;// ******** local constants (shared by reader & writer) ******** 

const char	inputFileName[]  = "inputFile.txt";
const char outputFileName[] = "outputFile.txt";

// ******** reader & writer threads ******** 

// The database writer
void writeToDatabase(  long int writerID ) {
	const int lineLength 		= 128;
	const int maxLines2skip	= 450000;
	const int maxLines2copy	= 100000;
	
	char	line[ lineLength ];
	
	// open both files
	FILE 	*inputfd = fopen( inputFileName, "r" );
	if (NULL == inputfd) {
		printf("Writer %ld could not open input file!\n", writerID );
		exit( 2 );
	}
	FILE 	*outputfd = fopen( outputFileName, "w" );
	if (NULL == outputfd) {
		printf("Writer %ld could not open output file!\n", writerID );
		exit( 3 );
	}

	// skip a random number of lines
	int		lines2skip = random_int( maxLines2skip );
	assert( 0 <= lines2skip );
	assert( lines2skip <= maxLines2skip );
	
	int i;
	for( i = 0; i < lines2skip; ++i )
		fgets( line, lineLength, inputfd );

	// copy a fixed number of lines from input to output
	for( i = 0; i < maxLines2copy; ++i )
	{
		assert( !feof( inputfd ) );
		fgets( line, lineLength, inputfd );
		fputs( line, outputfd );
	} // end for 0 <= i < maxLines2copy
	
	fclose( inputfd );
	fclose( outputfd );
		
} // end writeToDatabase

// The database reader
void readFromDatabase( long int readerID ) {
	const int lineLength 		= 128;
	char	oldLine[ lineLength ];
	char	newLine[ lineLength ];

	// open the output file - for reading!
	FILE 	*outputfd = fopen( outputFileName, "r" );
	if (NULL == outputfd) {
		printf("Reader %ld could not open output file!\n", readerID );
		exit( 4 );
	}

	// read the first line...
	assert( !feof( outputfd ) );
	fgets( oldLine, lineLength, outputfd );

	// read all the other lines, checking the order
	while( !feof( outputfd ) )
	{
		// read one line
		fgets( newLine, lineLength, outputfd );

		// compare the new line to the last line 
		int	comparison = strcmp( oldLine, newLine );
		if ( 0 < comparison ) {
			printf("READER %ld: Problem - %s and %s not ordered!\n",
					readerID, oldLine, newLine );
			everything_ok = 0; // d.h. FALSE
		} // end if not OK
		
		// oldLine <- newLine
		strncpy( oldLine, newLine, lineLength ); 
	} // end while not eof( input ) 
	
	fclose( outputfd );
		
} // end readFromDatabase

// The writer thread
void *writer( void *writerID ) {
	long int	myID = (long int)writerID;

	printf("Writer %ld starting...\n", myID );

	long int	test = 0;
	double startTime = now();
	while ( time_since( startTime ) < numSeconds ) {
		
		writeToDatabase( myID );
		++test;
		int numSeconds2sleep = random_int( 3 ); // i.e. either 0, 1 or 2 
		
		printf("WRITER %ld: Finished test %ld, sleeping %d seconds.\n",
				myID, test, numSeconds2sleep );		
		if ( numSeconds2sleep ) sleep( numSeconds2sleep );
	} // repeat until time used is longer than numSeconds
	
	// return number of tests
	printf("WRITER %ld: Finished. Returning %ld tests.\n", myID, test );
	return (void *)test;

} // end writer function

// The reader thread
void *reader( void *readerID ) {
	long int	myID = (long int)readerID;
	
	printf("Reader %ld starting ...\n", myID );
	
	long int	test=0;
	double startTime = now( );
	while ( time_since( startTime ) < numSeconds ) {

		readFromDatabase( myID );
		++test;
		int numSeconds2sleep = random_int( 3 ); // i.e. either 0, 1 or 2 
		printf("READER %ld: Finished test %ld, sleeping %d seconds.\n",
				myID, test, numSeconds2sleep  );
		if ( numSeconds2sleep ) sleep( numSeconds2sleep );
	} // repeat until time used is longer than numSeconds

	// return number of tests
	printf("READER %ld: Finished. Returning %ld tests.\n", myID, test );
	return (void *)test;

} // end reader function

