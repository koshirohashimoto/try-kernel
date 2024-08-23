/*
 *** Scheduler
 */

#include <trykernel.h>
#include <knldef.h>

TCB *ready_queue[CNF_MAX_TSKPRI];
TCB *cur_task;
TCB *sche_task;

UW	disp_running;	// running state of dispatcher

/* Task scheduling */
void scheduler(void)
{
	INT i;

	for(i = 0; i < CNF_MAX_TSKPRI; i++){
		if(ready_queue[i] != NULL) break;
	}

	if(i < CNF_MAX_TSKPRI){
		sche_task = ready_queue[i];
	}else{
		sche_task = NULL;
	}

	if(sche_task != cur_task && !disp_running){
		dispatch();
	}
}



