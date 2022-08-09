    .global myhypot
myhypot:
     push %ebp      // пролог
     mov %esp, %ebp 
     
     //помним, что xmm - 128бит
     movsd 8(%ebp), %xmm0 // x в xmm0
     movsd 16(%ebp), %xmm1 // y в xmm1
     mulsd %xmm0, %xmm0 // возвожу в квадрат
     mulsd %xmm1, %xmm1 // возможу в квадрат
     addsd %xmm1, %xmm0 // суммирую
     sqrtsd %xmm0, %xmm0 // беру корень

     mov 24(%ebp), %eax // кидаю в eax поинтер
     movsd %xmm0, (%eax) // меняю значение по поинтеру (*p)
 
     mov %ebp, %esp // эпилог
     pop %ebp
     ret