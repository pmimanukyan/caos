    .global discrim
discrim:
     push %ebp      // пролог
     mov %esp, %ebp 
     
     movss 8(%ebp), %xmm0 // a
     movss 12(%ebp), %xmm1 // b
     movss 16(%ebp), %xmm2 // c
     mulss %xmm1, %xmm1 // b^2
     mulss four, %xmm0 // 4*a
     mulss %xmm0, %xmm2 // 4*a*c
     subss %xmm2, %xmm1 // b^2-4ac

     mov 20(%ebp), %eax // кидаю в eax поинтер
     movss %xmm1, (%eax) // меняю значение по поинтеру (*p)
 
     mov %ebp, %esp // эпилог
     pop %ebp
     ret

four:
    .float 4.0