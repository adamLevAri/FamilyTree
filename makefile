#!make -f

test: badkan.o familyTree.o node.o
	g++ $^ -o test

demo: Demo.o familyTree.o node.o
	g++ $^ -o test

%.o: %.cpp
	g++ -c $< -o $@

node.o: node.cpp node.h
	g++ -c node.cpp

familyTree.o: familyTree.cpp familyTree.h
	g++ -c familyTree.cpp

Demo.o: Demo.cpp Demo.h
	g++ -c Demo.cpp

badkan.o: badkan.cpp badkan.h
	g++ -c badkan.cpp

clean:
	rm -f *.o demo test