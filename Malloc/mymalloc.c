/* 
Vikram Kadyan
mymalloc

*/

#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"


static double memory[MEMLENGTH];


/*
typedef struct{
    int size; 
    int alloc;
}header;
*/

header* nextHeader(header* rn){
    char* ph = (char*) rn;
    ph = ph + rn->size + sizeof(header);
    return (header*)ph;
}


void *mymalloc(size_t size, char *file, int line){
    header* data = (header*) memory;
    
    if (size ==0 ){
        printf("Error: cannot allocate 0 bytes.File: %s, Line: %d \n", file, line);
        return NULL;
    }

    size = (size + 7) &~7; size = (size + 7) &~7;

    size_t total = size + sizeof(header);
    

    if (total> MEMLENGTH ){
        printf ("Error: Not enough memory. File: %s, Line: %d \n", file, line);
        return NULL;
    }
    
     //printf("alloc:%d\n", data->alloc);
    // printf("data: %d\n", data->size);
    

    if(data->alloc== 0 && data->size == 0 ){
        //printf("in branch\n");
        data->alloc == 0;
        data->size= MEMLENGTH - sizeof(header);
    }

    header* rn = data; 

    while ((char*)rn < (char*)&memory[MEMLENGTH]){
       
        if (rn->alloc ==0 && rn->size >= size){
            rn->alloc= 1;
            int diff= rn->size - size;
            rn->size= size;
            char* res= (char*)rn + sizeof(header) + size;
        if (diff<=sizeof(header)){
            rn->size += diff;
        }else if ((double*)res + sizeof(header)<&memory[MEMLENGTH]){
            header* ptr = (header*)res;
            ptr ->size= diff-sizeof(header);
            ptr->alloc = 0;
        }else{
            rn->size += diff;
            }
        res =(char*)rn+sizeof(header);
        return (void*)res;
        }else{
        rn = nextHeader(rn);
            }
    }
    printf("Error: Not enough remaining memory. File: %s, Line: %d \n", file, line);
    return NULL;

}

header* lastHeader(header* rn){
    header* last;
    header* ph = (header*)memory;
    while (ph != rn){
        last = ph;
        ph = nextHeader(ph);
    }
    return last;
}


void myfree(void *ptr, char *file, int line){
    
    char* start = (char*)ptr- sizeof(header);
    header* rn = (header*) start;
    
    if (ptr == NULL){
        printf("Error: Pointer is NULL. File: %s, Line: %d \n", file, line);
        return;
    }

    if((char*)rn<start || (char*)rn> start + MEMLENGTH){
        printf("Error: Invalid memory pointer, not allocated with malloc. File: %s, Line: %d \n", file, line);
        return;
    }

    if (rn-> alloc == 0){
        printf("Error: Attempted free on unallocated or previously freed memory. File: %s, Line: %d \n", file, line);
        return;
    }

    if (rn->alloc != 1){
        printf("Error: Attempted free within working memory- Pointer not at start of chunk.File: %s, Line: %d \n", file, line);
        return;
    }

    header* last;
    header* next;
    if ((double*)rn ==memory){
        next=nextHeader(rn);
        if ((double*)next> &memory[MEMLENGTH-1]){
                rn->alloc = 0;
        }else if (next->alloc == 0){
            rn->size +=sizeof(header)+next->size;
            rn->alloc = 0;
        }else{
            rn->alloc = 0;
        }
        return;
    }

    if ((double*)rn +sizeof(header)+ rn->size ==&memory[MEMLENGTH]){
        last = lastHeader(rn);
        if  (last->alloc == 0){
            last->size +=sizeof(header)+ rn->size;
        }else{
            rn->alloc=0;
        }
        return;
    }
    next = nextHeader(rn);
    last = lastHeader(rn);

    if (last->alloc == 0){
        int a = last->size +rn->size +sizeof(header);
        last->size = a;
        if (next->alloc==0){
            int b = last->size + next->size +sizeof(header);
            last->size = b;
        }
        return;

    }

    if (next->alloc==0){
        int a = rn->size + next->size +sizeof(header);
        rn->size = a;
        rn->alloc=0;
        return;
    }
    rn->alloc = 0;
    return;
}


//returns 1 if mem is clear, 0 if not
int memClear() {
    header* start =(header*) &memory;
    int chunkSize = start->size;
    // printf("%d", chunkSize);

    // If Memory pool is uninitialized or fully cleared
    if ( chunkSize == 0 && start->alloc==0 ) {
        return 1;
    } 
    if (chunkSize == MEMLENGTH-8 && start->alloc == 0){
        return 1;
    }

        return 0;
}