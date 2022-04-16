//
// File: mopsolver.c
// mopsolver.c takes in a given maze, solves it, and prints solution if the 
// given flag is entered
//
// @author Ming Creekmore mec5765
// 
// @date 4/14/2022
//
// // // // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "QueueADT.h"
#include "map_config.h"
#include "maze_solve.h"

/// usage message as a string
static char* usage_msg = "Usage:\nmopsolver [-hdsp] [-i INFILE] [-o OUTFILE]\nOptions:\n   -h          Print usage and options list to stdout only.    (Default: off)\n   -d          Pretty-print (display) the maze after reading.  (Default: off)\n   -s          Print length of shortest path or 'No solution'. (Default: off)\n   -p          Pretty-print maze with the path, if one exists. (Default: off)\n   -i infile   Read maze from infile.                          (Default: stdin)\n   -o outfile  Write all output to outfile.                    (Default: stdout)\n";

/// struct options     holds optional choices that client picks
/// display            if not 0, will display initial maze
/// solve              if not 0, will solve for shortest path
/// print_solution     if not 0, will display shortest path
/// infile             open file for reading the maze
/// outfile            open file for writing output
struct choices {
    int display;
    int solve;
    int print_solution;
    char* infile;
    char* outfile;
};

typedef struct choices options;



/// prints the options struct
/// @param state    the struct to print
void print_struct(options state) {
    printf("\nStruct Options:\n");
    printf("Display: %d\n", state.display);
    printf("Solve: %d\n", state.solve);
    printf("Print Solution: %d\n", state.print_solution);
    printf("Infile: %s\n", state.infile);
    printf("Outfile: %s\n", state.outfile);
}

int main(int argc, char *argv[]) {
    static options state = {0, 0, 0, "stdin", "stdout"};
    int opt;

    //taking in optional arguments
    while((opt = getopt(argc, argv, "hdspi:o:")) != -1) {
        switch(opt) {
        case 'h': //help command
            printf("%s", usage_msg);
            return EXIT_SUCCESS;
            break;
        case 'd': //display initial maze
            state.display = 1;
            break;
        case 's': //solve
            state.solve = 1;
            break;
        case 'p': //print solution
            state.print_solution = 1;
            break;
        case 'i': //change infile
            state.infile = optarg;
            break;
        case 'o': //change outfile
            state.outfile = optarg;
            break;
        default: //if bad input
            fprintf(stderr, "%s", usage_msg);
            break;
        }
    } //end of while loop

    //setup files
    FILE *infile;
    if(strcmp(state.infile, "stdin") != 0) {
        infile = fopen(state.infile, "r");
    }
    else {
        infile = stdin;
    }
    maze_data maze = scan_maze(infile);
    FILE *outfile;
    if(strcmp(state.outfile, "stdout") != 0) {
        outfile = fopen(state.outfile, "w");
    }
    else {
        outfile = stdout;
    }

    //do operations based on input flags
    if(state.display == 1) {
        pretty_print(maze, outfile);
    }
    if(state.solve == 1) {
        int steps = find_solution(maze);
        if(steps != 0) {
            fprintf(outfile, "Solution in %d steps.\n", steps);
        }
        else {
            fprintf(outfile, "No Solution.\n");
        }
    }
    if(state.print_solution == 1) {
        if(state.solve == 0) {
            find_solution(maze);
        }
        pretty_print(maze, outfile);
    }

    //close files
    if(strcmp(state.infile, "stdin") != 0) {
        fclose(infile);
    }
    if(strcmp(state.outfile, "stdout") != 0) {
        fclose(outfile);
    }
    del_maze(maze);
}



