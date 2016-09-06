//
//  getScore.h
//  getScorePDB
//
//  Created by Ruqiang Liang on 9/2/16.
//  Copyright © 2016 Ruqiang Liang. All rights reserved.
//

#ifndef getScore_h
#define getScore_h

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#define START "ClassicGrid_grid_X"
#define END "total_score_X"
#define SEP " "

typedef struct {
    char* name;
    double* score;
} record;

int getScoreFromFile(char * fn, const FILE * fo, record rec);
int getLabelFromFile(const char * fn, const FILE * fo, char** label);
long int getScoreFromDir(const char * dn, const FILE * fo, record * myRec, char** label, size_t* dim);
int cmp(const void* x, const void* y);
#endif /* getScore_h */
