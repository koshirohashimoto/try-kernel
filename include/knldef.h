/*
 *** Kernel common definition
 */

#ifndef KNLDEF_H
#define KNLDEF_H

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

/* Main function */
extern int main(void);

#endif  /* KNLDEF_H */
