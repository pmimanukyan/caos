    .global process
process:
    push %ebp
    mov %esp, %ebp
    mov A, %eax
    mov B, %ecx
    cmp $0, %ecx
    jge return1
negativeB:
    neg %eax
    neg %ecx
return1:
    mov $0, %edx
    mov R, %edx
loop:
    test $1, %ecx
    jz even
odd:
    add %eax, %edx
even:
    shl %eax
    shr %ecx
continuing:
    cmp $0, %ecx
    jnz loop
    mov %edx, R
    mov %ebp, %esp
    pop %ebp
    ret

//main:
//    call process
//    mov R, %eax
//    call writei32
//    call finish
    .global A, B, R
    .data
A:
    .int 0
B:
    .int 0
R:
    .int 0