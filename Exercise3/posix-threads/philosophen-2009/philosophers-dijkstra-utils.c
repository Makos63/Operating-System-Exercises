#include <stdio.h>

#include "time-killer.h"
#include "philosophers-dijkstra-utils.h"


// internal utility, used only in this file

// wrapper for sem_wait that measures waiting time
int measured_sem_wait( sem_t *sem ) {
	double	startedWaiting = now();
	int	result = sem_wait( sem ); // call the REAL sem_wait
	measureWaitTime( startedWaiting );
	return result;
}

// ****** Philosopher Utilities
void think(int i){	
	printf("Philosopher %d starts thinking.\n", i);
	random_sleep(1.0);
	printf("Philosopher %d is hungry!\n", i);
}

void eat(int i){
	printf("Philosopher %d eating ...\n", i);
	random_sleep(1.0);
	printf("Philosopher %d asks \"Why Spaghetti?\"\n", i);
}

void test(int i) {            /* Let phil[i] eat, if waiting */
	if ( pflag[i]         == HUNGRY 
          && pflag[(i-1+N)%N] != EATING 
          && pflag[(i+1)%N]   != EATING) {
		pflag[i] = EATING;
		sem_post(&p[i]); // release philosopher i
	}
}

void take_forks(int i) {
	printf("asking for forks %d and %d\n", i, (i+1)%N);
	measured_sem_wait(&mtx);		/* critical section */
	pflag[i] = HUNGRY;
	test(i);
	sem_post(&mtx);		/* end critical section */
	measured_sem_wait(&p[i]);	/* Eat if enabled */
	printf("forks %d and %d granted\n", i, (i+1)%N );	
}
 
void put_forks(int i) {

	measured_sem_wait(&mtx);		/* critical section */

	printf("dropping forks %d and %d", 
			i, (i+1)%N );
	printWaitStatistics();
	
	pflag[i] = THINKING;
	test((i-1)%N);		/* Let phil. on left eat if possible */
	test((i+1)%N);		/* Let phil. on rght eat if possible */
	sem_post(&mtx);		/* end critical section */
}

// ****** Philosopher Thread Function
// The Signature (return type = paramater type = void*) 
// forced by POSIX Threads standard.
void *philosopher(void * threadId) { 

	long int i = (long int)threadId;
	
	while (1) { // for ever
		think(i); 
		take_forks(i); 
		eat(i); 
		put_forks(i); 
	} 
} 

