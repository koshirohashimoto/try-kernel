
#ifndef KNLDEF_H
#define KNLDEF_H
/*
 *** Try Kernel
 *      カーネル内部共通定義
 */

/* グローバル関数 */
extern void Reset_Handler(void);        /* リセットハンドラ */
extern void dispatch_entry(void);		// dispatch

/* Call dispatch */
#define SCB_ICSR		0xE000ED04		// Address of ICSR
#define ICSR_PENDSVSET	(1<<28)			// bit for PendSV set-pending

static inline void dispatch(void)
{
	out_w(SCB_ICSR, ICSR_PENDSVSET);
}


/* OSメイン関数 */
extern int main(void);

#endif  /* KNLDEF_H */
