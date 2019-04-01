#include <sys/time.h>	// for usleep(), gettimeofday()...
#include <assert.h> 	// for assert()
#include <unistd.h>	// for usleep()
#include <stdlib.h>	// for abs()

#include <stdio.h>		// only for debug printf...

#include "time-killer.h"

#include "randomness.h"

/*********************************************************
 * Internal Utility Functions
 *********************************************************/

// see definitions in time-killer.h
const int microsPerSec =  1000000;

struct timeval double2timeval( double time )
{
	assert( 0.0 <= time );
	struct timeval result;
	result.tv_sec = (int)time;
	assert( 0 <= result.tv_sec );
	assert( result.tv_sec <= time );
	assert( (time -1) < result.tv_sec );
	
	double remainder = ( time - result.tv_sec );
	result.tv_usec = microsPerSec * remainder;
	assert( 0 <= result.tv_usec );
	assert( result.tv_usec < microsPerSec );
	
	return result;
}

double timeval2double( struct timeval time )
{
	assert( 0 <= time.tv_sec );
	assert( 0 <= time.tv_usec );
	assert( time.tv_usec < microsPerSec );
	double	vorKomma = (double)time.tv_sec;
	double	nachKomma = (double)time.tv_usec / (double)microsPerSec;
	assert( 0.0 <= vorKomma );
	assert( 0.0 <= nachKomma );
	assert( nachKomma < 1.0 );
	double  result = vorKomma + nachKomma;
	return result;
}

// statistics 
static double	totalTimeWaiting = 0.0;
static int		numberWaits = 0;
static double longestWait = 0.0;
static double shortestWait = 60.0 * 60.0 * 24;

/*********************************************************
 * Export Functions - random_sleep and now()
 *********************************************************/

void random_sleep( double max_time ) {
	assert( 0.0 <= max_time ); // no time travel, please
	assert( max_time <= 60 ); // don't try my patience
	double time_to_sleep = random_in_range( 0.0, max_time );
	int usecs2sleep = time_to_sleep * microsPerSec;		
	usleep( usecs2sleep );
} // end random_sleep() 
 
double now( ) {
	struct timeval rightNow;
	int status = gettimeofday( &rightNow, NULL );
	assert( 0 == status );
	assert( 0 < rightNow.tv_sec );
	assert( 0 <= rightNow.tv_usec );
	assert( rightNow.tv_usec < microsPerSec );
	double result = timeval2double( rightNow );
	assert( 0.0 < result );
	assert( rightNow.tv_sec <= result );
	return result;
} // end now()

double time_since( double before ) {
	return( now( ) - before );
}

double averageWaitTime( ) {
	if ( 0 == numberWaits )
		return 0.0;
	else {  // if 0 != numberWaits
		assert( 0 < numberWaits );
		assert( 0.0 <= totalTimeWaiting );
		return totalTimeWaiting / (double)numberWaits;
	} // end if 0 != numberWaits
}

void measureWaitTime( double startedWaiting ) {
	double waitTime = time_since( startedWaiting );
	
	// update avg
	totalTimeWaiting += waitTime;
	++numberWaits;
	
	// update min und max
	longestWait   = ( longestWait < waitTime  ) ? waitTime : longestWait ;
	shortestWait  = ( waitTime < shortestWait ) ? waitTime : shortestWait ;
}

void printWaitStatistics( ) {
	printf(" Wait Statistics: avg %f, min %f, max %f (%d measurements)\n",
			averageWaitTime(), shortestWait, longestWait, numberWaits );
}