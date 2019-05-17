CC=gcc
CFLAGS=-O3
OUTPUT=generate_load

all:
	$(CC) -o $(OUTPUT) generate_load.c

generate_load:
	$(CC) -o $(OUTPUT) generate_load.c

clean:
	rm $(OUTPUT)
