#include <stdio.h>
#include <pthread.h>
#include <stdint.h>

pthread_mutex_t mutex;
pthread_cond_t cond_var;

unsigned long long base = 0;
int count = 0;

unsigned long long prime_number = 0;
int found = 0;

int is_prime(unsigned long long number) {
    if (number <= 1) {
        return 0;
    } else if (number == 2) {
        return 1;
    } else {
        for (unsigned long long i = 2; i * i <= number; ++i) {
            if (number % i == 0) {
                return 0;
            }
        }
    }
    return 1;
}

void* thread_func(void* smth) {
    for (unsigned long long i = base; i < UINT64_MAX; ++i) {
        if (is_prime(i)) {
            pthread_mutex_lock(&mutex);
            prime_number = i;
            found = 1;
            pthread_cond_signal(&cond_var);
            if (count == 0) {
                pthread_mutex_unlock(&mutex);
                return NULL;
            }
            pthread_mutex_unlock(&mutex);
        }
    }
    return NULL;
}


int main() {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_var, NULL);

    if (scanf("%llu %d", &base, &count) != 2) {
        perror("scanf");
        return 1;
    }

    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, NULL);

    while (1) {
        pthread_mutex_lock(&mutex);
        while (found == 0) {
            pthread_cond_wait(&cond_var, &mutex);
        }
        found = 0;
        count -= 1;
        unsigned long long prime_number_cpy = prime_number;
        pthread_mutex_unlock(&mutex);
        printf("%llu\n", prime_number_cpy);
        if (count == 0) {
            break;
        }
    }


    pthread_join(tid, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_var);
}