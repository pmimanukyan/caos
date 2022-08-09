    .global main
main:
    call readi32
loop:
    cmp $0, %eax
    jl return
    call writei32
    decl %eax
    jmp loop
return:
    call finish