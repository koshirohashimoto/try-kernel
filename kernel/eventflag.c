/*
 *** eventflag.c
*/

#include <trykernel.h>
#include <knldef.h>

FLGCB	flgcb_tbl[CNF_MAX_FLGID];

/* Event flag create API */
ID tk_cre_flg(const T_CFLG *pk_cflg)
{
	ID		flgid;
	UINT	intsts;

	DI(intsts);

	for(flgid = 0; flgcb_tbl[flgid].state != KS_NONEXIST; flgid++);

	if(flgid < CNF_MAX_FLGID){
		flgcb_tbl[flgid].state	= KS_EXIST;
		flgcb_tbl[flgid].flgptn	= pk_cflg->iflgptn;
		flgid++;
	}else{
		flgid = E_LIMIT;
	}

	EI(intsts);
	return flgid;
}

/* Event flag condition check API */
static BOOL check_flag(UINT flgptn, UINT waiptn, UINT wfmode)
{
	if(wfmode & TWF_ORW){
		return ((flgptn & waiptn) != 0);
	}else{
		return ((flgptn & waiptn) == 0);
	}
}

/* Event flag set API */
ER tk_set_flg(ID flgid, UINT setptn)
{
	FLGCB	*flgcb;
	TCB		*tcb;
	ER		err = E_OK;
	UINT	intsts;

	if(flgid <= 0 || flgid > CNF_MAX_FLGID) return E_ID;

	DI(intsts);

	flgcb = &flgcb_tbl[--flgid];
	if(flgcb->state == KS_EXIST){
		flgcb->flgptn |= setptn;
		for(tcb = wait_queue; tcb != NULL; tcb = tcb->next){
			if(tcb->waifct == TWFCT_FLG){
				if(check_flag(flgcb->flgptn, tcb->waiptn, tcb->wfmode)){
					tqueue_remove_entry(&wait_queue, tcb);
					tcb->state	= TS_READY;
					tcb->waifct	= TWFCT_NON;
					*tcb->p_flgptn = flgcb->flgptn;
					tqueue_add_entry(&ready_queue[tcb->itskpri], tcb);
					scheduler();

					if((tcb->wfmode & TWF_BITCLR) != 0){
						if((flgcb->flgptn &= ~(tcb->waiptn)) == 0){
							break;
						}
					}

					if((tcb->wfmode & TWF_CLR) != 0){
						flgcb->flgptn = 0;
						break;
					}
				}
			}
		}
	}else{
		err = E_NOEXS;
	}

	EI(intsts);
	return err;
}

/* Event flag clear API */
ER tk_clr_flg(ID flgid, UINT clrptn)
{
	FLGCB	*flgcb;
	ER		err = E_OK;
	UINT	intsts;

	if(flgid <= 0 || flgid > CNF_MAX_FLGID) return E_ID;

	DI(intsts);

	flgcb = &flgcb_tbl[--flgid];
	if(flgcb->state == KS_EXIST){
		flgcb->flgptn &= clrptn;
	}else{
		err = E_NOEXS;
	}

	EI(intsts);
	return err;
}

/* Event flag wait API */
ER tk_wai_flg(ID flgid, UINT waiptn, UINT wfmode, UINT *p_flgptn, TMO tmout)
{
	FLGCB	*flgcb;
	ER		err = E_OK;
	UINT	intsts;

	if(flgid <= 0 || flgid > CNF_MAX_FLGID) return E_ID;

	DI(intsts);

	flgcb = &flgcb_tbl[--flgid];
	if(flgcb->state == KS_EXIST){
		if(check_flag(flgcb->flgptn, waiptn, wfmode)){
			*p_flgptn = flgcb->flgptn;
			if((wfmode & TWF_BITCLR) != 0){
				flgcb->flgptn &= ~waiptn;
			}

			if((wfmode & TWF_CLR) != 0){
				flgcb->flgptn = 0;
			}
		}else if(tmout == TMO_POL){
			err = E_TMOUT;
		}else{
			tqueue_remove_top(&ready_queue[cur_task->itskpri]);

			/* Change TCB info */
			cur_task->state		= TS_WAIT;
			cur_task->waifct	= TWFCT_FLG;
			cur_task->waitim	= ((tmout == TMO_FEVR)? tmout: tmout + TIMER_PERIOD);
			cur_task->waiptn	= waiptn;
			cur_task->wfmode	= wfmode;
			cur_task->p_flgptn	= p_flgptn;
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



