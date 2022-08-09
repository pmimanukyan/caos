#include <stdio.h>
#include <pthread.h>

void* thread_func(void* smth) {
    int number;
    if (scanf("%d", &number) != 1) {
        return NULL;
    }
    pthread_t t;
    pthread_create(&t, NULL, thread_func, NULL);
    pthread_join(t, NULL);
    printf("%d\n", number);
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, NULL);
    pthread_join(tid, NULL);
}