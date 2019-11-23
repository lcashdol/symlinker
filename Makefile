MAKE=gmake
CC=gcc
CFLAGS = -Wall -ggdb -O2
CLEAN = $(rm main.o symlink)


all	: 
	make 	symlink

symlink	: main.o
	$(CC) -O2 -o symlink main.o


clean	:
	@rm -f main.o symlink 
