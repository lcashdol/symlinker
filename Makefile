MAKE=gmake
CC=gcc
CFLAGS = -Wall -ggdb -O2 


all	: 
	make 	symlink

symlink	: main.o
	$(CC) -O2 -o symlink main.o

