#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "expected filename\n");
        return 1;
    }
    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0600);
    if (fd < 0) {
        return 1;
    }

    size_t rows = atoll(argv[2]);
    size_t cols = atoll(argv[3]);

    int input_size = (int)sizeof(int) * rows * cols;
    if (ftruncate(fd, input_size) == -1) {
        perror("error");
        exit(1);
    }
    void *mp = mmap(NULL, input_size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    if (mp == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }
    int *data = mp;

    size_t cols_copy = cols;
    int index = 0;
    size_t i = 0;
    size_t j = 0;
    while (i < rows && j < cols) {
        for (size_t x = j; x < cols; ++x) {
            data[i * cols_copy + x] = ++index;
        }
        ++i;

        for (size_t x = i; x < rows; ++x) {
            data[x * cols_copy + cols - 1] = ++index;
        }
        --cols;

        if (i < rows) {
            for (size_t x = cols - 1; x + 1 > j; --x) {
                data[(rows - 1) * cols_copy + x] = ++index;
            }
            --rows;
        }

        if (j < cols) {
            for (size_t x = rows - 1; x + 1 > i; --x) {
                data[x * cols_copy + j] = ++index;
            }
            ++j;
        }
    }

    if (munmap(mp, input_size) == -1) {
        perror("error");
        exit(1);
    }

    if (close(fd) == -1) {
        perror("error");
        exit(1);
    }
}
