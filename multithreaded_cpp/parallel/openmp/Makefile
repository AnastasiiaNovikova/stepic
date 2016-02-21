all: hello loops barrier
hello:
	g++ -o hello hello.cpp -lgomp -fopenmp
loops:
	g++ -o loops loops.cpp -lgomp -fopenmp
barrier:
	g++ -o barrier barrier.cpp -lgomp -fopenmp
clean:
	rm -rf hello loops barrier
