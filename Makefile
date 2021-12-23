CC=g++ -std=c++20
all: final clean

final: graphs.o factory.o main.o
	$(CC) -o graphs.o factory.o main.o -v

main.o: factory.h
	$(CC) -c main.cpp

factory.o: factory.cpp factory.h
	$(CC) -c factory.cpp

graphs.o: graphs.cpp graphs.h
	$(CC) -c graphs.cpp

clean:
	rm -rf *.o