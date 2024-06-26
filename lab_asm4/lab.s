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
	db	"Your input was: %.10g %.10g", 10, 0


num:
	dd	1.0
section .text


extern printf
mylog1pf:
	mov	edi, input_was
	movss	xmm2, xmm0
	cvtss2sd xmm0, xmm2
	movss	xmm2, xmm1
	cvtss2sd xmm1, xmm2
	mov	eax, 2
	call	printf	


x	equ	8
y	equ	x + 8
z	equ	y + 8
acc	equ	z + 8
extern printf
extern scanf
extern log1pf
global main
main:
;	push	rcx
	push	rbp
	mov	rbp, rsp
	sub	rsp, acc
	xor	eax, eax
	mov	edi, msg1
	call	printf

	mov	edi, msg4
	lea	rsi, [rbp - x]
	mov	eax, 0
	call	scanf
	

	mov	edi, msg2
	xor	eax, eax
	call	printf
	
	mov	edi, msg4
	lea	rsi, [rbp - z]
	mov	eax, 0
	call	scanf

	;movss	xmm0, [rbp - x]
	movss	xmm0, [rbp - x]
	call	log1pf
	cvtss2sd 	xmm0, xmm0
	movsd	[rbp - y], xmm0
	movss	xmm0, [rbp - x]
	movss	xmm1, [rbp - z]
	call	mylog1pf
	


	movsd	xmm0, [rbp - y]
	mov	edi, input_was
	mov	eax, 1
	call	printf
;	pop	rcx

;	xor	eax, eax
;	mov	edi, msg2
;	call	printf
end:
	mov	eax, 60
	mov	rdi, 0
	syscall
