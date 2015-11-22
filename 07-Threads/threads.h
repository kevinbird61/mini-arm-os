#ifndef __THREADS_H__
#define __THREADS_H__

#include <stdint.h>
#define MAX_TASKS 10

void thread_start();
int thread_create(void (*run)(void*), void* userdata,char *thread_name , int priority);
void thread_kill(int thread_id);
void thread_self_terminal();

/* Thread Control Block */
typedef struct __TCB{
	void *stack;
	void *orig_stack;
	uint8_t in_use;
	/* --Plus-- */
	char *thread_name;
	int thread_tID;
	int priority;
	int scheduled;
}tcb_t;

#endif
