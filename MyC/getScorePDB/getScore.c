//
//  getScore.c
//  getScorePDB
//
//  Created by Ruqiang Liang on 9/2/16.
//  Copyright © 2016 Ruqiang Liang. All rights reserved.
//

#include "getScore.h"
#include <string.h>

void getScoreFromFile(char * fn, const FILE * fo)
{
    FILE* fp;
    char* p;
    char line[256];
    int tag = 0;
    
    if((fp = fopen(fn,"r")) != NULL){
        while(fgets(line, 256, fp)) {
            line[strlen(line)-1] = '\0';
            if ((p=strstr(line,START))) {
                tag = 1;
                fprintf(fo,"%s\t",p+strlen(START)+1);
            } else if ((p=strstr(line,END))) {
                tag = 0;
                fn[strlen(fn)-4] = '\0';
                fprintf(fo,"%s\t%s\n",p+strlen(END)+1,fn);
                break;
            } else if(tag) {
                if ((p=strstr(line, SEP))) {
                    fprintf(fo,"%s\t",p+strlen(SEP));}
            }
        }
        
        fclose(fp);
    }
    
}

void getLabelFromFile(const char * fn, const FILE * fo) {
    FILE* fp;
    char* p;
    char line[256];
    int tag = 0;
    
    if((fp = fopen(fn,"r")) != NULL){
        while(fgets(line, 256, fp)) {
            line[strlen(line)-1] = '\0';
            if ((p=strstr(line,START))) {
                tag = 1;
                p=strstr(line,SEP);
                *p = '\0';
                fprintf(fo,"%s\t",line);
            } else if ((p=strstr(line,END))) {
                tag = 0;
                p=strstr(line,SEP);
                *p = '\0';
                fprintf(fo,"%s\t description\n",line);
                break;
            } else if(tag) {
                if ((p=strstr(line, SEP))) {
                    *p='\0';
                    fprintf(fo,"%s\t",line);}
            }
        }
        
        fclose(fp);
    }
    
}

void getScoreFromDir(const char * dn, const FILE * fo) {
    DIR *dir;
    struct dirent* entry;
    char* p;
    char cwd[1024];
    int i = 0;
    
    if (!(dir = opendir(dn)))
        return;
    if (!(entry = readdir(dir)))
        return;
    getcwd(cwd,sizeof(cwd));
    chdir(dn);
    do {
        if (entry->d_type == DT_DIR) {}
        else {
            //printf("%s\n",entry->d_name);
            if((p=strstr(entry->d_name,".pdb"))) {
                if(!i)
                    getLabelFromFile(entry->d_name, fo);
                getScoreFromFile(entry->d_name, fo);
                ++i;
            }
        }
    } while ((entry = readdir(dir)));
    closedir(dir);
    chdir(cwd);
}