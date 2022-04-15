// 
// map_config.c is an implementation of map_config.h
//
// @author: Ming Creekmore mec5765
//
// @date: 4/15/2022
//
// // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define ALLOC_UNIT 5

/// struct to hold all maze values
///
/// row           the number of rows
/// col           the number of cols
/// col_capacity  the number of units allocated on heap for col
/// row_capacity  the number of units allocated on heap for row
/// contents      double array of unsigned int values to represent map
struct m {
    size_t row;
    size_t col;
    size_t col_capacity;
    size_t row_capacity;
    size_t **contents;
    bool **visited;
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
                    size_t *tmp = (size_t*)(realloc(maze->contents[maze->row], sizeof(size_t)*(maze->col_capacity + ALLOC_UNIT)));
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
    maze->contents = (size_t**) malloc(5*sizeof(size_t*));
    assert(maze->contents != 0);
    maze->row_capacity = ALLOC_UNIT;
    maze->contents[maze->row] = (size_t*) malloc(5*sizeof(size_t));
    assert(maze->contents[maze->row] != 0);
    maze->col_capacity = ALLOC_UNIT;
    char tmp = '\0';

    //read in first row to determine col size
    find_col(maze, input);
    //read in rest of rows
    while(!feof(input)) {
        maze->col = 0;
        maze->contents[maze->row] = (size_t*) malloc(sizeof(size_t)*maze->col_capacity);
        while(tmp != '\n') {
            //add data to array
            if(tmp == '0') {
                maze->contents[maze->row][maze->col] = 0;
                maze->col += 1;
            }
            else if(tmp == '1') {
                maze->contents[maze->row][maze->col] = 1;
                maze->col += 1;
            }
            tmp = getc(input);
        }
        //go to char after newline char
        tmp = getc(input);

        //if not enough row space
        if(maze->row >= maze->row_capacity-1) {
            size_t **tmp = (size_t**) realloc(maze->contents, sizeof(size_t*)*(maze->row_capacity + ALLOC_UNIT));
            assert(tmp != 0);
            maze->contents = tmp;
            maze->row_capacity += ALLOC_UNIT;
        }
        maze->row++;
    }
    
    //initialize visited 2d array
    maze->visited = (bool**) malloc(sizeof(bool)*maze->row);
    for(size_t i = 0; i < maze->row; i++) {
        maze->visited[i] = (bool*) malloc(sizeof(bool*)*maze->col);
    }
        
    return maze;
}

/// print_ends prints the border ends of the maze
///
/// @param col the number of col in the maze
static void print_ends(size_t col) {
    printf("|-");
    for(size_t i = 0; i< col; i++) {
        printf("--");
    }
    printf("|\n");
}

/// print_col prints a row of columns given a maze and the row number
///
/// @maze the maze to print
/// @row the row to print
static void print_col(maze_data maze, size_t row) {
    for(size_t i = 0; i < maze->col; i++) {
        switch(maze->contents[row][i]) {
            case 0: printf(". ");
                break;
            case 1: printf("# ");
                break;
            case 2: printf("+ ");
                break;
        }
    }
}

/// pretty_print prints a maze in a nice, readable format
void pretty_print(maze_data maze) {
    assert(maze != 0);
    //print first two lines with specific format
    print_ends(maze->col);
    printf("  ");
    print_col(maze, 0);
    printf("|\n");
    //prints the body
    for(size_t i = 1; i < maze->row-1; i++) {
        printf("| ");
        print_col(maze, i);
        printf("|\n");
    }
    //prints last two rows with specific format
    printf("| ");
    print_col(maze, maze->row-1);
    printf("\n");
    print_ends(maze->col);
}

/// deletes a maze instance
void del_maze(maze_data maze) {
    assert(maze != 0);
    //free valid
    for(size_t i = maze->row-1; i >= 0; i--) {
        free(maze->visited[i]);
    }
    free(maze->visited);
    //free contents
    for(size_t i = maze->row-1; i >= 0; i--) {
        free(maze->contents[i]);
    }
    free(maze->contents);
    free(maze);
}

