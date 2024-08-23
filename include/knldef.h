/*
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

/* TCB (Task Control Block) */
typedef struct st_tcb {
	void *context;		// Pointer to context data

	/* Pointer for ready queue */
	struct	st_tcb	*pre;
	struct	st_tcb	*next;

	TSTAT	state;				// Task state
	FP		tskadr;				// Task program start address
	PRI		itskpri;			// Priority
	void	*stkadr;			// Stack address
	SZ		stksz;				// Stack size
} TCB;

extern TCB	tcb_tbl[];			// TCB table
extern TCB	*ready_queue[];		// Ready queue per priority
extern TCB	*cur_task;			// Current task
extern TCB	*sche_task;			// Next task

/* Global function */
extern void Reset_Handler(void);        // Reset hander
extern void dispatch_entry(void);		// Dispatcher

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

/* OS main function */
extern int main(void);

/* User main function */
extern int usermain(void);

#endif  /* KNLDEF_H */
