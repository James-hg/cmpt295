insertion_sort(int*, int):
    push    rbp
    mov     rbp, rsp
    mov     QWORD PTR [rbp-24], rdi
    mov     DWORD PTR [rbp-28], esi
    mov     DWORD PTR [rbp-4], 1
    jmp     .L4
.L8:
    mov     eax, DWORD PTR [rbp-4]
    cdqe
    lea     rdx, [0+rax*4]
    mov     rax, QWORD PTR [rbp-24]
    add     rax, rdx
    mov     eax, DWORD PTR [rax]
    mov     DWORD PTR [rbp-12], eax
    mov     eax, DWORD PTR [rbp-4]
    dec     eax
    mov     DWORD PTR [rbp-8], eax
    jmp     .L5
.L7:
    mov     eax, DWORD PTR [rbp-8]
    cdqe
    lea     rdx, [0+rax*4]
    mov     rax, QWORD PTR [rbp-24]
    add     rdx, rax
    mov     eax, DWORD PTR [rbp-8]
    cdqe
    inc     rax
    lea     rcx, [0+rax*4]
    mov     rax, QWORD PTR [rbp-24]
    add     rax, rcx
    mov     edx, DWORD PTR [rdx]
    mov     DWORD PTR [rax], edx
    dec     DWORD PTR [rbp-8]
.L5:
    cmp     DWORD PTR [rbp-8], 0
    js      .L6
    mov     eax, DWORD PTR [rbp-8]
    cdqe
    lea     rdx, [0+rax*4]
    mov     rax, QWORD PTR [rbp-24]
    add     rax, rdx
    mov     eax, DWORD PTR [rax]
    cmp     DWORD PTR [rbp-12], eax
    jl      .L7
.L6:
    mov     eax, DWORD PTR [rbp-8]
    cdqe
    inc     rax
    lea     rdx, [0+rax*4]
    mov     rax, QWORD PTR [rbp-24]
    add     rax, rdx
    mov     edx, DWORD PTR [rbp-12]
    mov     DWORD PTR [rax], edx
    inc     DWORD PTR [rbp-4]
.L4:
    mov     eax, DWORD PTR [rbp-4]
    cmp     eax, DWORD PTR [rbp-28]
    jl      .L8
    nop
    nop
    pop     rbp
    ret
insertion_sort_optimized(int*, int):
    push    rbp
    mov     rbp, rsp
    sub     rsp, 48
    mov     QWORD PTR [rbp-40], rdi
    mov     DWORD PTR [rbp-44], esi
    mov     eax, DWORD PTR [rbp-44]
    cdqe
    lea     rdx, [0+rax*4]
    mov     rax, QWORD PTR [rbp-40]
    add     rax, rdx
    mov     QWORD PTR [rbp-16], rax
    mov     rax, QWORD PTR [rbp-40]
    add     rax, 4
    mov     QWORD PTR [rbp-8], rax
    jmp     .L10
.L13:
    mov     rax, QWORD PTR [rbp-8]
    mov     eax, DWORD PTR [rax]
    mov     DWORD PTR [rbp-28], eax
    mov     rax, QWORD PTR [rbp-8]
    sub     rax, 4
    mov     edx, DWORD PTR [rax]
    mov     eax, DWORD PTR [rbp-28]
    cmp     edx, eax
    jle     .L14
    lea     rax, [rbp-28]
    mov     rsi, QWORD PTR [rbp-8]
    mov     rcx, QWORD PTR [rbp-40]
    mov     rdx, rax
    mov     rdi, rcx
    call    int* std::upper_bound<int*, int>(int*, int*, int const&)
    mov     QWORD PTR [rbp-24], rax
    mov     rax, QWORD PTR [rbp-8]
    sub     rax, QWORD PTR [rbp-24]
    mov     rdx, rax
    mov     rax, QWORD PTR [rbp-24]
    add     rax, 4
    mov     rcx, QWORD PTR [rbp-24]
    mov     rsi, rcx
    mov     rdi, rax
    call    memmove
    mov     edx, DWORD PTR [rbp-28]
    mov     rax, QWORD PTR [rbp-24]
    mov     DWORD PTR [rax], edx
    jmp     .L12
.L14:
    nop
.L12:
    add     QWORD PTR [rbp-8], 4
.L10:
    mov     rax, QWORD PTR [rbp-8]
    cmp     rax, QWORD PTR [rbp-16]
    jb      .L13
    nop
    nop
    leave
    ret