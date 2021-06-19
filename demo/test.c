#include<unistd.h>
#include<stdio.h>

void fun() {
	while(1) {
		printf("hello, I'm fun\n");
		sleep(1);
	}
}
//stack overflow
int main() {
	int stack[64] = { 0 };
	stack[63] = (int)fun;
	printf("%d\n",stack[63]);
	int new_esp = (int)(stack + 63);

	__asm__(
		"mov %0, %%esp\n\t"
		"ret\n\t"
		::"m"(new_esp));
	return 0;
}
