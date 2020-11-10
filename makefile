all: main.cpp Lists.cpp main_pointer.cpp Lists_pointer.cpp
	g++ main.cpp Lists.cpp -o list
	g++ main_pointer.cpp Lists_pointer.cpp -o list_p

pointer: main_pointer.cpp Lists_pointer.cpp
	g++ main_pointer.cpp Lists_pointer.cpp -o list_p

array: main.cpp Lists.cpp
	g++ main.cpp Lists.cpp -o list
clean:
	rm "graph_array.jpeg"
	rm "graph_log.dot"
	rm "graph_log.jpeg"
	rm "graph_phys.dot"
	rm "graph_phys.jpeg"
	rm "graph_pointer.dot"
	rm "graph_pointer.jpeg"
	rm "graph.dot"
	rm "graph.jpeg"
