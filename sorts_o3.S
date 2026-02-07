insertion_sort(int*, int):
    lea     r9d, [rsi-1]
    xor     r8d, r8d
    cmp     esi, 1
    jle     .L11
.L6:
    mov     esi, DWORD PTR [rdi+4+r8*4]
    mov     rax, r8
.L3:
    mov     edx, DWORD PTR [rdi+rax*4]
    mov     ecx, eax
    cmp     edx, esi
    jle     .L13
    mov     DWORD PTR [rdi+4+rax*4], edx
    dec     rax
    cmp     eax, -1
    jne     .L3
    mov     rax, rdi
.L4:
    inc     r8
    mov     DWORD PTR [rax], esi
    cmp     r9, r8
    jne     .L6
.L11:
    ret
.L13:
    inc     ecx
    movsx   rcx, ecx
    lea     rax, [rdi+rcx*4]
    jmp     .L4
insertion_sort_optimized(int*, int):
    movsx   rsi, esi
    push    r14
    push    r13
    push    r12
    lea     r12, [rdi+4]
    push    rbp
    push    rbx
    lea     rbx, [rdi+rsi*4]
    cmp     rbx, r12
    jbe     .L23
    mov     r14, rdi
    jmp     .L20
.L16:
    add     r12, 4
    cmp     rbx, r12
    jbe     .L23
.L20:
    mov     r13d, DWORD PTR [r12]
    cmp     r13d, DWORD PTR [r12-4]
    jge     .L16
    mov     rax, r12
    mov     rbp, r14
    sub     rax, r14
    sar     rax, 2
.L18:
    test    rax, rax
    jle     .L25
.L19:
    mov     rdx, rax
    sar     rdx
    lea     rcx, [rbp+0+rdx*4]
    cmp     r13d, DWORD PTR [rcx]
    jl      .L21
    sub     rax, rdx
    lea     rbp, [rcx+4]
    dec     rax
    test    rax, rax
    jg      .L19
.L25:
    mov     rdx, r12
    lea     rdi, [rbp+4]
    mov     rsi, rbp
    add     r12, 4
    sub     rdx, rbp
    call    memmove
    mov     DWORD PTR [rbp+0], r13d
    cmp     rbx, r12
    ja      .L20
.L23:
    pop     rbx
    pop     rbp
    pop     r12
    pop     r13
    pop     r14
    ret
.L21:
    mov     rax, rdx
    jmp     .L18