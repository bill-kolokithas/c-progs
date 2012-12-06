bin/ch19ex1: bin/ch19ex1.o bin/ch19ex1-queue.o
	gcc -Wall -o bin/ch19ex1 bin/ch19ex1.o bin/ch19ex1-queue.o

bin/ch19ex1.o: ch19ex1.c ch19ex1-queue.h
	gcc -Wall -o bin/ch19ex1.o -c ch19ex1.c 

bin/ch19ex1-queue.o: ch19ex1-queue.c ch19ex1-queue.h
	gcc -Wall -o bin/ch19ex1-queue.o -c ch19ex1-queue.c 