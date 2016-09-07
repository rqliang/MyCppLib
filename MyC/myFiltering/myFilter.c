//
//  myFilter.c
//  myFiltering
//
//  Created by Ruqiang Liang on 9/7/16.
//  Copyright © 2016 Ruqiang Liang. All rights reserved.
//

#include "myFilter.h"
#include <stdlib.h>
#include <string.h>

extern int tag;

int getIndex(char** labels, const char* name) {
    //size_t num = sizeof(**labels) / sizeof(*name);
    int n=0;
    for (char** i = labels; i != NULL; ++i, ++n) {
        if (!(strcmp(*i, name)))
            return n;
    }
    return -1;
}
int comp_increase(const void * x, const void * y) {
    myRecord xx = * (myRecord* )x;
    myRecord yy = * (myRecord* )y;
    if (xx.scores[tag] < yy.scores[tag]) return -1;
    if (xx.scores[tag] > yy.scores[tag]) return 1;
    return 0;
}

int comp_decrease(const void * x, const void * y) {
    myRecord xx = * (myRecord* )x;
    myRecord yy = * (myRecord* )y;
    if (xx.scores[tag] < yy.scores[tag]) return 1;
    if (xx.scores[tag] > yy.scores[tag]) return -1;
    return 0;
}
