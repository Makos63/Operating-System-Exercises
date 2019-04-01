#ifndef _READER_WRITER_UTILS_H_
#define _READER_WRITER_UTILS_H_

// ******** global variables ******** 

// was reading always successful?
extern int everything_ok;

// number of seconds run time
extern int numSeconds;

// number of reader threads
extern int numReaders;

// number of writer threads
extern int numWriters;


// ******** functions ********

// The database writer
void writeToDatabase(  long int writerID );

// The database reader
void readFromDatabase( long int readerID );

// The writer thread
// Return value: NULL. Always.
void *writer( void *writerID );

// The reader thread
// Return value: NULL. Always.
void *reader( void *readerID );

#endif // ifndef _READER_WRITER_UTILS_H_

