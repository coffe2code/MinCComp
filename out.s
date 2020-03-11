	.text
.LC0:
	.string	"%d\n"
printint:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	ret

	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	$13, %r8
	movq	$6, %r9
	movq	$4, %r10
	movq	$5, %r11
	imulq	%r10, %r11
	addq	%r9, %r11
	movq	$8, %r9
	movq	$3, %r10
	movq	%r9,%rax
	cqo
	idivq	%r10
	movq	%rax,%r9
	addq	%r11, %r9
	subq	%r9, %r8
	movq	%r8, %rdi
	call	printint
	movl	$0, %eax
	popq	%rbp
	ret
