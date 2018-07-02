	.file	"test.c"
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
.globl main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$136, %rsp
	leaq	-80(%rbp), %rbx
	.cfi_offset 3, -24
	movl	$0, %eax
	movl	$7, %edx
	movq	%rbx, %rdi
	movq	%rdx, %rcx
	rep stosq
	movl	$1, -80(%rbp)
	movl	$-442913307, -76(%rbp)
	movl	$-1729709381, -72(%rbp)
	movq	$165, -68(%rbp)
	movq	$0, -60(%rbp)
	movq	$0, -52(%rbp)
	movq	$0, -44(%rbp)
	movq	$0, -36(%rbp)
	movw	$0, -28(%rbp)
	leaq	-80(%rbp), %rcx
	leaq	-144(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy
	movl	-144(%rbp), %edx
	movl	$.LC0, %eax
	movl	%edx, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	addq	$136, %rsp
	popq	%rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-18)"
	.section	.note.GNU-stack,"",@progbits
