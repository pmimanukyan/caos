    .global delegate
delegate:
    push    %ebp
    mov     %esp, %ebp
    mov     8(%esp), %ecx // N
    mov     12(%esp), %eax // address fun
while: // пока N != 0 по очереди пушим аргументы
    cmp     $0, %ecx
    jz      return
    mov     12(%ebp, %ecx, 4), %edx
    push    %edx
    sub     $1, %ecx
    jmp     while
return: 
    call    *%eax
    mov     %ebp, %esp
    pop     %ebp
    ret