/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * philosophers-dijkstra.cpp
 * Based on an example from Dijkstra's "Modern Operating Systems",
 * converted from C & POSIX threads to C++11 threads by 
 * Prof. Dr. R. C. Moore <ronald.moore@h-da.de>
 *
 */

#include <future>		// for std::future
#include "philosophers.h"


/********************************************* * main entry point *********************************************/
int main(int argc, char *argv[]) {

	if ( 2 != argc ) {
		std::cerr << "Usage: " << argv[0] << " numberOfSecondsToRun." << std::endl;
		return( 1 );
	};
	// else if 2 == argc
	int numSeconds = std::stoi( std::string( argv[1] ) );

	
	if ( (numSeconds <= 0 ) || ( (60*60*24) < numSeconds ) ) {
		std::cerr << "Usage: " << argv[0] << " numberOfSecondsToRun." << std::endl;
		std::cerr << "where 0 < numberOfSecondsToRun <= 1 day." << std::endl;
		return( 2 );
	};
	// else if 0 < numberOfSecondsToRun <= 1 day 
	std::cout << "Simulation will run for approximately " << numSeconds 
		      << " seconds." << std::endl;

	// We use std::future instead of std::thread, since philosopher::work
	// has a return value (of type double).
    std::future<double>  	futures[ philosopher::numPhilosophers ]; // no threads yet!

	// start philophers working...
	int i = 0;
	for ( philosopher& p : thinkers ) { // new C++11 "range-for"!!
		// Calling an object's method is a little tricky... 
		// Using a closure (i.e. lambda expression, anonymous function) makes
		// it easy...   
        futures[i++] = std::async( std::launch::async, // start NOW!
                                   [&p, numSeconds] { 
									   return p.work(numSeconds); 
								    } ); 
	};
    assert( philosopher::numPhilosophers == i );
	
	// wait for philosophers to stop working...
	double totalDelays = 0.0;
	for ( std::future<double>& fut : futures ) {
		totalDelays += fut.get(); // get return value, wait as long as necessary
	}; 

	std::cout << philosopher::numPhilosophers 
		      << " philosophers are finished, average delay was " 
			  << totalDelays / philosopher::numPhilosophers  
		      << " seconds." << std::endl;
	// we're done!
	return ( 0 );

}

