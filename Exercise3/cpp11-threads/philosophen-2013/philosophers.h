#pragma once 

// This algorithm is from Tanenbaum's "Modern Operating Systems" 
// modified by Prof. Dr. Ronald Moore to work with C++11

#include <iostream>       // for std::cin, cout, cerr...
#include <cassert>        // for assert
#include <mutex>          // for std::mutex

#include "stopwatch.h" 	   // for time measurements

// Global variables, constants and enums

// ****** Philosopher Utilities
class philosopher { // note that this inherits nothing, extends nothing - nice and simple!
	
public: // Prelinaries - Constants, embedded types, etc.

	// Philosopher type
	typedef enum { THINKING	= 0,
		            HUNGRY 		= 1,
	    	        EATING 		= 2 } philosopherState;

	// Important constant - number of philoosphers = ring (wraps around)!!!
	static const int numPhilosophers = 5;
	static int rightOf( int i ) { return ((i+1) % numPhilosophers); };
	static int leftOf( int i ) { return ((i+numPhilosophers-1) % numPhilosophers); };
	int rightNeighbor( ) { return rightOf( id ); };
	int leftNeighbor( )  { return leftOf( id ); };

private : // philosopher's data
	philosopherState myState;
	int				 id;
	stopwatch		 myDelayTimer;

public: // philosopher's methods
		
	// Constructor
	philosopher(  ) 
		: myState( THINKING ) {
		static int numberOfPhilosophers = 0; 
		id = numberOfPhilosophers++;
		assert( 0 <= id );
		assert( id < numPhilosophers );
		ownMutex.lock(); // every philosopher starts out being blocked
	};

	// Getters and setters - 
	void 				setState( philosopherState newState ) { myState = newState; };
	philosopherState 	state( ) const { return myState; }
	stopwatch&			delayTimer( ) { return myDelayTimer; }

	// Philosophy Methods
	void sleep( );
	
    void think( ) {
		std::cout << "Philosopher " << id << " starts thinking." << std::endl;
		sleep();
		std::cout << "Philosopher " << id << " is hungry!" << std::endl;
	}; // end think
	
    void eat( ) {
		std::cout << "Philosopher " << id << " starts eating..." << std::endl;
		sleep();
		std::cout << "Philosopher " << id << " asks \"Why Spaghetti?\"." << std::endl;
	}; // end eat

	// Philosopher Thread Function: work = think and eat for numSeconds;
	// Return value is the average waiting time in seconds (as double)
	double work(  int numSeconds );

	// Synchronization methods - Note staticness!
	void take_forks( );
	void put_forks( );
	static void test( int i );

	// Helper-functions (just for readability)...
	void testLeftNeighbor( ) 	{ test( leftNeighbor() ); };
	void testRightNeighbor( )	{ test( rightNeighbor() ); };

	// We use the following mutexes - note that these are public!!!
    std::mutex 			ownMutex;    // one mutex, per philosopher 
	static std::mutex 	globalMutex; // mutual exclusion for everybody,
	                                 // initially unlocked.

}; // end philospher class

// Global array of Philosophers
extern philosopher thinkers[ philosopher::numPhilosophers ];

