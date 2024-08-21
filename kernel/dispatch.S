/*
 *** Dispatch
*/

	.align 2
	.thumb_func
	.globl dispatch_entry

dispatch_entry:
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

	/* [3] Store the value of SP register to ctx_tbl */
	ldr		r0, =ctx_tbl
	sub		r1, #1
	lsl		r1, r1, #2
	mov		r2, sp
	str		r2, [r0, r1]

disp_010:
	/* [4] Change the current task to the next task */
	ldr		r0, =next_task
	ldr		r1, [r0]
	ldr		r0, =cur_task
	str		r1, [r0]

	/* [5] Change the stack */
	ldr		r0, =ctx_tbl
	sub		r1, #1
	lsl		r1, r1, #2
	ldr		r2, [r0, r1]
	mov		sp, r2

	/* [6] Pop the context data from stack */
	pop		{r0-r3}
	mov		r11, r3
	mov		r10, r2
	mov		r9, r1
	mov		r8, r0
	pop		{r4-r7}
	bx		lr
