#include <iostream>
#include <stdlib.h>
#include <uv.h>

uv_fs_t open_req;
uv_fs_t read_req;
uv_fs_t close_req;
uv_fs_t write_req;

uv_buf_t iov;

char buffer[1024];

void on_read(uv_fs_t * req);
void on_open(uv_fs_t * req);
void on_write(uv_fs_t * req);

void on_write(uv_fs_t *req)
{
    if(req->result >= 0) {
        uv_fs_read(uv_default_loop(), &read_req,
                open_req.result, &iov, 1,-1, on_read);
    } else {
        std::cerr << "Error" << std::endl;
    }
}

void on_open(uv_fs_t * req) {
    if(req->result>=0) {
        iov = uv_buf_init( buffer, sizeof(buffer));
        uv_fs_read(uv_default_loop(), &read_req,
                req->result, &iov, 1, -1, on_read);
    } else {
        std::cout << "Error" << std::endl;
    }
}

void on_read(uv_fs_t * req) {
    if(req->result<0) {
    } else if (req->result==0) {
        uv_fs_close(uv_default_loop(), &close_req,
                open_req.result, NULL);
    } else {
        iov.len = req->result;
        uv_fs_write(uv_default_loop(), &write_req, 1, &iov,
                1, -1, on_write);
    }
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "Usage: cat filename" << std::endl;
        return -1;
    }

    uv_fs_open(uv_default_loop(), &open_req, argv[1],
            O_RDONLY, 0, on_open);

    uv_run(uv_default_loop(), UV_RUN_DEFAULT);

    uv_fs_req_cleanup(&open_req);
    uv_fs_req_cleanup(&read_req);
    uv_fs_req_cleanup(&write_req);
    uv_fs_req_cleanup(&close_req);
}
