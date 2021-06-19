#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#define STACK_SIZE 1024
#define NR_TASKS 16


struct task_struct {
	int id;//thread id
	void (*th_fn)();//func of thread
	int esp;//the ptr of stack top
	int stack[STACK_SIZE];//stack
};

static struct task_struct init_task = {0,NULL,0,{0}};
struct task_struct *current = &init_task;
struct task_struct *task[NR_TASKS] = {&init_task};

void switch_to(struct task_struct* next);	//defined in the switch.s
struct task_struct *pick() {
	int current_id = current->id;
	int i = current_id;
	
	struct task_struct *next = NULL;

	while(1) {
		i = (i + 1) % NR_TASKS;

		if(task[i]) {
			next = task[i];
			break;
		}
	}
	
	return next;
}
//start func of thread
void start(struct task_struct *tsk) {
	tsk->th_fn();
	task[tsk->id] = NULL;//to be care about,it's stored in switch,just not working
	struct task_struct *next = pick();
	if(next) {
		switch_to(next);
	}
}

void fun1() {
	while(1) {
		printf("hello,I'm fun1\n");
		sleep(1);
		struct task_struct *next = pick();
		if(next) {
			switch_to(next);
		}
	}
}	
void fun2() {
	while(1) {
		printf("hello,I'm fun2\n");
		sleep(1);
		struct task_struct *next = pick();
		if(next) {
			switch_to(next);
		}
	}
}	
void fun3() {
	while(1) {
		printf("hello,I'm fun3\n");
		sleep(1);
		struct task_struct *next = pick();
		if(next) {
			switch_to(next);
		}
	}
}	
int thread_create(int *tid,void (*start_routine)()) {
	int id = -1;
	struct task_struct *tsk = 
		(struct task_struct*)malloc(sizeof(struct task_struct));
	
	//find an empty position
	while(++id < NR_TASKS && task[id]);
	
	//cannot find it
	if(id == NR_TASKS) return -1;

	//put it in the empty position
	task[id] = tsk;

	//set tid
	if(tid) *tid = id;

	//init thread
	tsk->id = id;
	tsk->th_fn = start_routine;
	int *stack = tsk->stack;
	tsk->esp = (int)(stack + STACK_SIZE - 11);

	//init func stack frame
	stack[STACK_SIZE - 11] = 7;
	stack[STACK_SIZE - 10] = 6;
	stack[STACK_SIZE - 9] = 5;
	stack[STACK_SIZE - 8] = 4;
	stack[STACK_SIZE - 7] = 3;
	stack[STACK_SIZE - 6] = 2;
	stack[STACK_SIZE - 5] = 1;
	stack[STACK_SIZE - 4] = 0;
	stack[STACK_SIZE - 3] = (int)start;
	stack[STACK_SIZE - 2] = 100;
	stack[STACK_SIZE - 1] = (int)tsk;

	return 0;
}

int main()
{
	int tid1,tid2,tid3;
	thread_create(&tid1,fun1);
	printf("create thread %d\n",tid1);
	thread_create(&tid2,fun2);
	printf("create thread %d\n",tid2);
	thread_create(&tid3,fun3);
	printf("create thread %d\n",tid3);

	int i = 5;
	while(i--) {
		printf("hello, I'm main\n");
		sleep(1);
		struct task_struct *next = pick();
		if(next) {
			switch_to(next);
		}
	}
}
