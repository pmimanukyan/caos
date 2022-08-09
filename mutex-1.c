#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

enum {
    N = 3,
    ITERATIONS = 1000000
};

double a[N];
pthread_mutex_t mutex;

void* thread_func(void* smth) {
    int i = (intptr_t) smth;
    for (int iter = 0; iter < ITERATIONS; ++iter) {
        pthread_mutex_lock(&mutex);
        if (i == 0) {
            a[0] += 100;
            a[1] -= 101;
        } else if (i == 1) {
            a[1] += 200;
            a[2] -= 201;
        } else {
            a[2] += 300;
            a[0] -= 301;
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t tids[N];
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < N; ++i) {
        pthread_create(&tids[i], NULL, thread_func, (void*)(intptr_t) i);
    }
    for (int i = 0; i < N; ++i) {
        pthread_join(tids[i], NULL);
    }
    for (int i = 0; i < N; ++i) {
        printf("%.10g\n", a[i]);
    }
    pthread_mutex_destroy(&mutex);
}