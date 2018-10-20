all: candyCrushTest

candyCrushTest: candyCrushTest.o candyCrush.o
	g++ -g -std=c++11 -o candyCrushTest candyCrushTest.o candyCrush.o

candyCrushTest.o: candyCrushTest.cpp candyCrush.h
	g++ -g -std=c++11 -c candyCrushTest.cpp 

candyCrush.o: candyCrush.cpp candyCrush.h
	g++ -g -std=c++11 -c candyCrush.cpp

clean:
	gvfs-trash --force candyCrush.o candyCrushTest.o
