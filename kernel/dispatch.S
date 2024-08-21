/*
 *** Dispatch
*/

	.align 2
	.thumb_func
	.globl dispatch_entry

dispatch_entry:
	/* [1] 実行中タスクのコンテキスト情報をスタックに退避 */
	push	{r4-r7}
	mov		r0, r8
	mov		r1, r9
	mov		r2, r10
	mov		r3, r11
	push	{r0-r3}

	/* [2] 現在実行中のタスク確認 */
