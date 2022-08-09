    .equ SYS_exit, 1
    .equ SYS_write, 4
    .equ SYS_read, 3
    .equ STDIN_FILENO, 0
    .equ STDOUT_FILENO, 1
    .equ BUFSIZE, 1


myprint:
    push %ebp
    mov %esp, %ebp

    push %ebx
    push %ecx
    push %edx

    mov $SYS_write, %eax
    mov $STDOUT_FILENO, %ebx
    mov 8(%ebp), %ecx
    mov 12(%ebp), %edx

    int $0x80
    
    pop %edx
    pop %ecx
    pop %ebx
    mov %ebp, %esp
    pop %ebp
    ret

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
    xor %ecx, %ecx
loop:
    inc %ecx
    sub $BUFSIZE, %esp
    mov %esp, %edi

    push $BUFSIZE
    push %edi
    call myinput
    cmp $0, %eax
    jle fail
    mov (%edi), %dl
 
    mov %eax, %esi
    mov (%edi), %al
    cmp $'\n', %al
    jnz notnewline
newline:
    push $greetingend-greeting
    push $greeting
    call myprint

    xor %ecx, %ecx
    jmp loop

elevennotnewline:
    push $greetingend-greeting
    push $greeting
    call myprint
    
    push %esi
    push %edi
    call myprint

    xor %ecx, %ecx
    inc %ecx
    jmp loop
notnewline:
    cmp $11, %ecx
    jz elevennotnewline
printsymbol:
    push %esi
    push %edi
    call myprint
    jmp loop
fail:
    cmp $'\n', %dl
    jz dontneednewline
    push $greetingend-greeting
    push $greeting
    call myprint
dontneednewline:
    mov $SYS_exit, %eax
    mov $0, %ebx
    int $0x80
    
greeting:
    .byte '\n'
greetingend:
    



; input:
; Mary had a little lamb,
; its fleece was white as snow.

; output:
; Mary had a
;  little la
; mb,
; its fleece
;  was white
;  as snow.