all: server_libevent server_libev server_libuv client_libuv server_boost_asio cat
server_libevent:
	g++ -o server_libevent server_libevent.cpp -levent
server_libev:
	g++ -o server_libev server_libev.cpp -lev
server_libuv:
	g++ -o server_libuv server_libuv.cpp -luv
client_libuv:
	g++ -o client_libuv client_libuv.cpp -luv
cat:
	g++ -o cat cat.cpp -luv
server_boost_asio:
	g++ -o server_boost_asio server_boost_asio.cpp -lboost_system
clean:
	rm -rf server_libevent server_libev server_libuv client_libuv cat server_boost_asio
