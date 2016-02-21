all: hello loops barrier single ordered critical
hello:
	g++ -o hello hello.cpp -lgomp -fopenmp
loops:
	g++ -o loops loops.cpp -lgomp -fopenmp
barrier:
	g++ -o barrier barrier.cpp -lgomp -fopenmp
single:
	g++ -o single single.cpp -lgomp -fopenmp
ordered:
	g++ -o ordered ordered.cpp -lgomp -fopenmp
critical:
	g++ -o critical critical.cpp -lgomp -fopenmp
clean:
	rm -rf hello loops barrier single ordered
