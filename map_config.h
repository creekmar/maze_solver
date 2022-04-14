// 
// map_config.h is an interface of an ADT for a maze map
//
// @author: Ming Creekmore mec5765
//
// @date: 4/15/2022
//
// // // // // // // // // // // // // // // // // // // // // //

#ifndef _MAPCONFIG_
#define _MAPCONFIG_

#include <stdbool.h>
#include "coor.h"

#ifndef _MAZE_DATA_
typedef struct m *maze_data;
#endif

/// scan_maze a function to make a new maze_data instance from a file
///
/// @param input      file to be read
/// @return maze_data the maze instance created
maze_data scan_maze(FILE *input);

/// pretty_print a function to print a maze with good format
///
/// @param maze       maze instance to be printed
void pretty_print(maze_data maze);

/// del_maze deletes a maze_data instance
///
/// @param maze       maze instance to be deleted
void del_maze(maze_data maze);

/// is_solution determines whether the given coordinate instance is the end of 
///       the maze
///
/// @param maze    the maze being analyzed
/// @param current coordinate instance 
/// @return        1 if the coor is the maze exit, 0 otherwise
bool is_solution(maze_data maze, coor current);

/// getNeighbors returns all the posible directions one can go from the given
/// coordinate
///
/// @param maze    the maze being analyzed
/// @param current the coordinate that you are currently on
/// @return        a QueueADT of all the possible neighbors
QueueADT getNeighbors(maze_data maze, coor current);


#endif
