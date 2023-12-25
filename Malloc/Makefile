all: mymalloc.o
	@gcc -g -o memgrind memgrind.c mymalloc.o

mymalloc.o: mymalloc.c
	@gcc -g -o mymalloc.o -c mymalloc.c

clean:
	@echo "Removed files"
	@rm *.o ./memgrind
