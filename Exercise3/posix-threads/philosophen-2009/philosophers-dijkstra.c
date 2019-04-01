#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "randomness.h"
#include "philosophers-dijkstra-utils.h"

/********************************************* * main entry point *********************************************/
int main(int argc, char *argv[]) {
	pthread_t thread[N];
	long int t, j, ret;
	long int status;

	setup_randoms(); // see random.h

	// initialize all semaphores
	sem_init(&mtx, 0, 1);
	for (j=0; j<N; j++) {
		pflag[j] = THINKING;
		sem_init(&(p[j]), 0, 0);
	}

	for (t=0; t<N; t++) {
		//printf("Creating thread %d\n", t);
		ret = pthread_create( &thread[t], NULL, philosopher, (void *)t);

		if (ret) {
			printf("ERROR; return code from pthread_create() is %ld\n", ret);
			exit(-1);
		}
	}

	// Wait for all threads
	for (t=0; t<N; t++) {
		ret = pthread_join(thread[t], (void **)&status);

		if (ret) {
			printf("ERROR return code from pthread_join() is %ld\n", ret);
			exit(-1);
		}
		printf("Completed join with thread %ld status= %ld\n", t, status);
	}

	pthread_exit(NULL);

}

