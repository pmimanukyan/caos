   .global process
process:
    push %ebp
    mov %esp, %ebp
    mov $0, %edx
loop:
    call readi32
    jc return
    push %eax
    add $1, %edx
    jmp loop
return:
loop1:
    cmp $0, %edx
    jz finish
    pop %ecx
    mov %ecx, %eax
    call writei32
    sub $1, %edx
    jmp loop1 
finish:
    mov %ebp, %esp
    pop %ebp
    ret