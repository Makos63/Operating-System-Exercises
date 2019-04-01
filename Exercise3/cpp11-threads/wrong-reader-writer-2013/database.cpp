#include <fstream>			// for std::ifstream and ofstream
#include <iostream>			// for std::cerr, cout... 
#include <random>           // for std::default_random_engine etc.
#include <cassert>			// for assert
#include <string>			// for std::string

#include "database.h"

// ******** database class ********

// Static (global) variables & constants

int database::numberDatabases = 0;
const std::string database::inputFileName( "inputFile.txt" );
const std::string database::outputFileName( "outputFile.txt" );

database theDatabase;  

int randomInt( int maxRandomInt ) {
	static std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution( 0, maxRandomInt-1 );
	int result = distribution( generator );
	assert( 0 <= result );
	assert( result < maxRandomInt );
    return result;
} // end randomInt

// Methods

bool database::write(  int writerID ) {

	writerClock.startMeasuring();
	
	// open both files
	std::ifstream inputStream( inputFileName );
	if ( ! inputStream.good() ) {
		std::cerr << "Writer " << writerID 
		          << " could not open input file (filename = " << inputFileName
		          << ")!" << std::endl;
		return ( everything_ok = false );
	};
	std::ofstream outputStream( outputFileName );
	if ( ! outputStream.good() ) {
		std::cerr << "Writer " << writerID 
		          << " could not open output file (filename = " << outputFileName
		          << ")!" << std::endl;
		return ( everything_ok = false );
	};

	// Termporary memory...
	std::string line; 

	// skip a random number of lines
	const int maxLines2skip	= 450000;
	int		lines2skip = randomInt( maxLines2skip );
	for( int i = 0; i < lines2skip; ++i )
		if ( !( inputStream >> line ) ) {
			std::cerr << "Writer " << writerID 
				      << " cannot skip line " << i 
				      << " of " << lines2skip << std::endl;
		return ( everything_ok = false );
		}; // end if input not OK
	// end for 0 <= i < lines2skip

	// copy a fixed number of lines from input to output
	const int maxLines2copy	= 100000;
	for( int i = 0; i < maxLines2copy; ++i )
	{
		if ( ! ( inputStream >> line ) )  {
			std::cerr << "Writer " << writerID 
				      << " cannot read line " << i 
				      << " of " << maxLines2copy << std::endl;
		    return ( everything_ok = false );
		} else  if ( ! ( outputStream << line << std::endl ) ) {	
			std::cerr << "Writer " << writerID 
				      << " cannot write line " << i 
				      << " of " << maxLines2copy << std::endl;
		    return ( everything_ok = false );
		};
	} // end for 0 <= i < maxLines2copy

	writerClock.takeMeasurement();
	// if we're here, everything was OK (unless it wasn't to begin with)
	return( everything_ok ); 

} // end write method

// The database reader
bool database::read( int readerID ) {

	readerClock.startMeasuring();

	// open the output file - for reading!
	std::ifstream inputStream( outputFileName ); // Not a mistake! 
	
	if ( ! inputStream.good() ) {
		std::cerr << "Reader " << readerID 
		          << " could not open input file (filename = " << outputFileName
		          << ")!" << std::endl;
		return ( everything_ok = false );
	};

	std::string oldLine;
	std::string newLine;

	if ( ! (inputStream >> oldLine) ) {  // read 1st line outside of loop...  
		// File is empty? Then no writer has written - that's OK!
		return ( everything_ok);
	};

	// read all the other lines, checking the order
	while( inputStream >> newLine ) {
		// compare the new line to the old line, see if they're in alphabetical order
		if ( newLine <= oldLine  ) {
			std::cout << "READER " << readerID
				      << ": Problem - \"" << oldLine 
				      << "\" and \"" << newLine 
				      << "\" are not correctly ordered!" << std::endl;
		    everything_ok = false;
		} // end if not OK
		
		oldLine = newLine;
	} // end while not eof( input ) 

	readerClock.takeMeasurement();
	return ( everything_ok );
} // end readFromDatabase

void database::printStatistics( ) const { // output reader and writer times
	std::cout << "Database Statistics " << std::endl
		      << "--------------------" << std::endl
		      << " Readers: number of read operations  = " 
		      << readerClock.count() << std::endl
		      << "          average read time          = " 
		      << readerClock.averageMeasurement() << std::endl
		      << " Writers: number of write operations = " 
		      << writerClock.count() << std::endl
		      << "          average write time         = " 
		      << writerClock.averageMeasurement() << std::endl;
} // end printStatistics

