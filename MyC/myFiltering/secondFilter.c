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

#define NROW 1000
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
        sscanf(line, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", &disposible,labels[0], labels[1], \
               labels[2],labels[3], labels[4], labels[5],labels[6],labels[7],labels[8], labels[9],labels[10], \
               labels[11],labels[12], labels[13],labels[14],labels[15],labels[16], labels[17],labels[18], \
               labels[19],labels[20], labels[21]);
        
        for (i=0;fgets(line, 2048, fp); ) {
            if (strstr(line, "SEQUENCE")) continue;
            if (strstr(line,"total_score")) continue;
            sscanf(line, "%s%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%s", &disposible, &rec[i].scores[0],  \
                   &rec[i].scores[1],&rec[i].scores[2],&rec[i].scores[3],&rec[i].scores[4], &rec[i].scores[5], \
                   &rec[i].scores[6],&rec[i].scores[7],&rec[i].scores[8], &rec[i].scores[9],&rec[i].scores[10], \
                   &rec[i].scores[11],&rec[i].scores[12], &rec[i].scores[13],&rec[i].scores[14],&rec[i].scores[15], \
                   &rec[i].scores[16], &rec[i].scores[17],&rec[i].scores[18],&rec[i].scores[19],&rec[i].scores[20], \
                   &rec[i].name);
            ++i;
        }
        
    }
    fclose(fp);
    
    tag = getIndex(labels, "packstat");
    
    qsort(rec, i, sizeof(myRecord), comp_decrease);
    int deep = i;
    for(int i=0; i<deep; ++i)
        if (rec[i].scores[tag] < 0.55){
            fprintf(stdout,"Discarded %.2f%% (%d) designs filtered by packstat.\n", (deep-i)*100.0/deep, (deep-i));
            deep = i;
            break;
        }
    

    tag = getIndex(labels, "sc_value");
    
    qsort(rec, deep, sizeof(myRecord), comp_decrease);
    for(int i=0; i<deep; ++i)
        if (rec[i].scores[tag] < 0.45){
            fprintf(stdout,"Discarded %.2f%% (%d) designs filtered by sc_value.\n", (deep-i)*100.0/deep, (deep-i));
            deep = i;
            break;
        }
    tag = getIndex(labels, "delta_unsatHbonds");
    
    qsort(rec, deep, sizeof(myRecord), comp_increase);
    for(int i=0; i<deep; ++i)
        if (rec[i].scores[tag] > 1.5){
            fprintf(stdout,"Discarded %.2f%% (%d) designs filtered by delta_unsatHbonds.\n", (deep-i)*100.0/deep, (deep-i));
            deep = i;
            break;
        }
    
    tag = getIndex(labels, "dG_separated/dSASAx100");
    qsort(rec, deep, sizeof(myRecord), comp_increase);
    for(int i=0; i<deep; ++i)
        if (rec[i].scores[tag] > -0.5){
            fprintf(stdout,"Discarded %.2f%% (%d) designs filtered by dG_separated/dSASAx100.\n", (deep-i)*100.0/deep, (deep-i));
            deep = i;
            break;
        }
    
    tag = getIndex(labels, "dG_separated");
    
    qsort(rec, deep, sizeof(myRecord), comp_increase);
    fprintf(stdout,"Only %d designs passed filters.\n", deep);
    
    if(fp = fopen(argv[2],"w")) {
        for(int i=0; i< 26; ++i) {
            fprintf(fp,"%s",labels[i]);
            if (i !=25) fprintf(fp,"\t");
        }
        fprintf(fp,"\n");
        for (int i=0; i< deep; ++i) {
            for(int j=0; j< 26; ++j)
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
