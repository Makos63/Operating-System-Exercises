#ifndef __TIME_KILLER_H__
#define __TIME_KILLER_H__

// Sleep for a random time not greater than max_time seconds.
void random_sleep( double max_time );

// the current time, as a floating point number 
// to be used for measuring durations.
// Not suitable for other purposes. 
double now( ); 

// The duration between now() and another call to now()
double time_since( double time1 ) ;

// The average time spent waiting.
// Presumes the use of measureWaitTime (see below)
double averageWaitTime( );

// measure and record time spent waiting 
// - for use later with averageWaitTime (see above)
// Input: startingWaiting = return value of now() before waiting
//        began.   now() will be called again and the difference
//        take (with time_since() - see above).
void measureWaitTime( double startedWaiting );

// output the statistics about waiting
void printWaitStatistics( );

#endif 

