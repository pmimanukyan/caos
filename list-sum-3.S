    .global обработка
    // проблема была в том, что портил ebx.
    // хотя локально всё было ок 
    // :|
    // но главное ОК)
обработка:
    mov %ebx, %edx
    xor %eax, %eax // сумма
    push %eax // буду каждый раз доставать со стека и прибавить текущее значение
while:
    cmp     $0, %edx
    jz      return
    
    mov     4(%edx, %esi, 4), %ecx
    add     52(%edx, %edi, 4), %ecx // m1[i] + m2[i]


    // %ecx / 2
    xor     %eax, %eax
    mov     %ecx, %eax
    shr     $31, %ecx
    add     %eax, %ecx
    sar     %ecx
    pop     %eax
    add     %ecx, %eax
    push    %eax
    mov     (%edx), %edx
    jmp     while
return:
    pop     %eax
    pop     %edx
    push    %eax
    push    %edx
    ret

//.text
//    .global load 
//load:
//    mov $4, %esi
//    mov $4, %edi
//    mov 4(%esp), %ebx
  
//    call обработка
//    pop %eax
//    ret