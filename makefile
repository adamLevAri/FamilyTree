#!make -f

CFLAGS=-stdlib=libc++ -std=c++11

demo: Demo.o familyTree.o node.o
	g++ $(CFLAGS) $^ -o demo

test: badkan.o familyTree.o node.o
	g++ $(CFLAGS) $^ -o test

%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@
	

node.o: node.cpp node.h

familyTree.o: familyTree.cpp familyTree.h

Demo.o: Demo.cpp Demo.h

badkan.o: badkan.cpp badkan.h

clean:
	rm -f *.o demo test
