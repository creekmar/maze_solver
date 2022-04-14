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
void del_coor(coor current);

#endif
