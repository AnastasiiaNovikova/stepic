#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <uv.h>
#include <string.h>

uv_loop_t *loop;
char *message;

void alloc_buffer_cb(uv_handle_t * handle, size_t size, uv_buf_t* buf) {
    *buf = uv_buf_init((char *)malloc(size), size);
}

void read_cb(uv_stream_t *stream, ssize_t nread, const uv_buf_t * buf) {
    uv_write_t *req = (uv_write_t *)malloc(sizeof(uv_write_t));
    std::cout << buf->base << std::endl;
    free(buf->base);
    uv_close((uv_handle_t *)stream, NULL);
}

void on_connect_cb(uv_connect_t* connect, int status) {
    uv_tcp_t * server = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));

    if(status < 0) {
        std::cerr << "Error on connect: " << 
            uv_strerror(status) << std::endl;
    }

    uv_write_t *req = (uv_write_t *)malloc(sizeof(uv_write_t));
    uv_buf_t buf = uv_buf_init((char*)malloc(strlen(message)+1), strlen(message)+1);
    strncpy(buf.base, message, strlen(message)+1);
    uv_write(req, (uv_stream_t*)server, &buf, 1, NULL);

    uv_read_start((uv_stream_t *)server, alloc_buffer_cb, read_cb);
}

int main(int argc, char**argv) {
    if(argc < 2)
        return -1;

    message = argv[1];

    loop = uv_default_loop();

    uv_tcp_t *socket = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, socket);

    uv_connect_t * connect = (uv_connect_t *)malloc(sizeof(uv_connect_t));
    
    struct sockaddr_in dest;
    uv_ip4_addr("127.0.0.1", 6666, &dest);

    uv_tcp_connect(connect, socket, (const sockaddr*)&dest, on_connect_cb);
}
