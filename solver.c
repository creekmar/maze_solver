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

QueueADT construct_path(QueueADT hashmap, void *start, void *end, void* (*prev) (void*)) {
    QueueADT path = que_create(0, del, 0);
    if(que_remove(hashmap, end) != 0) {
        void * current = end;
        while(current != start) {
            que_insert(path, current);
            current = prev(current); 
            assert(current != 0);
            que_remove(hashmap, current);
        }
        que_remove(hashmap, start);
        que_insert(path, start);
    }
    que_destroy(hashmap);
    return path;
}

QueueADT solve(void * start, void * config, void (*del) (void *a), QueueADT (*getNeigh) (void *b, void *c), bool (*isSolution) (const void *d, const void *e), bool (*equals) (const void *f, const void *g), void* (*prev) (void*)) {
    QueueADT queue = que_create(0, del, 0);
    que_insert(queue, start);
    QueueADT hashmap = que_create(0, del, equals);
    que_insert(hashmap, start);
    void *current;

    // keep adding possible paths until no more places to go or reach solution
    while(!que_empty(queue)) {
        current = que_remove(queue);
        if(isSolution(config, current)) {
            break;
        }
        QueueADT successor = getNeigh(config, current);
        while(!que_empty(successor)) {
            void * neigh = que_remove(successor);
            if(!que_contains(hashmap, neigh)) {
                que_insert(queue, neigh);
                que_insert(hashmap, neigh);
            }
            else {
                del(neigh);
            }
        }
        que_destroy(successor);
    }
    
    que_destroy(queue);
    if(!isSolution(config, current)) {
        que_destroy(hashmap);
        return 0;
    }
    else {
        return construct_path(hashmap, start, current, prev);
    }
}
