#include<stdio.h>
#include<stdlib.h>
#include"semaphore.h"

sem_t *mutex;
int abt;
void fun1() {
	int i = 10;
	//sem_wait(mutex);
	while(i--) {
		printf("hello,I'm fun1\n");
	abt++;
		printf("a = %d\n",abt);
		mysleep(2);
	}
	//sem_post(mutex);
}

void fun2() {
	int i = 10;
	//sem_wait(mutex);
	while(i--) {
		printf("hello,I'm fun2\n");
	abt++;
		printf("a = %d\n",abt);
		mysleep(1);
	}
	//sem_post(mutex);
}

void fun3() {
	int i = 15;
	//sem_wait(mutex);
	while(i--) {
		printf("hello,I'm fun3\n");
	abt++;
		printf("a = %d\n",abt);
		mysleep(1);
	}
	//sem_post(mutex);
}

void fun4() {
	int i = 15;
	int m,n;
	//sem_wait(mutex);
	while(i--) {
		printf("hello,I'm fun4\n");
	abt++;
		printf("a = %d\n",abt);
		for(m = 0; m < 10000; m++) 
		  for(n = 0; n < 10000; n++);
	}
	//sem_post(mutex);
}

int main()
{
	int tid1,tid2,tid3,tid4;
	thread_create(&tid1,fun1);
	printf("create thread %d\n",tid1);
	thread_create(&tid2,fun2);
	printf("create thread %d\n",tid2);
	thread_create(&tid3,fun3);
	printf("create thread %d\n",tid3);
	thread_create(&tid4,fun4);
	printf("create thread %d\n",tid4);

	mutex = sem_open("mutex",1);
	int i = 2;
	while(i--) {
		printf("hello,I'm main\n");
		mysleep(3);
	}
	thread_join(tid1);
	printf("join\n");
	thread_join(tid2);
	printf("join\n");
	thread_join(tid3);
	printf("join\n");
	thread_join(tid4);
	printf("join\n");
	
	sem_unlink("mutex");
	return 0;
}
