#ifndef __THREAD_h__
#define __THREAD_H__

#define NR_TASKS 16
#define STACK_SIZE 1024

#define THREAD_RUNNING 0
#define THREAD_SLEEP 1
#define THREAD_EXIT 2

struct task_struct {
	int id;//thread id
	void (*th_fn)();//func of thread
	int esp;//the ptr of stack top
	int stack[STACK_SIZE];//stack
};

int thread_create(int* tid,void(*start_routine)());
int thread_join(int tid);
void mysleep(int seconds);

