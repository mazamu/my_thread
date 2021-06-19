#include<unistd.h>
#include<stdio.h>

int task[3] = {0,0,0};	//esp
int cur = 0;			//current esp
void switch_to(int n);	//defined in the switch.s
void fun1() {
	while(1) {
		printf("hello,I'm fun1\n");
		sleep(1);
		switch_to(2);
	}
}
void fun2() {
	while(1) {
		printf("hello,I'm fun2\n");
		sleep(1);
		switch_to(1);
	}
}

//start func of thread
void start(int n) {
	if(n == 1) fun1();
	else if(n == 2) fun2();
}

int main() {
	
	int stack1[1024] = {0};
	int stack2[1024] = {0};
	task[1] = (int)(stack1 + 1013);
	task[2] = (int)(stack2 + 1013);
	
	//init fun1 thread
	//init switch_to func
	stack1[1013] = 7;//eflags
	stack1[1014] = 6;//eax
	stack1[1015] = 5;//edx
	stack1[1016] = 4;//ecx
	stack1[1017] = 3;//ebx
	stack1[1018] = 2;//esi
	stack1[1019] = 1;//edi
	stack1[1020] = 0;//old ebp
	stack1[1021] = (int)start;//ret to start
	
	//the first time of func start,about stack page
	stack1[1022] = 100;//ret to unknown,if start end,so the thread end
	stack1[1023] = 1;//start flag

	//init fun2 thread
	//init switch_to func
	stack2[1013] = 7;//eflags
	stack2[1014] = 6;//eax
	stack2[1015] = 5;//edx
	stack2[1016] = 4;//ecx
	stack2[1017] = 3;//ebx
	stack2[1018] = 2;//esi
	stack2[1019] = 1;//edi
	stack2[1020] = 0;//old ebp
	stack2[1021] = (int)start;//ret to start

	//the first time of func start,about stack page
	stack2[1022] = 100;//ret to unknown,if start end,so the thread end
	stack2[1023] = 2;//start flag

	switch_to(1);
}
