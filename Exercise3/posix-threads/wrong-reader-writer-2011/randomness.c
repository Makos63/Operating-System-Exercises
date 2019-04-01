#include <unistd.h> // voodoo
#include <stdlib.h> // for srandom() & random & RAND_MAX
#include <time.h>   // for time() 

#include "randomness.h"

// Initialize randomness
void setup_randoms( void ) {
	unsigned int seed = time( NULL );
	srandom( seed );
}

// Random float between 0.0 and 1.0 
float random_unit( ) {
	return( (float)random() / (float)RAND_MAX );
}

// Random int r so that 0 <= r < max
int random_int( int max ) {
	return ( random() % max );
}

// Random float r so that mix <= r <= max
inline float random_in_range( float min, float max ) {
	return (min + ((max-min) * random_unit() ) );
}

