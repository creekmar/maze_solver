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
typedef struct m *maze_data;
#endif

#include <stdbool.h>
#include "QueueADT.h"
#include "coor.h"

/// is_solution checks if a coordinate is the end of the maze
/// 
/// @param config the maze to check
/// @param courrent the coordinate to check
/// @return 1 if solution, 0 if not solution
bool is_solution(const void *config, const void *current);

/// exit_blocked checks if the entrance and exit of the maze are blocked
///
/// @param maze the maze to check
/// @return 1 if blocked, 0 if clear
bool exit_blocked(maze_data maze);

/// wall_follower checks if there is a solution path along the edge of maze
/// also changes the maze to show the solution path
///
/// @param maze the maze to check
/// @return 1 if there is a path, 0 if no path
bool wall_follower(maze_data maze);

/// getNeighbors returns all the posible directions one can go from the given
/// coordinate
///
/// @param maze    the maze being analyzed
/// @param current the coordinate that you are currently on
/// @return        a QueueADT of all the possible neighbors
QueueADT getNeighbors(maze_data maze, coor current);

/// find_solution finds the shortest solution to the maze if there is one
/// and marks it on the maze and returns the number of steps
///
/// @param maze the maze to analyze
/// @return int the number of steps in the solution
///     if no solution, return 0
int find_solution(maze_data maze);


