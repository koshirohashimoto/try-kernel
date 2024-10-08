﻿/*
 *** Kernel common definition
 */

#ifndef KNLDEF_H
#define KNLDEF_H


/* Task state */
typedef enum {
	TS_NONEXIST	= 0,
	TS_READY	= 1,
	TS_WAIT		= 2,
	TS_DORMANT	= 8
} TSTAT;

/* Task wait factor */
typedef enum {
	TWFCT_NON	= 0,	// Not wait
	TWFCT_DLY	= 1,	// Wait by tk_dly_tsk
	TWFCT_SLP	= 2,	// Wait by tk_slp_tsk
	TWFCT_FLG	= 3,	// Wait by tk_wai_flg
	TWFCT_SEM	= 4,	// Wait by tk_wai_sem
} TWFCT;

/* TCB (Task Control Block) */
typedef struct st_tcb {
	void *context;		// Pointer to context data

	/* Pointer for ready queue */
	struct	st_tcb	*pre;
	struct	st_tcb	*next;

	/* Task info */
	TSTAT	state;				// Task state
	FP		tskadr;				// Task program start address
	PRI		itskpri;			// Priority
	void	*stkadr;			// Stack address
	SZ		stksz;				// Stack size
	INT		wupcnt;				// Wake up count
	
	/* Wait info */
	TWFCT	waifct;				// Wait factor
	RELTIM	waitim;				// Wait time
	ER		*waierr;			// Error code for wait exit

	/* Event flag info */
	UINT	waiptn;				// Wait flag pattern
	UINT	wfmode;				// Wait mode
	UINT	*p_flgptn;			// Flag pattern for wait unlock

	/* Semaphore info */
	INT		waisem;				// Semaphore resource demand count
} TCB;

extern TCB	tcb_tbl[];			// TCB table
extern TCB	*ready_queue[];		// Ready queue per priority
extern TCB	*cur_task;			// Current task
extern TCB	*sche_task;			// Next task
extern TCB	*wait_queue;		// Wait queue

/* Global function */
extern void Reset_Handler(void);        // Reset hander
extern void dispatch_entry(void);		// Dispatcher
extern void systimer_handler(void);		// System timer interrupt handler

/* Call dispatcher */
#define SCB_ICSR		0xE000ED04		// Address of ICSR
#define ICSR_PENDSVSET	(1<<28)			// bit for PendSV set-pending
static inline void dispatch(void)
{
	out_w(SCB_ICSR, ICSR_PENDSVSET);	// PendSV exception
}

/* Scheduler */
extern void scheduler(void);

/* Make context data */
extern void *make_context(UW *sp, UINT ssize, void (*fp)());

/* Control function for ready queue */
extern void tqueue_add_entry(TCB **queue, TCB *tcb);
extern void tqueue_remove_top(TCB **queue);
extern void tqueue_remove_entry(TCB **queue, TCB *tcb);

/* Kernel object */
typedef enum {
	KS_NONEXIST	= 0,	// Not registered
	KS_EXIST	= 1,	// Registered
} KSSTAT;

/* Event flag control block (FLGCB) */
typedef struct st_flgcb {
	KSSTAT	state;		// Event flag state
	UINT	flgptn;		// Event flag pattern
} FLGCB;

/* Semaphore control block (SEMCB) */
typedef struct semaphore_control_block {
	KSSTAT	state;
	INT		semcnt;
	INT		maxsem;
} SEMCB;

/* OS main function */
extern int main(void);

/* User main function */
extern int usermain(void);

#endif  /* KNLDEF_H */
