CC = gcc
program = main

all: ./main.c
	$(CC) -o $(program) ./main.c 

clean:
	rm -r /lib/*/*.o $(program)

run:
	$(CC) -o $(program) ./main.c
	./$(program)