CC=gcc
CFLAGS=-O3 -lm
OUTPUT=generate_load

all:
	$(CC) $(CFLAGS) -o $(OUTPUT) generate_load.c

generate_load:
	$(CC) $(CFLAGS) -o $(OUTPUT) generate_load.c

clean:
	rm $(OUTPUT)
