all: server_libevent server_libev cat
server_libevent:
	g++ -o server_libevent server_libevent.cpp -levent
server_libev:
	g++ -o server_libev server_libev.cpp -lev
cat:
	g++ -o cat cat.cpp -luv
clean:
	rm -rf server_libevent server_libev cat
