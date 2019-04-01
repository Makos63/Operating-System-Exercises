#ifndef RANDOMNESS_H_
#define RANDOMNESS_H_


// Initialize randomness
void setup_randoms( void ); 

// Random float between 0.0 and 1.0 
float random_unit( );

// Random int r so that 0 <= r < max
int random_int( int max ) ;

// Random float r so that mix <= r <= max
float random_in_range( float min, float max );


#endif /*RANDOMNESS_H_*/
