randmst: main.o edgeNPoints.o debug.o graph.o graphND.o myHeap.o MST.o
	g++ main.o edgeNPoints.o debug.o graph.o graphND.o myHeap.o MST.o -o randmst

main.o: main.cpp graph.h debug.h graphND.h MST.h
	g++ -c main.cpp
edgeNPoints.o: edgeNPoints.h edgeNPoints.cpp
	g++ -c edgeNPoints.cpp
debug.o: debug.cpp debug.h
	g++ -c debug.cpp
graph.o: graph.cpp debug.h edge.h graph.h
	g++ -c graph.cpp
graphND.o: graphND.h graphND.cpp edgeNPoints.h debug.h
	g++ -c graphND.cpp
myHeap.o: myHeap.cpp myHeap.h heapElement.h
	g++ -c myHeap.cpp
MST.o: MST.cpp edge.h edgeNPoints.h graph.h graphND.h myHeap.h MST.h
	g++ -c MST.cpp
clean:
	rm *.o randmst