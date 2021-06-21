#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__
#include"thread.h"

struct semaphore_queue {
	int front;
	int rear;
	struct task_struct *wait_tasks[NR_TASKS];
};
typedef struct semaphore_queue sem_queue;

struct semaphore_t {
	int value;
	int occupied;
	char name[16];
	struct semaphore_queue wait_queue;
};

typedef struct semaphore_t sem_t;

sem_t* sem_open(const char* name,unsigned int value);
int sem_wait(sem_t* sem);
int sem_post(sem_t* sem);
int sem_unlink(const char* name);
#endif
