CC=g++
FLAGS=-Wall -Wextra -Werror -pedantic -O2

all: ./build/main

./build/main: ./build/astar.o
	$(CC) ./build/astar.o -o ./build/main

./build/astar.o: ./src/astar.cpp
	$(CC) -c ./src/astar.cpp -o ./build/astar.o $(FLAGS)

clean:
	rm ./build/main *.o
