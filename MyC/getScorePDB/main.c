//
//  main.c
//  getScorePDB
//
//  Created by Ruqiang Liang on 9/2/16.
//  Copyright © 2016 Ruqiang Liang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "getScore.h"



int main(int argc, const char * argv[]) {
    FILE * fp;
    char** labels = (char **) malloc(20000*sizeof(char*));
    double** scores = (double **) malloc(20000*sizeof(double*));
    for (int i=0; i<20000; ++i) {
        scores[i] = (double *) malloc(60*sizeof(double));
        labels[i] = (char *) malloc(60*sizeof(char));
    }
    long int rows = 0;
    if (argc < 3) {
        fprintf(stderr,"This program print the Score in a Rosetta PDB.\nUsage: %s dir output.txt.\n", argv[0]);
        EXIT_FAILURE;
    }
    if((fp = fopen(argv[2],"w")) != NULL){
        rows = getScoreFromDir(argv[1], fp, scores, labels);
        fclose(fp);
    }
    
    
    for (int i=0; i<20000; ++i) {
        free(scores[i]);
        free(labels[i]);
    }
    free(labels);
    free(scores);
    return EXIT_SUCCESS;
}
