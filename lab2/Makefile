all: patricia.o main.o
	g++ patricia.o main.o -o lab2

patricia.o: patricia.cpp
	g++ patricia.cpp -c

main.o: main.cpp
	g++ main.cpp -c

clean:
	rm -rf *.o lab2