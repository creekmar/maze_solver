//
// File: QueueADT.c
// QueueADT.c implements the interface QueueADT.h
//
// @author Ming Creekmore mec5765
// 
// @date 3/24/2022
//
// // // // // // // // // // // // // // // // // // // //

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#define ALLOC_UNIT 5

/// struct stackStruct      array of 64 bit values with basic info about array
/// contents                array that contains 64 bit values
/// capacity                max number of units in the array
/// len                     number of spots initialized in the array
/// cmp                     pointer to function that tells how to order array
/// del                     pointer to function that frees the data that is added
///                         to contents, only for heap allocated data
struct stackStruct {
    void **contents;
    size_t capacity;
    size_t len;
    int (*cmp)(const void *a, const void *b);
    void (*del)(const void *c);
};

typedef struct stackStruct *QueueADT;

#define _QUEUE_IMPL_
#include "QueueADT.h"

/// que_empty tells whether given queue has any contents
bool que_empty(QueueADT queue) {
    return (queue->len == 0);
}

/// que_findInsert      determines where in the queue the data belongs based 
///                     on the comparision function
/// @param queue        the queueADT that the data will be inserted into
/// @param data         the value to add to the queue
/// @return int         the index where data should be added - values at the
///                     index all the way to the end of queue should be 
///                     shifted to the right by one
static int que_findInsert(QueueADT queue, void *data) {
    int pointer;
    for(pointer = queue->len; pointer > 0; pointer--) {
        int compare = queue->cmp(data, queue->contents[pointer-1]);
        if(compare > 0) {
            break;
        }
    }
    return pointer;
}

/// que_create makes a new QueueADT that will sort data based on
/// the comparision function given
QueueADT que_create(int (*cmp)(const void *a, const void *b), void (*del)(const void *c)) {
    QueueADT queue;
    queue = (QueueADT) malloc(sizeof(struct stackStruct));

    if(queue != 0) {
        queue->contents = 0;
        queue->capacity = 0;
        queue->len = 0;
        queue->cmp = cmp;
        queue->del = del;
    }
    return queue;
}

/// que_destroy completely frees any memory associated with the 
/// given queue
void que_destroy(QueueADT queue) {
    assert(queue != 0);
    if(queue->contents != 0) {
        if(queue->del != 0) {
            for(int i = queue->len; i > 0; i--) {
                del(queue->contents[i-1]);
            }
        }
        free(queue->contents);
    }
    free(queue);
}

/// que_clear removes all contents from queue and resets values
void que_clear(QueueADT queue) {
    assert(queue != 0);
    if(queue->contents != 0) {
        if(queue->del != 0) {
            for(int i = queue->len; i > 0; i--) {
                del(queue->contents[i-1]);
            }
        }
        free(queue->contents);
        queue->contents = 0;
    }
    queue->capacity = 0;
    queue->len = 0;
}

/// que_insert inserts specified data pointer into the queue based on the
/// cmp function found in queue
void que_insert(QueueADT queue, void *data) {
    assert(queue != 0);

    //initialize queue contents if empty
    if(queue->contents == 0) {
        queue->contents = malloc(sizeof(void*) * ALLOC_UNIT);
        assert(queue->contents != 0);
        queue->capacity = ALLOC_UNIT;
    }
    //if need more space
    else if(queue->len >= queue->capacity) {
        void *tmp;
        tmp = realloc(queue->contents, sizeof(void*) * (queue->capacity + ALLOC_UNIT));
        assert(tmp != 0);
        queue->contents = tmp;
        queue->capacity += ALLOC_UNIT;
    }
    
    //no comparison function so use FILO
    if(queue->cmp == 0) {
        queue->contents[queue->len] = data;
        queue->len +=1;
    }
    //else will add data based on cmp function in queue
    else {
        int pointer = que_findInsert(queue, data);
        for(int i = queue->len; i > pointer; i--) {
            queue->contents[i] = queue->contents[i-1];
        }
        queue->contents[pointer] = data;
        queue->len += 1;
    }
}

/// que_remove removes and returns the first element in the list
void* que_remove(QueueADT queue) {
    void *data;
    assert(!que_empty(queue));
    data = queue->contents[0];

    //move all data forward/to the left
    for(size_t i = 0; i < (queue->len-1); i++) {
        queue->contents[i] = queue ->contents[i+1];
    }

    queue->len -= 1;
    return data;
}

