#include <stddef.h>
#include <stdint.h>
#include "reg.h"
#include "threads.h"
#include "os.h"
#include "UserStr.c"

/* USART TXE Flag
 * This flag is cleared when data is written to USARTx_DR and
 * set when that data is transferred to the TDR
 */

/* For mutex part */
int wait_Mutex(Mutex *mutex){
	if(mutex->status == Mutex_unlock){
		mutex->status = Mutex_lock;
		return Mutex_success;	// success
	}
	else if(mutex->status == Mutex_lock){
		return Mutex_failure;	// failure
	}
	return Mutex_failure;	// failure
}

void signal_Mutex(Mutex *mutex){
	mutex->status = Mutex_unlock;
}

Mutex *current_Mutex = &(Mutex){
	.status = Mutex_unlock
};

/* Implementation of RCC,GPIO,USART  */

void usart_init(void)
{
	*(RCC_APB2ENR) |= (uint32_t) (0x00000001 | 0x00000004);
	*(RCC_APB1ENR) |= (uint32_t) (0x00020000);

	/* USART2 Configuration, Rx->PA3, Tx->PA2 */
	*(GPIOA_CRL) = 0x00004B00;
	*(GPIOA_CRH) = 0x44444444;
	*(GPIOA_ODR) = 0x00000000;
	*(GPIOA_BSRR) = 0x00000000;
	*(GPIOA_BRR) = 0x00000000;

	*(USART2_CR1) = 0x0000000C;
	*(USART2_CR2) = 0x00000000;
	*(USART2_CR3) = 0x00000000;
	*(USART2_CR1) |= 0x2000;
}

/* Implementation  I/O */

void print(const char *str)
{
	while(*str){
		while(!(*(USART2_SR) & USART_FLAG_TXE));
		*(USART2_DR) = (*str & 0xFF);
		str++;
	}
}

void print_char(const char *str){
	if(*str){
		while(!(*(USART2_SR) & USART_FLAG_TXE));
		*(USART2_DR) = (*str & 0xFF);
	}
}

void print_str(const char *str)
{
	while(wait_Mutex(current_Mutex)!=1); // busy wait
	while (*str) {
		while (!(*(USART2_SR) & USART_FLAG_TXE));
		*(USART2_DR) = (*str & 0xFF);
		str++;
	}
	signal_Mutex(current_Mutex);
}

void print_count_str(const char *str , int count)
{
	while(wait_Mutex(current_Mutex) != 1); // busy wait
	for(int i = 0; i < count ; i++){
		print_char(str++);
	}
	signal_Mutex(current_Mutex);
}

/* Task subfunction */

int command(const char *cmd , uint32_t index)
{
	if(strcmp(cmd,"help",4) && index==4 ){
		while(wait_Mutex(current_Mutex)!= 1); // success
		print("\nWelcome to kevin mini-shell\n");
		print("Commands available : \n");
		print("- help\n");
		print("- about\n");	
		//print("- ps\n");
		//print("- test\n");
		//print("- \"up arrow\"\n");
		signal_Mutex(current_Mutex);
		return 1;		
	}
	else if(strcmp(cmd , "about" , 5) && index == 5){
		print("\nBuild by KevinChiu\n");
		print("2015/11/22 First Edit\n");
		print("Version 0.0.1\n");
		return 1;
	}
	else{
		return 0;
	}
}

static void delay(volatile int count)
{
	count *= 50000;
	while (count--);
}

static void busy_loop(void *str)
{
	while (1) {
		print_str(str);
		print_str(": Running...\n");
		delay(1000);
	}
}

/* Implementation task function */

void shell_command()
{
	/* Using variables */	
	char str_buf[INPUT_MAX];
	int index = 0;
	/* Implement mini-shell */
	while(1){
		print_str("\nmini@kevin-shell:~$");
		/* Blocking the task and get the input */
		while(1){
			if(*(USART2_SR) & USART_FLAG_RXNE){
				str_buf[index] = (*(USART2_DR) & 0xFF);
				if(str_buf[index]==0xD){
					// '\r' in ascii
					print_char("\n");
					signal_Mutex(current_Mutex);
					if(!command(str_buf , index)){
						print_str("User Input:");
						print_count_str(str_buf , index);
					}
						
					print_str("\n");
					index = 0;
					print_str("\nmini@kevin-shell:~$");	
				}
				else{
					if(index == 0){
						print_str("\nmini@kevin-shell:~$");
						while(wait_Mutex(current_Mutex)!=1); // busy wait
						print_char(&str_buf[index]);
						index++;
					}
				}
				print_str(str_buf);
			} 
		}
		delay(1000);
	}
}

void shell(void *userdata)
{
	/* Start the shell */
	shell_command();	
}

void fib_compute(void *userdata)
{
	busy_loop(userdata);
}

void print_result(void *userdata)
{
	busy_loop(userdata);
}

/* 72MHz */
#define CPU_CLOCK_HZ 72000000

/* 100 ms per tick. */
#define TICK_RATE_HZ 10

int main(void)
{
	const char *str1 = "Build_Shell", *str2 = "Fibonacci", *str3 = "Print_result";
	
	usart_init();

	if (thread_create(shell, (void *) str1, str1 , 3) == -1)
		print_str("Shell creation failed\r\n");

	if (thread_create(fib_compute, (void *) str2 , str2 , 1) == -1)
		print_str("Compute Fibonacci failed\r\n");

	if (thread_create(print_result, (void *) str3 , str3 , 2) == -1)
		print_str("Print Result failed\r\n");

	/* SysTick configuration */
	*SYSTICK_LOAD = (CPU_CLOCK_HZ / TICK_RATE_HZ) - 1UL;
	*SYSTICK_VAL = 0;
	*SYSTICK_CTRL = 0x07;
	
	/* Implement shell  */
	//print_str("kevin@kevin-shell:~$\n");	
	/* Do job */
	thread_start();

	return 0;
}
