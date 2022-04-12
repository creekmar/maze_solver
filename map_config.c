// 
// map_config.c is an implementation of map_config.h
//
// @author: Ming Creekmore mec5765
//
// @date: 4/15/2022
//
// // // // // // // // // // // // // // // // // // // // // //

#include "map_config.h"
#include "QueueADT.h"

static void del_line(QueueADT queue) {
    que_destroy(queue);
}

static void (*delete)(QueueADT) = &del_line;

QueueADT scan_maze(FILE *input) {
    QueueADT map = que_create(NULL, delete);
    char tmp '\0';
    while(!feof(input)) {
        // a queue for each line of the maze
        QueueADT line = que_create(NULL, NULL);
        while(tmp != '\n') {
            tmp = getc(input);
            if(tmp ==  0 || tmp == 1) {
                que_insert(line, &tmp);
            }
        }
        que_insert(map, line);
    }
    return map;
}


