   .global main
main:
    mov $0, %ecx
    mov $0, %edx
loop:
    call readi32
    jc return
    test $1, %eax
    jnz odd
even:
    add %eax, %ecx
    jmp loop
odd:
    add %eax, %edx
    jmp loop
return:
    mov %ecx, %eax
    call writei32
    mov %edx, %eax
    call writei32
    call finish