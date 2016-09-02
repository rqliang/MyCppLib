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

#define START "ClassicGrid_grid_X"
#define END "total_score_X"
#define SEP " "

int main(int argc, const char * argv[]) {
    FILE * fp;
    char line[256];
    //char line2[256];
    char * p;
    //int tagEnd = 0;
    int tagStart = 0;
    
    if (argc < 2) {
        fprintf(stderr,"This program print the Score in a Rosetta PDB.\nUsage: %s input.pdb.\n", argv[0]);
        EXIT_FAILURE;
    }
    if ((fp = fopen(argv[1], "r")) != NULL) {
        while (fgets(line, sizeof(line), fp)){
            //strncpy(line,line2,strlen(line2)+1);
            line[strlen(line)-1] = '\0';
            if ((p = strstr(line, START)) != NULL)
            {
                tagStart = 1;
                printf("%s", p+strlen(START)+1);
            } else if (tagStart) {
                if ((p = strstr(line, SEP)) != NULL)
                    printf("\t%s", p+strlen(SEP));
            }
            if ((p = strstr(line, END)) != NULL) {
                tagStart = 0;
                //printf("\t%s\n",p+strlen(END));
                printf("\n");
                break;
            }
                
        }
    }
    fclose(fp);
    return 0;
}
