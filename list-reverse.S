    .global list_reverse
    // %eax -- prev
    // %edx -- next
    // %ecx -- head
list_reverse:
    mov head, %ecx
    xor %eax, %eax
while:
    cmp $0, %ecx
    jz return
    mov 8(%ecx), %edx
    mov %eax, 8(%ecx)
    mov %ecx, %eax
    mov %edx, %ecx
    jmp while
return:
    mov %eax, head
    ret 