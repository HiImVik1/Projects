/*
Vikram Kadyan's mymalloc.h
*/

//guard definition
#ifndef  MALLOC_H_
#define MALLOC_H_
#define MEMLENGTH 4096

#include <stdlib.h>
#include <stdio.h>


//redefine malloc and free to our version
#define malloc(s) mymalloc(s, __FILE__, __LINE__)
#define free(p) myfree(p, __FILE__, __LINE__)


void* mymalloc(size_t, char*, int);

void myfree(void*, char*, int);


typedef struct{
    int alloc;
    int size; 
}header;

int memClear();

header* nextHeader();

header* lastHeader();


#endif

