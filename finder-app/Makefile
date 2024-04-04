CC=	gcc
FILE= ./writer.c
FLAGS= -g -Wall
OUTPUT= writer

# Cross compilation
CROSS_COMPILER= ../../gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-
ifdef CROSS_COMPILE
CC= $(CROSS_COMPILER)gcc
endif

all:
	$(CC) $(FLAGS) $(FILE) -c -o $(OUTPUT).o
	$(CC) $(FLAGS) -I/ $(OUTPUT).o -o $(OUTPUT)

.PHONY: clean

clean:
	@rm -f *.o $(OUTPUT) *.elf *.map

