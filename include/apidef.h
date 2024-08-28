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

/* Task manage API */
ID tk_cre_tsk(const T_CTSK *pk_ctsk);
ER tk_sta_tsk(ID tskid, INT stacd);
void tk_ext_tsk(void);

/* Task sync API */
ER tk_dly_tsk(RELTIM dlytime);
ER tk_slp_tsk(TMO tmout);
ER tk_wup_tsk(ID tskid);

#endif /* APIDEF_H_ */
