	.thumb
	.syntax unified

	.global fib
fib:
	push {r4 , r5 , r6 , lr}
	
	cmp r0 , #0
	beq .L0
	
	cmp r0 , #1
	beq .L1
	
	subs r4 , r0 , #0
	mov r5 , #0
	mov r6 , #1

.LoopIt:
	mov r0 , r6
	add r6 , r5 , r6
	mov r5 , r0
	subs r4 , r4 , #1
	bne .LoopIt
	
	pop {r4, r5 , r6 ,pc}
.L0:
	mov r0 , #0
	pop {r4 , r5 ,r6 ,pc}
.L1:
	mov r0 , #1
	pop {r4 , r5 ,r6 ,pc}


