//
// File: solver.h is an interface for functions that will find
// the quickest solution to a map if there is one
//
// @author Ming Creekmore mec5765
//
// @date 4/14/2022
//
// // // // // // // // // // // // // // // // // // // // // // //

#ifndef _SOLVER_H_
#define _SOLVER_H_

#include "QueueADT.h"

/// construct_path constructs the shortest path to the solution given
/// a hashmap, start and end value, as well as the function that
/// gets the previous value of a data in a queue
/// Also deallocates the hashmap after removing the values that 
/// pertain to the path
///
/// @param hashmap all of the possible pathways given from first part of BFS
/// @param start the start data point of the path
/// @param end the end data point of the path
/// @param prev pointer to function that the data point previous to the
///     current data point (example: backtracking your path)
/// @return a queue of the path in correct order
QueueADT construct_path(QueueADT hashmap, void *start, void *end, void* (*prev) (void*));

/// solve solves a puzzle for the shortest solution using BFS
///
/// @param start the start data point of the path
/// @param config the puzzle to solve
/// @param del pointer to the function to delete a data point
/// @param getNeigh pointer to the function to get possible next configs
///     from current config
/// @param isSolution pointer to the function that determines if a data 
///     is the correct solution
/// @param equals pointer to the function that determines if two data points
///     are equivalent to each other
/// @param prev pointer to the function that gets the previous data point based
///     on the current data point (ex. backtracking your path)
/// @return a queue of all the steps in the solution
QueueADT solve(void *start, void *config, void (*del)(void *a), QueueADT (*getNeigh) (void *b, void *c), bool (*isSolution) (const void *d, const void *e), bool (*equals) (const void *f, const void *g), void* (*prev) (void*));



