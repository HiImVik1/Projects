My netID: vk414

I worked without a partner

Test plan:
The file memgrind.c has all the programs used to test mymalloc. 
The size of the memory array, MEMLENGTH, is set in mymalloc.h the header file. 

First there is a correctness testing program, memtest (made using the provided one on Canvas) that allocates the entire memory array into equally sized blocks and then fills the memory blocks with data objects. Then it checks to make sure there are no data errors. It prints how many errors there are, and should print 0. The number of objects, header size, and therefore object size is set by defined variables outside the function.

The second correctness testing program is getErrors. As the name suggests, the program makes sure that mymalloc outputs the right error messages given a specific incorrect input. This includes the 3 mandatory errors outlined in the project file, as well as some others. Both of these tests are run once in main on memgrind. 6 total errors should output.

Next are the performance tests. First, test1 allocates 1 byte of memory and releases it right after. This is done 32 times. The program returns the time taken to run it. In main of memgrind, a for loop runs this 50 times and prints the average time of 1 run. All tests after test1 are run the same way in main: run 50 times, then the average time taken is printed out. test1, like all subsequent tests returns the time it took to run it as a double. test1 tests how good the program is at immediate allocations and deallocations.

Next, test2 allocates 1 byte of memory at 120 consecutive locations and then frees them all. This tests performance with consecutive allocations and frees. 

Next, test3 120 times randomly either allocates a new byte of memory or deallocates an already allocated byte of memory. This tests how the memory management system handles more random, and potentially more realistic and complex sequences of allocation and deallocation.

After that, test4 allocates the full length of the memory array to one object, and then frees it 120 times. This tests how the memory management system handles very large allocations and deallocations (in this case, the largest possible).

Lastly, test5 allocates various memory blocks of different sizes and then frees all of them, looping this 120 times. This tests how the memory management system handles increasingly large yet chainging memory size allocations and frees. 

Thank you!! 


