MAKE=gmake
CC=gcc
CFLAGS = -Wall -ggdb -O2 -D IRIX
CLEAN = $(rm main.o symlink)


all	: 
	make 	symlink

symlink	: main.o
	$(CC) -O2 -o symlink main.o


clean	:
	@rm main.o symlink 
