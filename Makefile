CC = gcc
CFLAGS = -g -Wall

default: lab3

lab3: command.o main.o
	$(CC) $(CFLAGS) -o lab3 command.o main.o

command.o: command.c command.h
	$(CC) $(CFLAGS) -c command.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean: 
	$(RM) lab3 log.txt output.txt *.o *~

val-interactive: lab3
	valgrind --leak-check=full --tool=memcheck ./lab3 > log.txt 2>&1

val-file: lab3
	valgrind --leak-check=full --tool=memcheck ./lab3 -f input.txt > log.txt 2>&1
