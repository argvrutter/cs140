all: hash_test

hash_test: hash_test.o hash140.o
	g++ -std=c++11 -g -o hash_test hash_test.o hash140.o

hash_test.o: hash_test.cpp hash140.h
	g++ -std=c++11 -g -c hash_test.cpp

hash140.o: hash140.cpp hash140.h
	g++ -std=c++11 -g -c hash140.cpp
