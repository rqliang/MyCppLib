//
//  myFilter.h
//  myFiltering
//
//  Created by Ruqiang Liang on 9/7/16.
//  Copyright © 2016 Ruqiang Liang. All rights reserved.
//

#ifndef myFilter_h
#define myFilter_h

typedef struct{
    char name[60];
    float scores[60];
} myRecord;

int getIndex(char** labels, const char* name);
int comp_increase(const void * x, const void * y);
int comp_decrease(const void * x, const void * y);

#endif /* myFilter_h */
