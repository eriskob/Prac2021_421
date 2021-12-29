all:
	g++ -std=c++20 main.cpp factory.cpp graphs.cpp short_path.cpp tests.cpp -lgtest -pthread -o main -I /usr/local/include/gtest/
clean:
	rm -rf *.o