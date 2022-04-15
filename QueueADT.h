// File: QueueADT.h
//
// Description:  Interface to the QueueADT module
//
// Author:  CS@RIT.EDU
// Editor:  Ming Creekmore mec5765
//

#ifndef _QUEUEADT_H_
#define _QUEUEADT_H_

#include <stdbool.h>

// Define QueueADT type ONLY IF _not_ compiling the module implementation file.
//
// In the implementation file, define the QueueADT type as you need
// to for the implementation, and then define the symbol _QUEUE_IMPL_
// immediately before including this header file to prevent a
// redefinition of the type.
//

#ifndef _QUEUE_IMPL_

/// QueueADT is a pointer to an abstract queue data structure whose
/// payload data type is 'generic', implemented as void * in this interface.

typedef struct stackStruct * QueueADT;

#endif

/// Create a QueueADT that uses the supplied function as a comparison
/// routine.
///
/// The comparison function takes two void * parameters, and returns
/// an integer result that indicates the relationship between the
/// two things:
///
///	Result	Relationship
///	======	===========
///	 < 0	a < b
///	 = 0	a == b
///	 > 0	a > b
///
/// where ">" and "<" are dependent upon the data being compared
///
/// @param cmp the address of the comparison function to be used for
///    ordering this queue, or NULL if standard FIFO behavior is desired
/// @param del the address of the delete function used to free specific data
///    added to the queue, this is for allocated memory
/// @param equals the address of the equals function used to determine whether
///    two data items are equal
/// @return a QueueADT instance, or NULL if the allocation fails

QueueADT que_create( int (*cmp)(const void * a, const void * b), void (*del)(void* c), bool (*equals)(const void * d, const void * e) );


/// Determines whether a specific data is within the queue
/// 
/// @param queue - the QueueADT to search in
/// @param data - the data value to look for
/// @return - the index that the data is at, otherwise -1 if not in the lise
/// @exception If the data or queue is null then assert() will fail

int que_contains( QueueADT queue, void * data );


/// Tear down and deallocate the supplied QueuADT.
///
/// @param queue - the QueueADT to be manipulated

void que_destroy( QueueADT queue );


/// Remove all contents from the supplied QueueADT.
///
/// @param queue - the QueueADT to be manipuated

void que_clear( QueueADT queue );


/// Insert the specified data into the Queue in the appropriate place
///
/// Uses the queue's comparison function to determine the appropriate
/// place for the insertion.
///
/// @param queue the QueueADT into which the value is to be inserted
/// @param data the data to be inserted
/// @exception If the value cannot be inserted into the queue for
///     whatever reason (usually implementation-dependent), the program
///     should terminate with an error message.  This can be done by
///     printing an appropriate message to the standard error output and
///     then exiting with EXIT_FAILURE, or by having an assert() fail.

void que_insert( QueueADT queue, void * data );


/// Remove and return the first element from the QueueADT.
///
/// @param queue the QueueADT to be manipulated
/// @return the value that was removed from the queue
/// @exception If the queue is empty, the program should terminate
///     with an error message.  This can be done by printing an
///     appropriate message to the standard error output and then
///     exiting with EXIT_FAILURE, or by having an assert() fail.
/// Note: if returned value from queue was allocated on the heap, it must be 
///     freed by the client
void * que_remove( QueueADT queue );


/// Indicate whether or not the supplied Queue is empty
///
/// @param the QueueADT to be tested
/// @return true if the queue is empty, otherwise false

bool que_empty( QueueADT queue );


#endif

