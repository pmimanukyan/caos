#include <unistd.h>

enum { BUF_SIZE = 4096 };

struct FileWriteState
{
    int fd;
    unsigned char *buf;
    int buf_size;
    int buf_cur_size;
};
static unsigned char buf[BUF_SIZE];
static struct FileWriteState fws = {
        1,
        buf,
        BUF_SIZE,
        0,
};

struct FileWriteState *stout = &fws;


void flush(struct FileWriteState *out) {
    ssize_t buf_size = out->buf_cur_size;
    ssize_t i = 0;
    ssize_t k; // in bytes
    /* write returning -1 otherwise(when can't write) */
    while (buf_size != 0 && (k = write(out->fd, out->buf + i, buf_size)) > 0) {
        i += k;
        buf_size -= k;
    }
    out->buf_cur_size = 0;
}

void writechar(int c, struct FileWriteState *out) {
    out->buf[out->buf_cur_size] = c;
    ++out->buf_cur_size;
    if (out->buf_cur_size == out->buf_size) {
        flush(out);
    }
}