all: main.cpp Lists.cpp main_pointer.cpp Lists_pointer.cpp
	g++ main.cpp Lists.cpp -o list
	g++ main_pointer.cpp Lists_pointer.cpp -o list_p

pointer: main_pointer.cpp Lists_pointer.cpp
	g++ main_pointer.cpp Lists_pointer.cpp -o list_p

array: main.cpp Lists.cpp
	g++ main.cpp Lists.cpp -o list