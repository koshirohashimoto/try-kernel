/*
 *** Task sync function
*/


#include <trykernel.h>
#include <knldef.h>

/* Task delay API */
ER tk_dly_tsk(RELTIM dlytim) 
{
    UINT    intsts;
    ER      err = E_OK;

    DI(intsts);     // Disable Interrupt
    if(dlytim > 0){
        tqueue_remove_top(&ready_queue[cur_task->itskpri]);     // Remove task from task queue

        /* Change TCB info */
        cur_task->state     = TS_WAIT;                  // Change task state to wait
        cur_task->waifct    = TWFCT_DLY;                // Set wait factor
        cur_task->waitim    = dlytim + TIMER_PERIOD;    // Set wait time
        cur_task->waierr    = &err;                     // Error code

        tqueue_add_entry(&wait_queue, cur_task);        // Add task to wait queue
        scheduler();
    }
    EI(intsts);     // Enable Interrupt
    return err;
}