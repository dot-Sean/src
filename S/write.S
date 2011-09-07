.data
hello:
	.string "hello world\n"

.text
.globl	main
main:
	movl	$4,%eax
	movl	$1,%ebx
	movl	$hello,%ecx
	movl	$13,%edx
	int	$0x80

	ret

