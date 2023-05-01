all: patricia.o main.o
	g++ patricia.o main.o -g -o lab2

patricia.o: patricia.cpp
	g++ patricia.cpp -c -g

main.o: main.cpp
	g++ main.cpp -c -g

clean:
	rm -rf *.o lab2