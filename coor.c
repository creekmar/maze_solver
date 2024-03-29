//
// File: coor.c an implementation of coor.h
//
// @author Ming Creekmore mec5765
//
// @date 4/15/2022
//
// // // // // // // // // // // // // // // // // // // // // // // // //

#include "coor.h"
#include <assert.h>
#include <stdlib.h>

/// coor_create makes a new coordinate instance
coor coor_create(size_t row, size_t col, coor prev) {
    coor new = (coor) malloc(sizeof(struct c));
    assert(new != 0);
    new->row = row;
    new->col = col;
    new->prev = prev;
    return new;
}

/// del_coor destroys a coordinate instance but not the prev coordinate
void del_coor(void* current) {
    coor cur = (coor)(current);
    assert(cur != 0);
    free(cur);
}

/// equals determines whether two given coordinates are equal based on row and col
bool equals(const void* a,const void* b) {
    coor one = (coor) a;
    coor two = (coor) b;
    if(one->col == two->col) {
        if(one->row == two->row) {
            return 1;
        }
    }
    return 0;
}

