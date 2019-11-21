MAKE=gmake
CC=gcc
ARCH = `uname -s`
CFLAGS = -Wall -ggdb -O2 -D $(ARCH)
CLEAN = $(rm main.o symlink)


all	: 
	@echo "Building for $(ARCH)"
	make 	symlink

symlink	: main.o
	$(CC) -O2 -o symlink main.o


clean	:
	@rm -f main.o symlink 
