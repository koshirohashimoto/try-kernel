/*
 *** System timer
*/


#include <trykernel.h>
#include <knldef.h>

TCB *wait_queue;

/* System timer interrupt handler */
void systimer_handler(void)
{
    TCB *tcb;

    for(tcb = wait_queue; tcb != NULL; tcb = tcb->next){
        if(tcb->waitim == TMO_FEVR){
            continue;
        }else if (tcb->waitim > TIMER_PERIOD){
            tcb->waitim -= TIMER_PERIOD;
        }else{
            tqueue_remove_entry(&wait_queue, tcb);

            /* Timeout */
            if(tcb->waifct == TWFCT_DLY){
            	*tcb->waierr = E_OK;
            }else{
            	*tcb->waierr = E_TMOUT;
            }

            tcb->state      = TS_READY;
            tcb->waifct     = TWFCT_NON;
            tqueue_add_entry(&ready_queue[tcb->itskpri], tcb);
        }
    }
    scheduler();
}
