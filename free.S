#include <sys/syscall.h>

    .global free_mem
free_mem:
    push   %ebp
    mov    %esp, %ebp
            //ebp
    mov    8(%esp), %ecx
    sub    $4, %ecx

    mov    freelist, %edx
    mov    %edx, 4(%ecx)
    mov    %ecx, freelist

    mov    %ebp, %esp
    pop    %ebp
    ret

    .data
    .global freelist
freelist:
    .int 0