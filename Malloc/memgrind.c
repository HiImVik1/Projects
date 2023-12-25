/* 
Vikram Kadyan
memgrind    .C

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "mymalloc.h"


#define HEADERSIZE 8
#define OBJECTS 8


void memtest (){

    double OBJSIZE = MEMLENGTH -(OBJECTS*HEADERSIZE);
   
    OBJSIZE = OBJSIZE/OBJECTS;

    char *obj[OBJECTS];
    int i = 0;
    int j = 0;
    int errors = 0;
    
   
    for (i = 0; i < OBJECTS; i++) {
       // printf("tally");
        obj[i] = malloc(OBJSIZE);
        }
    for (i = 0; i < OBJECTS; i++) {
        memset(obj[i], i, OBJSIZE);
        }

    for (i = 0; i < OBJECTS; i++) {
        for (j = 0; j < OBJSIZE; j++) {
            if (obj[i][j] != i) {
                errors++;
                printf("Object %d byte %d incorrect: %d\n", i, j, obj[i][j]);
            }
         }
    }
       
        printf("%d incorrect bytes\n", errors);
        
        for (i = 0; i < OBJECTS; i++) {
        
            char *a= obj[i];
        free(a);
        }

       // printf("Is MemClear?: %d\n", memClear());
return;
}

void getErrors(){
    //tests 
    int* e1 = malloc(0);
  //  printf("Is MemClear?: %d\n\n", memClear());
    int* e2 = malloc(100000);
   // printf("Is MemClear?: %d\n\n", memClear());
    int* e4 = NULL;
    free (e4);
    int e5;
    free(&e5);
    int* e6 = malloc(sizeof(int));
    free(e6+1);
    free(e6);
    //printf("Is MemClear?: %d\n\n", memClear());
    int* e7 = malloc(sizeof(int));
    int* e8 = e7;
    free(e7);
    free(e8);

   //printf("Is MemClear?: %d\n", memClear());


}

double test1() {

struct timeval start, end;
double etime;

gettimeofday(&start,NULL);

    for(int i = 0; i < 120; i++) {
        char *ptr = malloc(1);  // Allocate 1 byte of memory
        free(ptr);  // Release the memory
   }
   //printf("Is MemClear?: %d\n", memClear());  // Check if memory is cleared
    
    gettimeofday(&end,NULL);
    etime = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
    //printf("Time taken to complete test 1: %f seconds \n",etime);
    return etime;
}

double test2() {
    struct timeval start, end;
    double etime;

    gettimeofday(&start,NULL);
    char *ptrArray[120];  // Array to store 120 pointers

    for(int i = 0; i < 120; i++) {
        ptrArray[i] = malloc(1);  // Allocate 1 byte of memory and store the address
    }

    for(int i = 0; i < 120; i++) {
        free(ptrArray[i]);  // Release the memory
    }

   // printf("Is MemClear?: %d\n", memClear());  // Check if memory is cleared
    gettimeofday(&end,NULL);
    etime = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
    //printf("Time taken to complete test 2: %f seconds \n",etime);
    return(etime);

}

double test3() {
    struct timeval start, end;
    double etime;
    gettimeofday(&start,NULL);
    char *ptrArray[120];  
    int allocated[120] = {0}; 
    int loc = 0;  

    for(int i = 0; i < 120; i++) {
        if(loc == 0 || (rand() % 2 == 0 && loc < 120)) {
            
         //   printf("alloc loc=%d\n", loc);
            ptrArray[loc] = malloc(1);
            allocated[loc] = 1;
            loc++;
        } else {
            
            loc--;
         //   printf("free loc=%d\n", loc);
            free(ptrArray[loc]);
            allocated[loc] = 0;
        }
    }

  //  printf("Process is done.\n");

    for(int i = 0; i < 120; i++) {
        if(allocated[i] == 1) {
            free(ptrArray[i]);
        }
    }

 //  printf("Is MemClear?: %d\n", memClear());  
    gettimeofday(&end,NULL);
    etime = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
   // printf("Time taken to complete test 3: %f seconds \n",etime);
   return etime;

}

double test4(){
    struct timeval start, end;
    double etime;
    gettimeofday(&start,NULL);

    for (int i = 0; i<120; i++){
        long* a = malloc(MEMLENGTH-HEADERSIZE);
        free(a);
    }
    gettimeofday(&end,NULL);
    etime = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
   //printf("Time taken to complete test 4: %f seconds \n",etime);
   return etime;
}

double test5(){
    struct timeval start, end;
    double etime;
    gettimeofday(&start,NULL);
    for (int i = 0; i<120; i++){
        int* a = malloc(8);
        int* b = malloc(64);
        int* c = malloc (16);
        int* d = malloc (128);

        free(a);
        free(b);
        free(c);
        free(d);

    }


    gettimeofday(&end,NULL);
    etime = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
   //printf("Time taken to complete test 5: %f seconds \n",etime);
   return etime;
}


int main (void){

    
    memtest();
    getErrors();

/*
    double a = test1();
    double b = test2();
    double c = test3();
    double d = test4();
*/


    double t1total;
    for (int i = 0; i<50; i++){
        double a = test1();
        t1total += a;
    }
    double t1avg = t1total/50;
    printf("Average time taken to complete test 1 over 50 runs: %f seconds \n", t1avg);
     

    double t2total;
    for (int i = 0; i<50; i++){
        double a = test2();
        t2total += a;
    }
    double t2avg = t2total/50;
    printf("Average time taken to complete test 2 over 50 runs: %f seconds \n", t2avg);
    
    double t3total;
    for (int i = 0; i<50; i++){
        double a = test3();
        t3total += a;
    }
    double t3avg = t3total/50;
    printf("Average time taken to complete test 3 over 50 runs: %f seconds \n", t3avg);
   
    double t4total;
    for (int i = 0; i<50; i++){
        double a = test4();
        t4total += a;
    }
    double t4avg = t4total/50;
    printf("Average time taken to complete test 4 over 50 runs: %f seconds \n", t4avg);
    

    double t5total;
    for (int i = 0; i<50; i++){
        double a = test5();
        t5total += a;
    }
    double t5avg = t5total/50;
    printf("Average time taken to complete test 5 over 50 runs: %f seconds \n", t5avg);
  
    return 0;
    
}