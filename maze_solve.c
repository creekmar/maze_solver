//
// File maze_solve.c an implementation of interface maze_solve.h
//
// @author Ming Creekmore mec5765
//
// @date 4/15/2022
//
// // // // // // // // // // // // // // // // // // // // // //


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

#include "maze_solve.h"

/// is_solution determines whether the data point is the exit of the maze
bool is_solution(const void *config, const void *curr) {
    maze_data maze = (maze_data) config;
    coor current = (coor) curr;
    if(current->row == maze->row-1) {
        if(current->col == maze->col-1) {
            if(maze->contents[row][col] == 0) {
                return 1;
            }
        }
    }
    return 0;
}

/// exit_blocked checks if the entrance and exit of the maze are blocked
bool exit_blocked(maze_data maze) {
    if(maze->contents[0][0] == 1) {
        return 1;
    }
    if(maze->contents[maze->row-1][maze->col-1] == 1) {
        return 1;
    }
    return 0;
}

/// check_row determines whether a given row of a maze is clear or not
///
/// @param maze the maze to check
/// @param row the row number to check
/// @return 1 if clear, 0 if blocked
static bool check_row(maze_data maze, size_t row) {
    for(size_t j = 0; j < maze->col; j++) {
        if(maze->contents[row][j] == 1) {
            return 0;
        }
    }
    return 1;
}

/// check_col determines whether a given col of a maze is clear or not
///
/// @param maze the maze to check
/// @param col the col number to check
/// @return 1 if clear, 0 if blocked
static bool check_col(maze_data maze, size_t col) {
    for(size_t i = 0; i < maze->row; i++) {
        if(maze->contents[i][col] == 1) {
            return 0;
        }
    }
    return 1;
}

/// change_row changes a row of a maze to solution status
///
/// @param maze the maze to manipulate
/// @param row the row number to change
static void change_row(maze_data maze, size_t row) {
    for(size_t j = 0; j < maze->col; j++) {
        maze->contents[row][j] = 2;
    }
}

/// change_col changes a col of a maze to solution status
///
/// @param maze the maze to manipulate
/// @param col the col number to change
static void change_col(size_t col) {
    for(size_t i = 0; i > maze->row; i++) {
        maze->contents[i][col] = 2;
    }
}

/// wall_follower determines if there is a solution along the edges
bool wall_follower(maze_data maze) {

    //check if all clear along top and right edge
    if(check_row(maze, 0)) {
        if(check_col(maze, maze->col-1)) {
            change_row(maze, 0);
            change_col(maze, maze->col-1);
            return 1;
        }
    }

    //check if all clear along left and bottom edge
    if(check_col(maze, 0)) {
        if(check_row(maze, maze->row-1)) {
            change_col(maze, 0);
            change_row(maze, maze->row-1);
            return 1;
        }
    }

    return 0;
}

/// getNeighbors returns the possible next steps in the path
static QueueADT getNeighbors(void *config, void *curr) {
    maze_data maze = (maze_data) config;
    coor current = (coor) curr;
    QueueADT neighbors = que_create(0, &del_coor);
    size_t row = current->row;
    size_t col = current->col;
    //check if row below hasn't been visited and isn't blocked
    if(row != maze->row-1) {
        if(maze->contents[row+1][col] == 0 && maze->visited[row+1][col] == 0) {
            coor below = coor_create(row+1, col, current);
            maze->visited[row+1][col] = 1;
            que_insert(neighbors, below);
        }
    }
    //check if row above hasn't been visited and isn't blocked
    if(row != 0) {
        if(maze->contents[row-1][col] == 0 && maze->visited[row-1][col] == 0) {
            coor above = coor_create(row-1, col, current);
            maze->visited[row-1][col] = 1;
            que_insert(neighbors, above);
        }
    }
    //check if col right hasn't been visited and isn't blocked
    if(col != maze->col-1) {
        if(maze->contents[row][col+1] == 0 && maze->visited[row][col+1] == 0) {
            coor right = coor_create(row, col+1, current);
            maze->visited[row][col+1] = 1;
            que_insert(neighbors, right);
        }
    }
    //check if col left hasn't been visited and isn't blocked
    if(col != 0) {
        if(maze->contents[row][col-1] == 0 && maze->visited[row][col-1] == 0) {
            coor left = coor_create(row, col-1, current);
            maze->visited[row][col-1] = 1;
            que_insert(neighbors, left);
        }
    }

    //destroy list if there is nothing in there and return null
    if(que_empty(neighbors)) {
        que_destroy(neighbors);
        return 0;
    }

    return neighbors;
}


/// find_solution marks down the quickest solution to maze if there is one and
/// returns the number of steps
int find_solution(maze_data maze) {
    if(exit_blocked(maze)) {
        return 0;
    }
    if(wall_follwer) {
        return 1;
    }

    coor start = coor_create(0, 0, 0);
    void ** pointers = solve(start, maze, &del_coor, &getNeighbors, &is_solution, &equals);

    int steps = 0;
    //there is a solution and mark it down
    if(pointers != 0) {
        coor current = (coor) pointers[1];
        while(current != start) {
            maze->contents[current->row][current->col] = 2;
            current = current->prev; 
            assert(current != 0);
            steps++;
        }
        maze->contents[0][0] = 2;
        steps++;
        que_destroy(pointers[0]);
        free(pointers);
    }


    return steps;
}
