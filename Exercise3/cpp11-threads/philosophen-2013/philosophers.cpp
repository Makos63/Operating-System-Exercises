#include <stdio.h>
#include <chrono>         // for std::chrono
#include <random>         // for std::default_random_engine etc.
#include <thread>         // for std::this_thread

#include "philosophers.h"

// This algorithm is from Tanenbaum's "Modern Operating Systems" 
// modified by Prof. Dr. Ronald Moore to work with C++11

// Four simple helper functions for readability
static philosopher::philosopherState getState( int i ) {
	return thinkers[i].state();
};
static void setStateOf( int i, philosopher::philosopherState newState ) {
	thinkers[i].setState( newState );
}

// Allocate Global array of Philosophers - and one global Mutex
philosopher thinkers[ philosopher::numPhilosophers ];
std::mutex 	philosopher::globalMutex; 

// Now define the methods for class philosopher

void philosopher::test( int i ) {      /* Let phil[i] eat, if waiting */
	if (     getState(     i      ) == HUNGRY 
          && getState( leftOf(i)  ) != EATING 
          && getState( rightOf(i) ) != EATING) {
		setStateOf( i, EATING );
        thinkers[ i ].ownMutex.unlock();  // release philosopher i
	}
}

void philosopher::sleep( ) {  
	// first we use C++11 to generate a random number between 1 and 1000
	// first set up
	static std::default_random_engine generator;
    static std::uniform_int_distribution<int> distribution( 1, 1000 );
    static auto randomNumber = std::bind ( distribution, generator );
	// then repeated usage (once per sleep)
	int timeToSleep = randomNumber();
	// conversion to milliseconds
	std::chrono::milliseconds randomMillisconds( timeToSleep );
	// finally get some sleep
	std::this_thread::sleep_for ( randomMillisconds ); 
}

void philosopher::take_forks( ) {
	globalMutex.lock();		        /* critical section */
	std::cout << "asking for forks " << id << " and " << rightOf(id) << std::endl;
	setState( HUNGRY );
	test( id );
	globalMutex.unlock();		            /* end critical section */
	myDelayTimer.startMeasuring(); 			// Measure average delay... 
	ownMutex.lock();	                    // Wait for own lock (i.e. for forks)
	myDelayTimer.takeMeasurement( ); 		// discard time measurement - keep average
	std::cout << "forks " << id << " and " << rightOf( id ) << " granted." << std::endl;	
}
 
void philosopher::put_forks( ) {

	globalMutex.lock();		/* critical section */
	std::cout << "dropping forks " << id << " and " << rightOf( id ) << std::endl;
    setState( THINKING );
	testLeftNeighbor( );		/* Let phil. on left eat if possible */
	testRightNeighbor( );		/* Let phil. on rght eat if possible */
	globalMutex.unlock();			/* end critical section */
}

// ****** Philosopher Thread Function
double philosopher::work( int numSeconds ) { 
	// CHANGE THE NEXT LINE to change simulation time!!
	std::chrono::seconds maxTime( numSeconds );  
	auto start_time = std::chrono::steady_clock::now();
	for ( auto end_time = std::chrono::steady_clock::now();
	     ( ( end_time - start_time ) < maxTime );
	     end_time = std::chrono::steady_clock::now() )
	{
		think( ); 
		take_forks( ); 
		eat( ); 
		put_forks( ); 
	}; // end for maxTime
	std::cout << "Philosopher " << id << " finished, average delay was " 
		      << myDelayTimer.averageMeasurement( ) << std::endl;
	return myDelayTimer.averageMeasurement( );
} 

