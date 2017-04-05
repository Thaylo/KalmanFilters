all:
	g++-5 -std=c++17 -O3 *.cpp -o example
clean:
	rm example