.global run_on_stack
run_on_stack:
    push %ebp
    mov %esp, %ebp

    mov 8(%ebp), %eax
    mov 12(%ebp), %ecx
    mov 16(%ebp), %esp

    push %esp
    push %ecx
    call *%eax

    mov %ebp, %esp
    pop %ebp
    ret