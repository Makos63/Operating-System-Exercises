#include <iostream>			// for std::cin, cerr, cout ...
#include <thread>			// for std::this_thread
#include <chrono>			// for std::chrono... 

#include "database.h"
#include "reader-writer-threads.h"


// ******** reader & writer threads ******** 

// The writer thread
void writer( int writerID, int numSeconds ) {

	std::cout << "Writer " << writerID << " starting..." << std::endl;

	int	tests = 0; 
	auto startTime = std::chrono::steady_clock::now();
	std::chrono::seconds maxTime( numSeconds ); 
	while ( ( std::chrono::steady_clock::now() - startTime ) < maxTime ) {
		
		bool result = theDatabase.write( writerID );
		++tests;

		// sleep a while...
		int numSeconds2sleep = randomInt( 3 ); // i.e. either 0, 1 or 2 
		std::chrono::seconds randomSeconds( numSeconds2sleep );
		std::cout << "WRITER " << writerID 
			      << " Finished test " << tests
			      << ", result = " << result
			      << ", sleeping " << numSeconds2sleep
			      << " seconds " << std::endl;
		if ( numSeconds2sleep ) std::this_thread::sleep_for ( randomSeconds ); 
		
	} // repeat until time used is up
	
	std::cout << "WRITER " << writerID 
		      << "Finished. Returning after " << tests 
		      << " tests." << std::endl;

} // end writer function

// The reader thread
void reader( int readerID, int numSeconds ) {
	
	std::cout << "Reader " << readerID << " starting..." << std::endl;
	
	int	tests=0;
	auto startTime = std::chrono::steady_clock::now();
	std::chrono::seconds maxTime( numSeconds ); 
	while ( ( std::chrono::steady_clock::now() - startTime ) < maxTime ) {

		bool result = theDatabase.read( readerID );
		++tests;

		// sleep a while...
		int numSeconds2sleep = randomInt( 3 ); // i.e. either 0, 1 or 2 
		std::chrono::seconds randomSeconds( numSeconds2sleep );
		std::cout << "READER " << readerID 
			      << " Finished test " << tests
			      << ", result = " << result
			      << ", sleeping " << numSeconds2sleep
			      << " seconds " << std::endl;
		if ( numSeconds2sleep ) std::this_thread::sleep_for ( randomSeconds ); 

	} // repeat until time is used up
	
	std::cout << "READER " << readerID 
		      << "Finished. Returning after " << tests 
		      << " tests." << std::endl;

} // end reader function

