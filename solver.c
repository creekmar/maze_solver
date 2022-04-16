//
// File: solver.c an implementation of solver.h
//
// @author Ming Creekmore mec5765
//
// 4/15/2022
//
// // // // // // // // // // // // // // // // // // // // // // 

#include "solver.h"
#include "QueueADT.h"
#include <stdlib.h>

// solve finds a solution to a given configuration given helper functions and 
// the start point
void** solve(void * start, void * config, void (*del) (void *a), QueueADT (*getNeigh) (void *b, void *c), bool (*isSolution) (const void *d, const void *e), bool (*equals) (const void *f, const void *g)) {
    QueueADT queue = que_create(0, 0, 0);
    que_insert(queue, start);
    QueueADT hashmap = que_create(0, del, equals);
    que_insert(hashmap, start);
    void *current;

    // keep adding possible paths until no more places to go or reach solution
    while(!que_empty(queue)) {
        current = que_remove(queue, 0);
        if(isSolution(config, current)) {
            break;
        }
        QueueADT successor = getNeigh(config, current);
        if(successor != 0) {
            while(!que_empty(successor)) {
                void * neigh = que_remove(successor, 0);
                if(que_contains(hashmap, neigh) == -1) {
                    que_insert(queue, neigh);
                    que_insert(hashmap, neigh);
                }
                else {
                    del(neigh);
                }
            }
            que_destroy(successor);
        }
    }
    
    //destroy allocated memory if no solution
    que_destroy(queue);
    if(!isSolution(config, current)) {
        que_destroy(hashmap);
        return 0;
    }
    else {
        //return pointers to the solution
        void **pointers = (void**)malloc(sizeof(void*) * 2);
        pointers[0] = (void*) hashmap;
        pointers[1] = current;
        return pointers;
    }
}
