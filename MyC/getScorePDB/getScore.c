//
//  getScore.c
//  getScorePDB
//
//  Created by Ruqiang Liang on 9/2/16.
//  Copyright © 2016 Ruqiang Liang. All rights reserved.
//

#include "getScore.h"
#include <string.h>
#include <stdlib.h>

int getScoreFromFile(char * fn,  FILE * fo, record myrec)
{
    FILE* fp;
    char* p;
    char line[256];
    
    //int tag = 0;
    int i = 0;
    
    if((fp = fopen(fn,"r")) != NULL){
        for (int tag =0 ; fgets(line, 256, fp); ) {
            
            line[strlen(line)-1] = '\0';
            if ((p=strstr(line,START))) {
                tag = 1;
                p = p+strlen(START)+1;
                fprintf(fo,"%s\t", p);
                myrec.score[i] = strtod(p,0);
                ++i;
            } else if ((p=strstr(line,END))) {
                tag = 0;
                fn[strlen(fn)-4] = '\0';
                p = p+strlen(END)+1;
                strcpy(myrec.name, fn);
                fprintf(fo,"%s\t%s\n",p,fn);
                myrec.score[i] = strtod(p,0);
                break;
            } else if(tag) {
                if ((p=strstr(line, SEP))) {
                    p = p+strlen(SEP);
                    fprintf(fo,"%s\t", p);
                    myrec.score[i] = strtod(p,0);
                    ++i;
                }
            }
        }
        
        fclose(fp);
    }
    
    return i;
}

int getLabelFromFile( char * fn,  FILE * fo, char ** labels) {
    FILE* fp;
    char* p;
    char line[256];
    int i = 0;
    
    if((fp = fopen(fn,"r")) != NULL){
        for(int tag=0; fgets(line, 256, fp); ) {
            line[strlen(line)-1] = '\0';
            if ((p=strstr(line,START))) {
                tag = 1;
                p=strstr(line,SEP);
                *p = '\0';
                fprintf(fo,"%s\t",line);
                strcpy(labels[i], line);
                ++i;
            } else if ((p=strstr(line,END))) {
                tag = 0;
                p=strstr(line,SEP);
                *p = '\0';
                fprintf(fo,"%s\t description\n",line);
                strcpy(labels[i], line);
                strcpy(labels[i+1], "description");
                break;
            } else if(tag) {
                if ((p=strstr(line, SEP))) {
                    *p='\0';
                    fprintf(fo,"%s\t",line);
                    strcpy(labels[i], line);
                    ++i;
                }
            }
        }
        
        fclose(fp);
    }
    return i+1;
}

long int  getScoreFromDir( char * dn,  FILE * fo, record* myRec, char** label, size_t* dim) {
    DIR *dir;
    struct dirent* entry;
    char* p;
    char cwd[1024];
    long int i = 0;
    
    if (!(dir = opendir(dn)))
        return -1;
    if (!(entry = readdir(dir)))
        return -1;
    getcwd(cwd,sizeof(cwd));
    chdir(dn);
    
    do {
        if (entry->d_type == DT_DIR) {}
        else {
            //printf("%s\n",entry->d_name);
            if((p=strstr(entry->d_name,".pdb"))) {
                if(!i)
                    dim[0] = getLabelFromFile(entry->d_name, fo, label);
                getScoreFromFile(entry->d_name, fo, myRec[i]);
                ++i;
                printf("%ld\r",i);
                fflush(stdout);
            }
        }
    } while ((entry = readdir(dir)));
    closedir(dir);
    chdir(cwd);
    dim[1] = i;
    return i;
}

int cmp(const void* x,const  void* y) {
    record xx = *(record*)x;
    record yy = *(record*)y;
    if(xx.score[52] < yy.score[52]) return -1;
    if(xx.score[52] < yy.score[52]) return 1;
    return 0;
}
