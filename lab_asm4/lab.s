bits 64

section .data
msg1:
	db	"Input x", 10, 0
msg2:
	db	"Input accuracy", 10, 0
msg3:
	db	"ln(1 + %.10g) = %.10g", 10, 0
msg4:
	db	"%f", 0
input_was:
	db	"Your input was: %f", 10, 0


section .text
x	equ	8
y	equ	x + 8

extern printf
extern scanf
extern log1p
global main
main:
	align	8
	push	rbp
	mov	rbp, rsp
	sub	rsp, y
	xor	eax, eax
	mov	edi, msg1
	call	printf

	mov	edi, msg4
	lea	rsi, [rbp - x]
	mov	eax, 0
	call	scanf

	movss	xmm0, [rbp - x]
	mov	edi, input_was
	mov	eax, 0
	call	printf
	

;	xor	eax, eax
;	mov	edi, msg2
;	call	printf
end:
	mov	eax, 60
	mov	rdi, 0
	syscall
