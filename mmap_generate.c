#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <math.h>


int main(int argc, char *argv[]) {
    if (argc < 2) {
//        fprintf(stderr, "expected filename\n");
//        exit(1);
    }
    int fd = open(argv[1], O_RDWR | O_CREAT, 0600);
    int rows = atoi(argv[2]);
    int cols = atoi(argv[3]);
    if (fd < 0) {
        return 1;
    }
    int res = ftruncate(fd, rows * cols * (int)sizeof(double));
    if (res != 0) {
        return 1;
    }
    size_t size = rows * cols * sizeof(double);
    double *data = (double *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (data == MAP_FAILED) {
        return 1;
    }
    for (int i = 0; i < rows; i = i + 1) {
        for (int j = 0; j < cols; ++j) {
            data[i * cols + j] = (double)(2 * sin((double)i) + 4 * cos((double)j / 2));
            printf("%f\n", data[i * cols + j]);
        }
    }
}