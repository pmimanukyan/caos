#include <sys/syscall.h>
#include <unistd.h>

void _start() {
    char a[] = "hello world\n";
    asm volatile(".equ SYS_exit, 1\n\t"
                 "int $0x80\n\t"
                 "mov $SYS_exit, %%eax\n\t"
                 "mov $0, %%ebx\n\t"
                 "int $0x80"
    :
    : "a"(SYS_write), "b"(STDOUT_FILENO), "c"(a), "d"(sizeof(a) - 1)
    : "memory"
    );
}