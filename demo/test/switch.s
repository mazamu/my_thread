/*void switch_to(int n)*/

.section .text
.global switch_to
switch_to:
	push %ebp
	mov %esp,%ebp /* in order to find flag */

	/*store the status*/
	push %edi
	push %esi
	push %ebx
	push %edx
	push %ecx
	push %eax
	pushfl

	/*prepare to change stack*/
	mov cur,%eax /*store the esp*/
	mov %esp,task(,%eax,4)
	mov 8(%ebp),%eax /*get the next thread id*/
	mov %eax,cur /*set cur the next thread*/
	mov task(,%eax,4),%esp /*switch_to the stack of next thread*/

	popfl
	popl %eax
	popl %edx
	popl %ecx
	popl %ebx
	popl %esi
	popl %edi

	popl %ebp
	ret
