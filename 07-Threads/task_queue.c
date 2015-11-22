#include <stddef.h>
#include "malloc.h"
#include "os.h"

struct tNode {
	int t_ID;
	struct tNode *next;
};

// Use circle queue
struct tNode *t_front = NULL;
struct tNode *t_rear = NULL;

// Delete from queue
void Dequeue_task(){
	struct tNode *temp = t_front;
	if(t_front == NULL){ // queue is empty
		return;
	}
	if(front_task == rear_task){
		t_front = NULL;
		t_rear = NULL;
	}
	else{
		t_front = t_front -> task;
	}
	free(temp);
}

// Push in the queue
void Enqueue_task(int id){
	struct tNode *temp = (struct tNode*)malloc(sizeof(struct tNode));
	temp -> t_ID = id;
	temp -> next = NULL;
	if(t_front == NULL && t_rear == NULL){
		t_front = temp;
		t_rear = temp;
		return;
	}
	t_rear->next = NULL;
	t_rear = temp;
}

// Get Front
int Front_task(){
	if(front_task == NULL){ // task queue is empty
		return -1;
	}
	return t_front -> t_ID;
}

// Check Empty
int isEmpty_task(){
	if(t_front == NULL){
		return 1;
	}
	else{
		return 0;
	}
	return 0;
}
