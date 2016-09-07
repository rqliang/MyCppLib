//
//  main.c
//  myFiltering
//
//  Created by Ruqiang Liang on 9/7/16.
//  Copyright © 2016 Ruqiang Liang. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "myFilter.h"
#include <stdlib.h>

#define NROW 30000
#define NCOL 60

int tag;

int main(int argc, const char * argv[]) {
    // insert code here...
    FILE* fp;
    int i;
    char* line = calloc(2048, sizeof(char));
    char disposible[NCOL];
    if (argc < 4){
        fprintf(stderr,"Usage: %s input.sc\n", argv[0]);
        return EXIT_FAILURE;
    }
    char** labels = (char**) calloc(NCOL , sizeof(char*));
    for (int i=0; i<NCOL; ++i)
        labels[i] = (char*)calloc(NCOL , sizeof(char));
    myRecord* rec = (myRecord*) calloc(NROW, sizeof(myRecord));
    
    if(fp = fopen(argv[1],"r")) {
        fgets(line, 2048, fp);
        fgets(line, 2048, fp);
        sscanf(line, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
               "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", &disposible,labels[0], labels[1],labels[2],labels[3], \
               labels[4], labels[5],labels[6],labels[7],labels[8], labels[9],labels[10],labels[11],labels[12], \
               labels[13],labels[14],labels[15],labels[16], labels[17],labels[18],labels[19],labels[20], labels[21], \
               labels[22],labels[23],labels[24], labels[25],labels[26],labels[27],labels[28], labels[29],labels[30], \
               labels[31],labels[32],labels[33], labels[34],labels[35],labels[36],labels[37], labels[38],labels[39], \
               labels[40],labels[41], labels[42],labels[43],labels[44],labels[45], labels[46],labels[47],labels[48], \
               labels[49], labels[50],labels[51],labels[52],labels[53], labels[54],labels[55],labels[56]);
        
        for (i=0;fgets(line, 2048, fp); ) {
            if (strstr(line, "SEQUENCE")) continue;
            if (strstr(line,"total_score")) continue;
            sscanf(line, "%s%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f"
                   "%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%s", \
                   &disposible, &rec[i].scores[0],  \
                   &rec[i].scores[1],&rec[i].scores[2],&rec[i].scores[3],&rec[i].scores[4], &rec[i].scores[5], \
                   &rec[i].scores[6],&rec[i].scores[7],&rec[i].scores[8], &rec[i].scores[9],&rec[i].scores[10], \
                   &rec[i].scores[11],&rec[i].scores[12], &rec[i].scores[13],&rec[i].scores[14],&rec[i].scores[15], \
                   &rec[i].scores[16], &rec[i].scores[17],&rec[i].scores[18],&rec[i].scores[19],&rec[i].scores[20], \
                   &rec[i].scores[21],&rec[i].scores[22],&rec[i].scores[23],&rec[i].scores[24], &rec[i].scores[25], \
                   &rec[i].scores[26],&rec[i].scores[27],&rec[i].scores[28], &rec[i].scores[29],&rec[i].scores[30], \
                   &rec[i].scores[31],&rec[i].scores[32],&rec[i].scores[33], &rec[i].scores[34],&rec[i].scores[35], \
                   &rec[i].scores[36],&rec[i].scores[37], &rec[i].scores[38],&rec[i].scores[39],&rec[i].scores[40], \
                   &rec[i].scores[41], &rec[i].scores[42],&rec[i].scores[43],&rec[i].scores[44],&rec[i].scores[45], \
                   &rec[i].scores[46],&rec[i].scores[47],&rec[i].scores[48],&rec[i].scores[49], &rec[i].scores[50], \
                   &rec[i].scores[51],&rec[i].scores[52],&rec[i].scores[53], &rec[i].scores[54],&rec[i].scores[55], \
                   &rec[i].name);
            ++i;
        }
        
    }
    fclose(fp);

    tag = getIndex(labels, "total_score");

    qsort(rec, i, sizeof(myRecord), comp_increase);
    int deep = i/10;
    
    fprintf(stdout,"Discarded %.2f%% (%d) designs filtered by total_score.\n", (i-deep)*100.0/i, (i-deep));
    tag = getIndex(labels, "if_X_fa_rep");

    qsort(rec, deep, sizeof(myRecord), comp_increase);
    for(int i=0; i<deep; ++i)
        if (rec[i].scores[tag] > 1.0){
            fprintf(stdout,"Discarded %.2f%% (%d) designs filtered by if_X_fa_rep.\n", (deep-i)*100.0/deep, (deep-i));
            deep = i;
            break;
        }
    tag = getIndex(labels, "ligand_is_touching_X");

    qsort(rec, deep, sizeof(myRecord), comp_decrease);
    for(int i=0; i<deep; ++i)
        if (rec[i].scores[tag] < 0.5){
            fprintf(stdout,"Discarded %.2f%% (%d) designs filtered by ligand_is_touching_X.\n", (deep-i)*100.0/deep, (deep-i));
            deep = i;
            break;
        }
    tag = getIndex(labels, "interface_delta_X");

    qsort(rec, deep, sizeof(myRecord), comp_increase);
    fprintf(stdout,"Only %d designs passed filters.\n", deep);
    if(fp = fopen(argv[2],"w")) {
        for(int i=0; i< 57; ++i) {
            fprintf(fp,"%s",labels[i]);
            if (i !=56) fprintf(fp,"\t");
        }
        fprintf(fp,"\n");
        for (int i=0; i< deep; ++i) {
            for(int j=0; j< 56; ++j)
                fprintf(fp,"%f\t", rec[i].scores[j]);
            fprintf(fp,"%s\n",rec[i].name);
        }
    }
    fclose(fp);
    
    if(fp = fopen(argv[3],"w")){
        for (int i=0; i< deep; ++i)
            fprintf(fp,"%s.pdb\n",rec[i].name);
    }
    
    fclose(fp);
    
    free(rec);
    for (int i=0; i<NCOL; ++i)
        free(labels[i]);
    free(labels);
    free(line);
    return 0;
}
