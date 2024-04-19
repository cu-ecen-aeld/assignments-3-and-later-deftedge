CC= gcc
FILE= ./aesdsocket.c
FLAGS= -g -Wall -Werror
OUTPUT= aesdsocket

# Cross compilation
CROSS_COMPILER= aarch64-none-linux-gnu-
ifdef CROSS_COMPILE
CC= $(CROSS_COMPILER)gcc
endif

all:
	$(CC) $(FLAGS) $(FILE) -c -o $(OUTPUT).o
	$(CC) $(FLAGS) -I/ $(OUTPUT).o -o $(OUTPUT)

.PHONY: clean

clean:
	@rm -f *.o $(OUTPUT) *.elf *.map
