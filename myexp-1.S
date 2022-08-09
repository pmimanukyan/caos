.global myexp
// xmm0 - x
// xmm1 - sum
// xmm2 - sum_next
// xmm4 - count
// xmm6 - d
// xmm7 - one
myexp:
    
    push %ebp
    mov %esp, %ebp
    movsd one, %xmm7
    movsd 8(%ebp), %xmm0
    movsd zero, %xmm1
    movsd zero, %xmm2
    movsd zero, %xmm4
    movsd one, %xmm5
    movsd one, %xmm6
    
while:
    addsd %xmm6, %xmm1 //sum += d
    movsd %xmm1, %xmm2 // sum_next = sum

    addsd %xmm7, %xmm4 // count += 1
    mulsd %xmm0, %xmm6 // d *= x
    divsd %xmm4, %xmm6 // d /= count

    addsd %xmm6, %xmm2 // sum_next += d

    comisd %xmm1, %xmm2 // sum == sum_next
    jne while

    mov 16(%ebp), %eax
    movsd %xmm1, (%eax) 
    
    mov %ebp, %esp
    pop %ebp    
    ret


one:
    .double 1
zero:
    .double 0