CC=g++
FLAGS=-Wall -Wextra -Werror -pedantic -O2

all: ./build/main

./build/main: ./build/example.o
	$(CC) ./build/example.o -o ./build/main

./build/example.o: ./src/example.cpp
	$(CC) -c ./src/example.cpp -o ./build/example.o $(FLAGS)

clean:
	rm ./build/main *.o
