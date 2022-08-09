#include <stdio.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

int64_t generate_or_fail(size_t i);

int64_t* parallel_populate(size_t N) {
    size_t input_size = N * sizeof(int64_t);
    void *mp = mmap(NULL, input_size, PROT_WRITE | PROT_READ, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (mp == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }

    int64_t* data = mp;
    int status;
    for (size_t i = 0; i < N; ++i) {
        pid_t pid = fork();
        if (pid == -1) {
            return NULL;
        } else if (pid == 0) {
            data[i] = generate_or_fail(i);
            _exit(0);
        } else {
            waitpid(pid, &status, 0);
            if (WEXITSTATUS(status) == 13) {
                data[i] = -1;
            }
        }
    }
    return data;
}