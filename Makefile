all: clean
	g++ -std=c++98 -Wall main.cpp -o main.out
run:
	./main.out
clean:
	rm -rf main.out
