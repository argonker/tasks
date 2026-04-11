all: test

matrix_test: main.o matrices.o
	g++ main.o matrices.o -o matrix_test

main.o: main.cpp matrices.h
	g++ -Wall -Wextra -std=c++23 -g -c main.cpp -o main.o

matrices.o: matrices.cpp matrices.h
	g++ -Wall -Wextra -std=c++23 -g -c matrices.cpp -o matrices.o

test: matrix_test
	./matrix_test
clean:
	rm -f main.o matrices.o matrix_test