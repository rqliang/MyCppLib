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

int getScoreFromFile(char * fn, const FILE * fo, double * score);
int getLabelFromFile(const char * fn, const FILE * fo, char** label);
long int getScoreFromDir(const char * dn, const FILE * fo, double ** scores, char** label);

#endif /* getScore_h */
