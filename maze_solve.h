//
// File: maze_solve.h an interface for functions that determine solutions to a maze
//
// @author Ming Creekmore mec5765
//
// @date 4/15/2022
//
// // // // // // // // // // // // // // // // // // // // // // // // // // //

#ifndef _MAZE_SOLVE_H_
#define _MAZE_SOLVE_H_

#ifndef _MAZE_DATA_
#define _MAZE_DATA_
typedef struct m *maze_data;
#endif

#include <stdbool.h>
#include "QueueADT.h"
#include "coor.h"

/// is_solution checks if a coordinate is the end of the maze
/// 
/// @param config the maze to check
/// @param current the coordinate to check
/// @return 1 if solution, 0 if not solution
bool is_solution(const void *config, const void *current);

/// find_solution finds the shortest solution to the maze if there is one
/// and marks it on the maze and returns the number of steps
///
/// @param maze the maze to analyze
/// @return int the number of steps in the solution
///     if no solution, return 0
int find_solution(maze_data maze);

#endif
