/*
 *** semaphore.c
*/

#include <trykernel.h>
#include <knldef.h>

SEMCB	semcb_tbl[CNF_MAX_SEMID];	// Semaphore control block

/* Semaphore create API */
ID tk_cre_sem(const T_CSEM *pk_csem)
{
	ID		semid;
	UINT	intsts;

	DI(intsts);

	for(semid = 0; semcb_tbl[semid].state != KS_NONEXIST; semid++);

	if(semid < CNF_MAX_SEMID){
		semcb_tbl[semid].state	= KS_EXIST;
		semcb_tbl[semid].semcnt	= pk_csem->isemcnt;
		semcb_tbl[semid].maxsem	= pk_csem->maxsem;
		semid++;
	}else{
		semid = E_LIMIT;
	}

	EI(intsts);
	return semid;
}

/* Semaphore wait API */
ER tk_wai_sem(ID semid, INT cnt, TMO tmout)
{
	SEMCB	*semcb;
	ER		err = E_OK;
	UINT	intsts;

	if(semid <= 0 || semid > CNF_MAX_SEMID) return E_ID;

	DI(intsts);

	semcb = &semcb_tbl[--semid];
	if(semcb->state == KS_EXIST){
		if(semcb->semcnt >= cnt){		// current semaphore num >= demand num
			semcb->semcnt -= cnt;
		}else if(tmout == TMO_POL){		// shortage of semaphore, and time out
			err = E_TMOUT;
		}else{							// shortage of semaphore, and move to wait state
			tqueue_remove_top(&ready_queue[cur_task->itskpri]);

			/* Change TCB info */
			cur_task->state		= TS_WAIT;
			cur_task->waifct	= TWFCT_SEM;
			cur_task->waitim	= ((tmout == TMO_FEVR)? tmout: tmout + TIMER_PERIOD);
			cur_task->waisem	= cnt;
			cur_task->waierr	= &err;

			tqueue_add_entry(&wait_queue, cur_task);
			scheduler();
		}
	}else{
		err = E_NOEXS;
	}

	EI(intsts);
	return err;
}

/* Semaphore signal API */
ER tk_sig_sem(ID semid, INT cnt)
{
	SEMCB	*semcb;
	TCB		*tcb;
	ER		err = E_OK;
	UINT	intsts;

	if(semid <= 0 || semid > CNF_MAX_SEMID) return E_ID;

	DI(intsts);

	semcb = &semcb_tbl[--semid];
	if(semcb->state == KS_EXIST){
		semcb->semcnt += cnt;		// Return of semaphore
		if(semcb->semcnt <= semcb->maxsem){
			for(tcb = wait_queue; tcb != NULL; tcb = tcb->next){	// Confirm wait_queue
				if(tcb->waifct == TWFCT_SEM){
					if(semcb->semcnt >= tcb->waisem){
						semcb->semcnt -= tcb->waisem;
						tqueue_remove_entry(&wait_queue, tcb);

						/* Change TCB info */
						tcb->state	= TS_READY;
						tcb->waifct	= TWFCT_NON;
						tcb->waierr	= &err;

						tqueue_add_entry(&ready_queue[tcb->itskpri], tcb);
						scheduler();
					}else{
						break;
					}
				}
			}
		}else{		// shortage of semaphore
			semcb->semcnt -= cnt;
			err = E_QOVR;
		}
	}else{
		err = E_NOEXS;
	}

	EI(intsts);
	return err;
}


