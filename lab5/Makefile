all: bitmatrix_editor

bitmatrix_editor: bitmatrix_editor.o bitmatrix.o
	g++ -std=c++11 -o bitmatrix_editor bitmatrix_editor.o bitmatrix.o

bitmatrix_editor.o: bitmatrix_editor.cpp bitmatrix.h
	g++ -std=c++11 -c bitmatrix_editor.cpp

bitmatrix.o: bitmatrix.cpp bitmatrix.h
	g++ -std=c++11 -c bitmatrix.cpp
