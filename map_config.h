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
#define _MAZE_DATA_
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
/// @param outfile    the file to print maze solution output on
void pretty_print(maze_data maze, FILE * outfile);

/// del_maze deletes a maze_data instance
///
/// @param maze       maze instance to be deleted
void del_maze(maze_data maze);


#endif
