#include"thread.h"
#include<stdlib.h>

void schedule();
static struct task_struct init_task = {0,NULL,0,{0}};
struct task_struct *current = &init_task;
struct task_struct *task[NR_TASKS] = {&init_task};
void start(struct task_struct *tsk) {
	tsk->th_fn();
	task[tsk->id] = NULL;//to be care about,it's stored in switch,just not working
	struct task_struct *next = pick();
	if(next) {
		switch_to(next);
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
