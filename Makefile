CC = gcc
program = main

all: ./main.c ./lib/skip_list/skip_list.c ./lib/skip_list/skip_list.h
	$(CC) -o $(program) ./main.c ./lib/skip_list/skip_list.c

clean:
	rm -r /lib/*/*.o $(program)

run:
	$(CC) -o $(program) ./main.c ./lib/skip_list/skip_list.c
	./$(program)