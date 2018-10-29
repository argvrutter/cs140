all: cp_tester

cp_tester: cp_tester.o code_processor.o double_checker.o
	g++ -std=c++11 -o cp_tester cp_tester.o code_processor.o double_checker.o

cp_tester.o: cp_tester.cpp code_processor.h
	g++ -std=c++11 -c cp_tester.cpp

code_processor.o: code_processor.cpp code_processor.h
	g++ -std=c++11 -c code_processor.cpp

double_checker.o: double_checker.cpp code_processor.h
	g++ -std=c++11 -c double_checker.cpp

