/*
 *** Task Manage
 */

#include <trykernel.h>
#include <knldef.h>

/* Task Control Block (TCB) */
TCB tcb_tbl[CNF_MAX_TSKID];

/* Task create API */
ID tk_cre_tsk(const T_CTSK *pk_ctsk)
{
	UINT	intsts;
	ID		tskid;
	INT		i;
	/* Error check for arguments */
	if((pk_ctsk->tskatr & ~TA_RNG3) != (TA_HLNG|TA_USERBUF)) return E_RSATR;
	if(pk_ctsk->itskpri <= 0 || pk_ctsk->itskpri > CNF_MAX_TSKPRI) return E_PAR;
	if(pk_ctsk->stksz == 0) return E_PAR;

	DI(intsts);		// Disable Interrupt

	/* Search no use TCB */
	for(i = 0; i < CNF_MAX_TSKID; i++){
		if(tcb_tbl[i].state == TS_NONEXIST) break;
	}

	/* Initialize TCB */
	if(i < CNF_MAX_TSKID){
		tcb_tbl[i].state	= TS_DORMANT;
		tcb_tbl[i].pre		= NULL;
		tcb_tbl[i].next		= NULL;
		tcb_tbl[i].tskadr	= pk_ctsk->task;
		tcb_tbl[i].itskpri	= pk_ctsk->itskpri;
		tcb_tbl[i].stksz	= pk_ctsk->stksz;
		tcb_tbl[i].stkadr	= pk_ctsk->bufptr;
		tskid = i+1;
	}else{
		tskid = (ID)E_LIMIT;
	}

	EI(intsts);		// Enable Interrupt
	return tskid;
}

/* Task start API */
ER tk_sta_tsk(ID tskid, INT stacd)
{
	TCB		*tcb;
	UINT	intsts;
	ER		err = E_OK;
	/* Error check for arguments */
	if(tskid <= 0 || tskid > CNF_MAX_TSKID) return E_ID;

	DI(intsts);		// Disable Interrupt

	tcb = &tcb_tbl[tskid-1];
	if(tcb->state == TS_DORMANT){
		tcb->state 		= TS_READY;
		tcb->context 	= make_context(tcb->stkadr, tcb->stksz, tcb->tskadr);
		tqueue_add_entry(&ready_queue[tcb->itskpri], tcb);
		scheduler();
	}else{
		err = E_OBJ;
	}

	EI(intsts);		// Enable Interrupt
	return err;
}

/* Task exit API */
void tk_ext_tsk(void)
{
	UINT	intsts;

	DI(intsts);		// Disable Interrupt

	cur_task->state = TS_DORMANT;	// Move the task state to DORMANT
	tqueue_remove_top(&ready_queue[cur_task->itskpri]);

	scheduler();
	EI(intsts);		// Enable Interrupt
}

