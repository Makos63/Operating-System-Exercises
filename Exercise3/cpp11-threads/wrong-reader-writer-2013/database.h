#pragma once

#include <string>		// for std::string
#include <iostream>		// for std::cerr
#include <cstdlib>		// for exit()

#include "stopwatch.h"  // for the stopwatch class

class database {

private:
		
	static int numberDatabases;
	bool   everything_ok; 

	stopwatch	readerClock;
	stopwatch	writerClock;
	
	// Static constants
	static const std::string inputFileName;
	static const std::string outputFileName;

public:	

	// constructor
	database( ) 
	: everything_ok( true ) // until something goes wrong...
   {
		if ( 0 < numberDatabases ) {	// Singleton check
			std::cerr << "There can only be one database!!!" << std::endl;
			exit( 1 );
		};
	} // end constructor 

	// Key Methods
	bool write(  int writerID ); // returns true iff operation ok
	bool read(   int readerID ); // returns true iff operation ok

	bool ok( ) const { return everything_ok; }

	void printStatistics( ) const; // output reader and writer times
	
}; // end class database

extern database	 theDatabase;

int randomInt( int maxRandomInt ); // returns 0 <= randomInt < maxRandomInt
