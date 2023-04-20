PROJECT=ifj2020
FILES=string.c scanner.c parser.c symtable.c precedencni_analyza.c generator.c
CFLAGS=-std=c99
CC=gcc

all: $(PROJECT)
$(PROJECT): $(FILES)
	$(CC) $(CFLAGS) -o $(PROJECT) $(FILES) -lm

clear:
	rm ifj2020