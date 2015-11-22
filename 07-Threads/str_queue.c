#include "mySTR.c"
#include "malloc.h"
#include "os.h"

void print(const char *str){
	while(*str){
		while(!(*(USART2_SR) & USART_FLAG_TXE));
		*(USART2_DR) = (*str & 0xFF);
		str++;
	}
}

struct Node{
	char data[40];
	struct Node *next;
};

// Using circle queue
struct Node *front = NULL;
struct Node *rear = NULL;

/* free the current queue */
void Dequeue(){
	struct Node *temp = front;
	if(front == NULL){
		print("Queue is empty\n");
		return;
	}
	if(front == rear){
		front = rear = NULL;
	}
	else{
		front = front -> next;
	}
	free(temp);
}

/* Push the string data into current queue */
void Enqueue(const char *str , int length){
	struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
	if(length == 0){
		strcpy(temp -> data , str , strlen(str));
	}
	else{
		strcpy(temp -> data , str , length);	
	}
	temp -> next = NULL;
	if(front == NULL && rear == NULL){
		front = temp;
		rear = temp;
		return;
	}
	rear -> next = temp;
	rear = temp;
}

/* Find the front */
char* Front(){
	if(front == NULL){
		print("Front is empty\n");
		return "EMPTY";
	}
	return front -> data;
}

/* Check is empty or not */
int isEmpty(){
	if(front == NULL){
		return 1;
	}
	else{
		return 0;
	}
}
