//
// File: coor.h an interface for a coordinate ADT
//
// @author Ming Creekmore mec5765
//
// @date 4/15/2022
//
// // // // // // // // // // // // // // // // // // // // // // 

#ifndef _COOR_H_
#define _COOR_H_

#include <stdbool.h>

/// struct c represents coordinates of a 2D array and also links to the another
///          coordinate
///
/// col      col number
/// row      row number
/// prev     the previous struct c (as if you were following a path of coor)
struct c {
    size_t col;
    size_t row;
    struct c *prev;
}

typedef struct c *coor;

/// coor_create makes a new coordinate instance
///
/// @param row    row number
/// @param col    col number
/// @param prev   the previous coordinate struct (as if following path of coor)
/// @return       a new coordinate instance
coor coor_create(size_t row, size_t col, coor prev);

/// del_coor destroys the given coordinate
///
/// @param current the coordinate instance to be destroyed
void del_coor(void *current);

/// equals determines whether two coordinate structs are equal based on the 
/// col and row number
///
/// @param a    the first coordinate to compare
/// @param b    the second coordinate to compare
/// @return     1 if equals, 0 if not equals
bool equals(void *a, void *b);

/// prev returns the pointer to the coordinate struct that the given coor
/// points to
///
/// @param current   the coordinate struct to look at as a void*
/// @return          the pointer that the struct contains as a void*
void * prev(void *current);

#endif
