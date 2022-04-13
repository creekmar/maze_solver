// 
// map_config.c is an implementation of map_config.h
//
// @author: Ming Creekmore mec5765
//
// @date: 4/15/2022
//
// // // // // // // // // // // // // // // // // // // // // //

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define ALLOC_UNIT 5

/// struct to hold all maze values
///
/// row           the number of rows
/// col           the number of cols
/// col_capacity  the number of units allocated on heap for col
/// row_capacity  the number of units allocated on heap for row
/// contents      double array of boolean values to represent map
struct m {
    int row;
    int col;
    int col_capacity;
    int row_capacity;
    bool **contents;
};

typedef struct m *maze_data;

#define _MAZE_DATA_
#include "map_config.h"

/// find_col a function to determine the number of columns and set the first row
///
/// @param maze   the maze to manipulate
/// @input        the file to read in maze data
static void find_col(maze_data maze, FILE *input) {
     char tmp = '\0';
     //read entire first line of file
     while(tmp != '\n') {
            tmp = getc(input);
            if(tmp == '0' || tmp == '1') {
                //if not enough column space
                if(maze->col >= maze->col_capacity) {
                    bool *tmp = (bool*)(realloc(maze->contents[maze->row], sizeof(bool)*(maze->col_capacity + ALLOC_UNIT)));
                    assert(tmp != 0);
                    maze->contents[maze->row] = tmp;
                    maze->col_capacity += ALLOC_UNIT;
                }
                //add new data to array
                if(tmp ==  '0') {
                    maze->contents[maze->row][maze->col] = 0;
                    maze->col += 1;
                }
                else if(tmp == '1') {
                    maze->contents[maze->row][maze->col] = 1;
                    maze->col += 1;
                }
            }
     }
     maze->col = 0;
     maze->row += 1;
}

/// scan_maze a function to create a maze from an input file
maze_data scan_maze(FILE *input) {
    //initialize and allocate stuff
    maze_data maze;
    maze = (maze_data)malloc(sizeof(struct m));
    assert(maze != 0);
    maze->row = 0;
    maze->col = 0;
    maze->contents = (bool**) malloc(5*sizeof(bool));
    assert(maze->contents != 0);
    maze->row_capacity = ALLOC_UNIT;
    maze->contents[maze->row] = (bool*) malloc(5*sizeof(bool));
    assert(maze->contents[maze->row] != 0);
    maze->col_capacity = ALLOC_UNIT;
    char tmp = '\0';

    //read in first row to determine col size
    find_col(maze, input);
    //read in rest of rows
    while(!feof(input)) {
        maze->col = 0;
        maze->contents[maze->row] = (bool*) malloc(sizeof(bool)*maze->col_capacity);
        while(tmp != '\n') {
            tmp = getc(input);
            //add data to array
            if(tmp == '0') {
                maze->contents[maze->row][maze->col] = 0;
                maze->col += 1;
            }
            else if(tmp == '1') {
                maze->contents[maze->row][maze->col] = 1;
                maze->col += 1;
            }
        }

        //if not enough row space
        if(maze->row >= maze->row_capacity) {
            bool **tmp = (bool**) realloc(maze->contents, sizeof(bool)*(maze->row_capacity + ALLOC_UNIT));
            assert(tmp != 0);
            maze->contents = tmp;
            maze->row_capacity += ALLOC_UNIT;
        }
        maze->row++;
    }
        
    return map;
}

/// pretty_print prints a maze in a nice, readable format
void pretty_print(maze_data maze) {
    for(int i = 0; i < maze->row; i++) {
        for(int j = 0; j < maze->col; j++) {
            printf("%c", maze->contents[i][j]);
        }
        printf("\n");
    }
}
