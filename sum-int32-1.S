    .global main
main:
    mov $0, %ebx
loop:
    call readi32
    jc return
    add %eax, %ebx
    jno loop
    mov $0x7FFFFFFF, %eax
    adc $0, %eax // обработка переполнения
    jmp return1
return:
    mov %ebx, %eax
return1:
    call writei32
    call finish