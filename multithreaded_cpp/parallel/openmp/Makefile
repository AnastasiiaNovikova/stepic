all: hello loops barrier single
hello:
	g++ -o hello hello.cpp -lgomp -fopenmp
loops:
	g++ -o loops loops.cpp -lgomp -fopenmp
barrier:
	g++ -o barrier barrier.cpp -lgomp -fopenmp
single:
	g++ -o single single.cpp -lgomp -fopenmp
clean:
	rm -rf hello loops barrier single
