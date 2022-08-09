    .equ SYS_exit, 1
    .equ SYS_write, 4
    .equ SYS_read, 3
    .equ STDIN_FILENO, 0
    .equ STDOUT_FILENO, 1
    .equ BUFSIZE, 1

myinput:
    push %ebp
    mov %esp, %ebp
    push %ebx
    push %ecx
    push %edx
    
    mov $SYS_read, %eax
    mov $STDIN_FILENO, %ebx
    mov 8(%ebp), %ecx
    mov 12(%ebp), %edx

    int $0x80

    pop %edx
    pop %ecx
    pop %ebx
    mov %ebp, %esp
    pop %ebp
    ret
    
    .global main
main:
    xor %ecx, %ecx // symbol
    xor %ebx, %ebx // word
    xor %esi, %esi // line
    
loop:
    sub $BUFSIZE, %esp
    mov %esp, %edi

    push $BUFSIZE
    push %edi
    call myinput
    pop %edi
    pop junk

    cmp $0, %eax
    jle fail
    inc %ecx
    mov (%edi), %al
    cmp $'\n', %al
    jnz notnewline
    inc %esi
    inc %ebx
notnewline:
    cmp $' ', %al
    jnz notspace
    inc %ebx
notspace:
    jmp loop
fail:
    mov %esi, %eax
    call writei32
    mov %ebx, %eax
    call writei32
    mov %ecx, %eax
    call writei32
    mov $SYS_exit, %eax
    mov $0, %ebx
    int $0x80
    

    .global A, junk
    .data
A:
    .int 0
junk:
    .int 0

; input:
; I sent a message to another time
; But as the days unwind, this I just can't believe...

; output:
; 2
; 17
; 86