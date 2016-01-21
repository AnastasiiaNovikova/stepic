all: server client select poll
server:
	gcc -o server server.c
client:
	gcc -o client client.c
select:
	g++ -std=c++11 -o select select.cpp
poll:
	g++ -std=c++11 -o poll poll.cpp
clean:
	rm -rf server client select poll
