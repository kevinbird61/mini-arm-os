#ifndef __OS_H_
#define __OS_H_

#define MAX_TASKS 10
#define STACK_SIZE 256
#define MAX_HEAPS 4096

#define USART_FLAG_TXE  ((uint16_t) 0x0080)
#define USART_FLAG_RXNE ((uint16_t) 0x20)
#define INPUT_MAX 30

#define Mutex_lock 1
#define Mutex_unlock -1
#define Mutex_success 1
#define Mutex_failure 0

typedef struct __Mutex{
	int status;
}Mutex;

#endif
