/*
 *** API definition
 */

#ifndef APIDEF_H_
#define APIDEF_H_

/* Time out duration */
#define TMO_POL		(0)
#define TMO_FEVR	(-1)	// endless loop

/* Task create info */
typedef struct {
	ATR		tskatr;		// task attribute
	FP		task;		// task boot addr
	PRI		itskpri;	// task priority
	SZ		stksz;		// stack size
	void	*bufptr;	// buffer pointer of stack
} T_CTSK;

/* Task attribute */
#define TA_HLNG		0x0000001
#define TA_USERBUF	0x0000020
#define TA_RNG0		0x0000000
#define TA_RNG1		0x0000100
#define TA_RNG2		0x0000200
#define TA_RNG3		0x0000300

/* Task wait attribute */
#define TA_TFIFO	0x00000000		// First In First Out
#define TA_TPRI		0x00000001		// Priority based
#define TA_FIRST	0x00000000		// Prior to first factor of wait_queue
#define TA_CNT		0x00000002		// Prior to less count of wake up demand
#define TA_WSGL		0x00000000		// Not allow multiple task wait (single wait)
#define TA_WMUL		0x00000008		// Allow multiple task wait

/* Task manage API */
ID tk_cre_tsk(const T_CTSK *pk_ctsk);
ER tk_sta_tsk(ID tskid, INT stacd);
void tk_ext_tsk(void);

/* Task sync API */
ER tk_dly_tsk(RELTIM dlytime);
ER tk_slp_tsk(TMO tmout);
ER tk_wup_tsk(ID tskid);

/* Event flag info */
typedef struct t_cflg {
	ATR		flgatr;
	UINT	iflgptn;
} T_CFLG;

/* Event flag API */
ID tk_cre_flg(const T_CFLG *pk_cflg);
ER tk_set_flg(ID flgid, UINT setptn);
ER tk_clr_flg(ID flgid, UINT clrptn);

#define TWF_ANDW	0x00000000U		// AND wait
#define TWF_ORW		0x00000001U		// OR wait
#define TWF_CLR		0x00000010U		// Clear All bit
#define TWF_BITCLR	0x00000020U		// Clear bit

ER tk_wai_flg(ID flgid, UINT waiptn, UINT wfmode, UINT *p_flgptn, TMO tmout);

#endif /* APIDEF_H_ */
