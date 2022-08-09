#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

enum { N = 10 };
pthread_t tids[N];

void* thread_func(void* smth) {
    int i = (intptr_t) smth;
    if (i > 0) {
        pthread_join(tids[i - 1], NULL);
    }
    printf("%d\n", i);
    return NULL;
}

int main() {
    for (int i = 0; i < N; ++i) {
        pthread_create(&tids[i], NULL, thread_func, (void*)(intptr_t) i);
    }
    pthread_join(tids[N - 1], NULL);
    return 0;
}