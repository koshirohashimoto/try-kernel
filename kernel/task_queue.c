/*
 *** Task Queue Control
 */

#include <trykernel.h>
#include <knldef.h>

/* Add entry to queue */
void tqueue_add_entry(TCB **queue, TCB *tcb)
{
	TCB *queue_end;

	if(*queue == NULL){		// if there is no task in queue
		*queue		= tcb;	// register add target entry (tcb) addr to top of queue
		tcb->pre	= tcb;	// there is one tcb, so tcb_pre indicates tcb (queue_end = queue_top)
	}else{
		queue_end		= (*queue)->pre;	// pre-factor of queue top is queue_end (loop structure)
		queue_end->next	= tcb;
		tcb->pre		= queue_end;
		(*queue)->pre	= tcb;
	}
	tcb->next = NULL;
}

/* Remove entry from queue top */
void tqueue_remove_top(TCB **queue)
{
	TCB *top;

	if(*queue == NULL) return;

	top 	= *queue;		// register current top factor of queue
	*queue	= top->next;	// update top factor to second factor
	if(*queue != NULL){
		(*queue)->pre = top->pre;	// update end factor (top->pre) as pre-factor of 2nd factor
	}
}

/* Remove entry from queue */
void tqueue_remove_entry(TCB **queue, TCB *tcb)
{
	if(*queue == tcb){		// if remove target entry (tcb) is top of queue
		tqueue_remove_top(queue);
	}else{
		(tcb->pre)->next = tcb->next;		// update next factor of tcb as next factor of tcb-pre
		if(tcb->next != NULL){
			(tcb->next)->pre = tcb->pre;	// update pre-factor of tcb as pre-factor of tcb-next
		}else{
			(*queue)->pre = tcb->pre;		// update end factor from tcb to tcb-pre
		}
	}
}
