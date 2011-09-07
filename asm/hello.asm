; http://www.nk.rim.or.jp/~jun/lxasm/asm_idx.html

%include "syscall.inc"
%include "cchars.inc"

section .bss
argc: resb 4

; The ELF section declared as ".data" is "WA" otherwise "A"
section .data
msg:
  db "Hello, World!", LF
msg_len equ $ - msg
section .data
hello_msg: db 'Hello, World2!', LF, NUL
newline: db LF, NUL

; ".text" is "AX" otherwise "A"
section .text

puts:
  pushad ; Push All, introduced for 80186
  mov ecx, eax
  mov eax, SYS_WRITE
  mov ebx, 1 ; stdout
  int 80h
  popad
  ret

put_newline:
  push eax
  mov eax, newline
  call putsz
  pop eax
  ret

strlen:
  push edi
  mov edi, eax ; Byte pointer
  push ecx
  push eax
  xor eax, eax ; Search for the null terminator
  mov ecx, 0xFFFF ; No more than 65k chars
  ; scasb: Scan String in Byte unit, Compare AL and [EDI] and
  ; increment EDI
  cld
  repne scasb
  pop ecx ; pop the start of the string
  sub edi, ecx ; edi points the end of the string
  mov eax, edi
  pop ecx
  pop edi
  ret

putsz:
  push edx ; To save the return value
  push eax ; Push the reg which will be destroyed with return value
  call strlen
  mov edx, eax
  pop eax
  call puts
  pop edx
  ret

exit:
  mov ebx, eax
  mov eax, SYS_EXIT
  int 80h
  ret ; Never

%macro PUTSZ 1+
section .data
%%msg: db %1
section .text
  push eax
  mov eax, %%msg
  call putsz
  pop eax
%endmacro

putchar:
  pushad
  push eax
  mov eax, SYS_WRITE
  mov ebx, 1 ; stdout
  mov edx, 1 ; 1 char
  mov ecx, esp ; use stack as a buffer :-)
  int 0x80
  pop eax
  popad
  ret

puthex2:
  push edx
  mov edx, 2
  call puthex
  pop edx
  ret

puthex4:
  push edx
  mov edx, 4
  call puthex
  pop edx
  ret

puthex8:
  push edx
  mov edx, 8
  call puthex
  pop edx
  ret

puthex:
  push eax
  push ecx
  push ebx
  mov ecx, edx ; put [ecx] digits
.loop1:
  mov bl, al
  and bl, 0x0F ; lower in bl
  shr eax
  or bl, 0x30 ; 0〜9 | '0' で、'0'〜'9' に
  cmp bl, 0x3A ; '9' + 1 以上、すなわち要 'A'〜'F'
  jb .skip
  add bl, 0x41 - 0x3A ; 'A' - '9'
.skip:
  push ebx
  loop .loop1
  mov ecx, edx
.loop2:
  pop eax
  call putchar
  loop .loop2
  pop ebx
  pop ecx
  pop eax
  ret

global _start
_start:
  pop eax
  mov [argc], eax
  mov eax, [argc]
  call puthex8
  call put_newline
  mov eax, SYS_WRITE
  mov ebx, 1 ; stdout
  mov ecx, msg
  mov edx, msg_len
  int 80h
  mov eax, hello_msg
  call putsz
  PUTSZ 'hogehoge', LF, NUL
  ; --------
  ; エンディアン――
  ; <-- アドレス下位 38373635 34333231 アドレス上位、スタック底 -->
  ; リトルエンディアンでは、0x31323334 = "4321" ということ
  push 31323334h
  push '5678'
  mov eax, SYS_WRITE
  mov ebx, 1 ; stdout
  mov edx, 8 ; 1 char
  mov ecx, esp
  int 0x80
  pop eax
  pop eax
  call put_newline
  ; --------
  mov eax, 0
  call exit
