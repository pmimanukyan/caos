; prologue problem

    .global main
main:
    push    $out    
    push    %ebp    
    mov     %esp, %ebp
    jmp     process
out:
    call writei32
    call finish