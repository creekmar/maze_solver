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
QueueADT solve(void *start, void *config, void (*del)(void *a), QueueADT (*getNeigh) (void *b, void *c), bool (*isSolution) (const void *d, const void *e), bool (*equals) (const void *f, const void *g));


