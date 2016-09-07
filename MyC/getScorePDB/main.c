//
//  main.c
//  getScorePDB
//
//  Created by Ruqiang Liang on 9/2/16.
//  Copyright © 2016 Ruqiang Liang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getScore.h"
#define LENGTH 30000
#define WIDTH   60



int main(int argc, const char * argv[]) {
    FILE * fp;
    char dirname[1024];
    strcpy(dirname, argv[1]);
    size_t * dim = (size_t *) calloc(2, sizeof(size_t));
    char** labels = (char **) malloc(WIDTH * sizeof(char*));
    record * myRecords = (record *) malloc ( LENGTH * sizeof(record));
    for(int i=0; i < LENGTH; ++i) {
        myRecords[i].score = malloc(WIDTH * sizeof(double));
        myRecords[i].name = malloc(WIDTH * sizeof(char));
    }
    
    for (int i=0; i < WIDTH; ++i)
        labels[i] = (char *) malloc(WIDTH * sizeof(char));
    
    if (argc < 3) {
        fprintf(stderr,"This program print the Score in a Rosetta PDB.\nUsage: %s dir output.txt.\n", argv[0]);
        EXIT_FAILURE;
    }
    if((fp = fopen(argv[2],"w")) != NULL){
        getScoreFromDir(dirname, fp, myRecords, labels, dim);
        fclose(fp);
    }
    
    size_t nrow = dim[1];
    size_t ncol = dim[0];
    
    qsort(myRecords, nrow, sizeof(record), cmp);
    for(int i=0; i < nrow; i += nrow/10)
        printf("scores[%d] = %g \t %s.\n",i,myRecords[i].score[52], myRecords[i].name);
    
    for (int i=0; i<LENGTH; ++i) {
        free(myRecords[i].name);
        free(myRecords[i].score);
    }
    for (int i=0; i<WIDTH; ++i)
        free(labels[i]);
    free(dim);
    free(labels);
    free(myRecords);
    return EXIT_SUCCESS;
}
