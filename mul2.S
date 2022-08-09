    .global mul2
mul2:
    push    %ebp
    mov     %esp, %ebp
    mov     8(%ebp), %ecx
    mov     (%ecx), %eax
    shl     %eax
    jo      return
    mov     %eax, (%ecx)

return:
    mov     %ecx, 8(%ebp)
    mov     %ebp, %esp
    pop     %ebp
    ret