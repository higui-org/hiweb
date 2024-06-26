.intel_syntax noprefix

%include "../Functions.asm"

section .data
    K dd 0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5
      dd 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5
      dd 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3
      dd 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174
      dd 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc
      dd 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da
      dd 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7
      dd 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967
      dd 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13
      dd 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85
      dd 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3
      dd 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070
      dd 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5
      dd 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3
      dd 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208
      dd 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2

    H dd 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a
      dd 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19


.global SHA256

SHA256:
  ; rdi - вказівник на рядок
  ; rsi - довжина рядка
  ; rdx - вказівник на результат
  ; Ініціалізуємо початкові значення
  call SHA256_Init

  call SHA256_Update
  mov rax, rdx
  ret

SHA256_Transform:
  ; rdi - вказівник на рядок
  ; rcx - 


SHA256_Update:
  sub rsp, 8    ; Виділити місце для локальних змінних
  xor rsp, rsp  ; Очистити rcx (лічильник)
  .loop_start:
    xor rcx, rcx  ; Очистити rcx
    cmp rsp, rsi  ; Порівняти лічильник з довжиною рядка
    jg .loop_end  ; jg(a<b) Вийти з циклу, якщо всі символи оброблені

    cmp rcx, 64   ; Порівняти лічильник з 64
    je .SHA256_Transform  ; je(a=b) В. викликати функцію SHA256_Transform, якщо оброблено 64 байти

    inc rsp
    inc rcx
    jmp .loop_start ; Повернутися на початок циклу
  .loop_end:
    add rsp, 8    ; Звільнити місце для локальних змінних
    ret

SHA256_Init:
  movdqa xmm0, [H]
  movdqa [rdi], xmm0
  movdqa xmm1, [H+16]
  movdqa [rdi+16], xmm1
  movdqa xmm2, [H+32]
  movdqa [rdi+32], xmm2
  movdqa xmm3, [H+48]
  movdqa [rdi+48], xmm3
  ret


SHA256_Update:
    ; rdi - вказівник на контекст SHA-256 (масив H)
    ; rsi - вказівник на рядок
    ; rdx - довжина рядка

    xor ecx, ecx          ; Очистити rcx (лічильник)
  .loop_start:
    cmp ecx, edx          ; Порівняти лічильник з довжиною рядка
    jge .loop_end         ; Вийти з циклу, якщо всі символи оброблені

    mov al, [rsi + rcx]   ; Зчитати символ з рядка (байт)
    ; Тут можна виконати якусь обробку символу, наприклад, додати до якогось значення
    ; У реальному алгоритмі SHA-256 тут буде складніша логіка


    inc rcx               ; Збільшити лічильник
    jmp .loop_start       ; Повернутися на початок циклу
  .loop_end:
    ret