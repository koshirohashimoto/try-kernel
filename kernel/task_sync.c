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

/* Task sleep API */
ER tk_slp_tsk(TMO tmout)
{
    UINT    intsts;
    ER      err = E_OK;

    DI(intsts);
    if(cur_task->wupcnt > 0){
        cur_task->wupcnt--;
    }else{
        tqueue_remove_top(&ready_queue[cur_task->itskpri]);

        /* Change TCB info */
        cur_task->state     = TS_WAIT;
        cur_task->waifct    = TWFCT_SLP;
        cur_task->waitim    = (tmout==TMO_FEVR)?tmout:(tmout+TIMER_PERIOD);
        cur_task->waierr    = &err;

        tqueue_add_entry(&wait_queue, cur_task);
        scheduler();
    }
    EI(intsts);
    return err;
}

/* Task wake up API */
ER tk_wup_tsk(ID tskid)
{
    TCB     *tcb;
    UINT    intsts;
    ER      err = E_OK;

    if(tskid <= 0 || tskid > CNF_MAX_TSKID) return E_ID;

    DI(intsts);
    tcb = &tcb_tbl[tskid-1];
    if((tcb->state == TS_WAIT) && (tcb->waifct == TWFCT_SLP)){
        tqueue_remove_entry(&wait_queue, tcb);

        /* Change TCB info */
        tcb->state  = TS_READY;
        tcb->waifct = TWFCT_NON;

        tqueue_add_entry(&ready_queue[tcb->itskpri], tcb);
        scheduler();
    }else if(tcb->state == TS_READY || tcb->state == TS_WAIT){
        tcb->wupcnt++;
    }else{
        err = E_OBJ;
    }

    EI(intsts);
    return err;
}
