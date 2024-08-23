/*
 *** Dispatcher
*/

	.align 2
	.thumb_func
	.globl dispatch_entry

dispatch_entry:
	mov		r0, #1
	msr		primask, r0		// Disable Interrupt
	ldr		r1, =disp_running
	str		r0, [r1]

	/* [1] Move the context data of executing task to stack */
	push	{r4-r7}
	mov		r0, r8
	mov		r1, r9
	mov		r2, r10
	mov		r3, r11
	push	{r0-r3}

	/* [2] Confirm the current task */
	ldr		r0, =cur_task
	ldr		r1, [r0]
	cmp		r1, #0
	beq		disp_010		// if cur_task ID = 0, go to disp_010

	/* [3] Store the context data on SP to current TCB */
	mov		r2, sp
	str		r2, [r1]

disp_010:
	/* [4] Confirm the next task */
	ldr		r1, =sche_task
	ldr		r2, [r1]
	cmp		r2, #0
	bne		disp_030

	/* [5] if there is no sche_task */
	str		r2, [r0]

disp_020:
	mov		r3, #0
	msr		primask, r3		// Enable Interrupt
	mov		r3, #1
	msr		primask, r3		// Disable Interrupt
	ldr		r2, [r1]
	cmp		r2, #0
	beq		disp_020

disp_030:
	/* [6] Change the running task */
	str		r2, [r0]
	ldr		r0, [r2]
	mov		sp, r0

	/* [7] Pop the context data from stack */
	pop		{r0-r3}
	mov		r11, r3
	mov		r10, r2
	mov		r9, r1
	mov		r8, r0
	pop		{r4-r7}

	/* Enable Interrupt */
	ldr		r0, =disp_running
	mov		r1, #0
	str		r1, [r0]
	msr		primask, r1		// Enable Interrupt

	bx	lr
