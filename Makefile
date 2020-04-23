CC = gcc
CFLAGS = -g -Wall

default: pseudo-shell

pseudo-shell: command.o main.o
	$(CC) $(CFLAGS) -o pseudo-shell command.o main.o

command.o: command.c command.h
	$(CC) $(CFLAGS) -c command.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	$(RM) pseudo-shell log.txt output.txt *.o *~

val-interactive: pseudo-shell
	valgrind --leak-check=full --tool=memcheck ./pseudo-shell > log.txt 2>&1

val-file: pseudo-shell
	valgrind --leak-check=full --tool=memcheck ./pseudo-shell -f input.txt > log.txt 2>&1
