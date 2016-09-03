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
    if (argc < 3) {
        fprintf(stderr,"This program print the Score in a Rosetta PDB.\nUsage: %s dir output.txt.\n", argv[0]);
        EXIT_FAILURE;
    }
    if((fp = fopen(argv[2],"w")) != NULL){
        getScoreFromDir(argv[1], fp);
        fclose(fp);
    }
 
    EXIT_SUCCESS;
}
