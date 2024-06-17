section .bss
    result_buffer resb 17
    newline resb 1

section .text
global RightRotate

; Rotate right (ROTR) function
; Arguments:
; rdi - value to rotate
; rsi - number of bits to rotate
ROTR:
    mov rax, rdi            ; Copy the value to rax
    mov rcx, rsi            ; Copy the number of bits to rotate to rcx
    ror rax, cl             ; Rotate rax right by the number of bits in cl
    ret

; Small sigma 0
sigma0:
    mov rax, rdi
    mov rcx, 7
    ror rax, cl
    mov rbx, rax

    mov rax, rdi
    mov rcx, 18
    ror rax, cl
    xor rbx, rax

    mov rax, rdi
    shr rax, 3
    xor rax, rbx

    ret

; Small sigma 1
sigma1:
    mov rax, rdi
    mov rcx, 17
    ror rax, cl
    mov rbx, rax

    mov rax, rdi
    mov rcx, 19
    ror rax, cl
    xor rbx, rax

    mov rax, rdi
    shr rax, 10
    xor rax, rbx

    ret

; Big Sigma 0
Sigma0:
    mov rax, rdi
    mov rcx, 2
    ror rax, cl
    mov rbx, rax

    mov rax, rdi
    mov rcx, 13
    ror rax, cl
    xor rbx, rax

    mov rax, rdi
    mov rcx, 22
    ror rax, cl
    xor rax, rbx

    ret

; Big Sigma 1
Sigma1:
    mov rax, rdi
    mov rcx, 6
    ror rax, cl
    mov rbx, rax

    mov rax, rdi
    mov rcx, 11
    ror rax, cl
    xor rbx, rax

    mov rax, rdi
    mov rcx, 25
    ror rax, cl
    xor rax, rbx

    ret

; Choose function
Choose:
    mov rax, rdi
    and rax, rsi
    mov rcx, rdi
    not rcx
    and rcx, rdx
    xor rax, rcx
    ret

; Majority function
Majority:
    mov rax, rdi
    and rax, rsi
    mov rcx, rdi
    and rcx, rdx
    or rax, rcx
    mov rcx, rsi
    and rcx, rdx
    or rax, rcx
    ret 