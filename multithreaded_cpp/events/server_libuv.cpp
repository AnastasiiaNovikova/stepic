#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

uv_tcp_t server;
uv_loop_t *loop;

void echo_read_cb(uv_stream_t *stream, ssize_t nread, const uv_buf_t* buf) {
    uv_write_t *req = (uv_write_t *)malloc(sizeof(uv_write_t));
    buf->base[nread] = 0;
    std::cout << buf->base << std::endl;
    uv_write(req, stream, buf, 1 , NULL);
    free(buf->base);
}

void alloc_buffer_cb(uv_handle_t *handle, size_t size, uv_buf_t* buf) {
    *buf = uv_buf_init((char *)malloc(size), size);
}

void on_new_connection_cb(uv_stream_t *server, int status) {
    if (status < 0) {
        std::cerr << "Error on connection" << std::endl;
    }

    uv_tcp_t *client = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, client);

    if(uv_accept(server, (uv_stream_t *)client) == 0) {
        uv_read_start((uv_stream_t *)client, alloc_buffer_cb, echo_read_cb);
    } else {
        uv_close((uv_handle_t *)client, NULL);
    }

}

int main(int argc, char **argv) {
    loop = uv_default_loop();
    
    struct sockaddr_in addr;
    uv_ip4_addr("0.0.0.0", 6666, &addr);
    
    uv_tcp_init(loop, &server);
    uv_tcp_bind(&server, (const struct sockaddr *)&addr, 0);
    uv_listen((uv_stream_t *)&server, 128, on_new_connection_cb);

    return uv_run(loop, UV_RUN_DEFAULT);
}
