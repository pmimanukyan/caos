#include <sys/syscall.h>
#include <stdint.h>

uint64_t rdtsc() {
    uint64_t x;
    uint64_t y;
    asm volatile ("mov $1, %%eax\n\t"
                  "rdtsc\n\t"
                  "mov %%eax, %0\n\t"
                  "mov %%edx, %1\n\t"
                  : "=m"(x), "=m"(y)
                  :
                  : "memory"
    );
    return x + (y << 32);
}

void work_until_deadline(const uint64_t *deadline, void (*do_work)()) {
    while (rdtsc() < *deadline) { do_work(); }
}