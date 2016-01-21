all: server client select poll epoll
server:
	gcc -o server server.c
client:
	gcc -o client client.c
select:
	g++ -std=c++11 -o select select.cpp
poll:
	g++ -std=c++11 -o poll poll.cpp
epoll:
	g++ -std=c++11 -o epoll epoll.cpp
clean:
	rm -rf server client select poll epoll
