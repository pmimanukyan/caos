#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <limits.h>

struct Item
{
    struct Item* next;
    long long value;
};
struct Item* _Atomic head;

enum {
    TIDS_SIZE = 100,
    NUM = 1000
};

void* thread_func(void* smth) {
    int i = (intptr_t) smth;
    for (int j = 0; j < NUM; ++j) {
        struct Item* cur_node = calloc(1, sizeof(*cur_node));
        cur_node->value = NUM * i + j;
        cur_node->next = atomic_exchange_explicit(&head, cur_node, memory_order_relaxed);
        sched_yield();
    }
    return NULL;
}

void print_and_free() {
    while (head != NULL) {
        printf("%lld\n", head->value);
        struct Item* prev = head;
        head = head->next;
        free(prev);
    }
}

int main() {
    pthread_t tids[TIDS_SIZE];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);

    for (int i = 0; i < TIDS_SIZE; ++i) {
        pthread_create(&tids[i], &attr, thread_func, (void*)(intptr_t) i);
    }
    pthread_attr_destroy(&attr);
    for (int i = 0; i < TIDS_SIZE; ++i) {
        pthread_join(tids[i], NULL);
    }
    print_and_free();
}