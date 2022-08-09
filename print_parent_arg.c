#include <stdint.h>
#include <stdio.h>

void print_parent_arg() {
    uint32_t parent_arg;
    asm volatile (
    "mov (%%ebp), %%eax\t\n"
    "mov 8(%%eax), %%edx\t\n"
    "mov %%edx, %0\t\n"
    : "=m"(parent_arg)
    :
    : "%eax", "%edx");
    printf("%x\n", parent_arg);
}