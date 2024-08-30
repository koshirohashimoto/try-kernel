/*
 *** main.c
 */

#include <trykernel.h>

/* Event flag create info */
ID	flgid;
T_CFLG cflg = {
	.flgatr		= TA_TFIFO | TA_WMUL,
	.iflgptn	= 0,
};

/* Semaphore create info */
ID	semid;
T_CSEM csem = {
	.sematr		= TA_TFIFO | TA_FIRST,
	.isemcnt	= 1,
	.maxsem		= 1,
};

/* Button task */
UW	tskstk_btn[1024/sizeof(UW)];	// Stack for button task
ID	tskid_btn;

void task_btn(INT stacd, void *exinf);
T_CTSK	ctsk_btn = {
	.tskatr		= TA_HLNG | TA_RNG3 | TA_USERBUF,
	.task		= task_btn,
	.itskpri	= 10,
	.stksz		= 1024,
	.bufptr		= tskstk_btn,
};

/* LED task1 */
UW	tskstk_led1[1024/sizeof(UW)];	// Stack for LED task
ID	tskid_led1;

void task_led1(INT stacd, void *exinf);
T_CTSK	ctsk_led1 = {
	.tskatr		= TA_HLNG | TA_RNG3 | TA_USERBUF,
	.task		= task_led1,
	.itskpri	= 10,
	.stksz		= 1024,
	.bufptr		= tskstk_led1,
};

/* LED task2 */
UW	tskstk_led2[1024/sizeof(UW)];	// Stack for LED task
ID	tskid_led2;

void task_led2(INT stacd, void *exinf);
T_CTSK	ctsk_led2 = {
	.tskatr		= TA_HLNG | TA_RNG3 | TA_USERBUF,
	.task		= task_led2,
	.itskpri	= 10,
	.stksz		= 1024,
	.bufptr		= tskstk_led2,
};

/* Button task function */
void task_btn(INT stacd, void *exinf)
{
	UW btn, btn0, diff;

	/* Set GP13 to switch input */
	out_w(GPIO(13), (in_w(GPIO(13)) | GPIO_PUE) & ~GPIO_PDE);	// Pull-up setting
	out_w(GPIO_OE_CLR, (1<<13));								// Invalidate output
	out_w(GPIO_CTRL(13), 5);									// SIO function

	/* Set GP14 to switch input */
	out_w(GPIO(14), (in_w(GPIO(14)) | GPIO_PUE) & ~GPIO_PDE);	// Pull-up setting
	out_w(GPIO_OE_CLR, (1<<14));								// Invalidate output
	out_w(GPIO_CTRL(14), 5);									// SIO function

	btn0 = in_w(GPIO_IN) & ((1<<14)|(1<<13));			// Set init value to GPIO_IN

	while(1){
		btn = in_w(GPIO_IN) & ((1<<14)|(1<<13));		// Read switch value
		if((diff = btn ^ btn0) != 0){
			if((diff & (1<<13)) && !(btn & (1<<13))){
				tm_putstring("Button1 ON");
				tk_set_flg(flgid, (1<<1));
			}
			if((diff & (1<<14)) && !(btn & (1<<14))){
				tm_putstring("Button2 ON");
				tk_set_flg(flgid, (1<<0));
			}
			btn0 = btn;
		}
		tk_dly_tsk(100);
	}
}

/* LED task function1 */
void task_led1(INT stacd, void *exinf)
{
	UINT flgptn;

	while(1){
		tk_wai_flg(flgid, (1<<0), TWF_ANDW | TWF_BITCLR, &flgptn, TMO_FEVR);

		tk_wai_sem(semid, 1, TMO_FEVR);

		for(INT i = 0; i < 3; i++){
			out_w(GPIO_OUT_SET, (1<<25));
			tk_dly_tsk(500);
			out_w(GPIO_OUT_CLR, (1<<25));
			tk_dly_tsk(500);
		}

		tk_sig_sem(semid, 1);
	}
}

/* LED task function2 */
void task_led2(INT stacd, void *exinf)
{
	UINT flgptn;

	while(1){
		tk_wai_flg(flgid, (1<<1), TWF_ANDW | TWF_BITCLR, &flgptn, TMO_FEVR);

		tk_wai_sem(semid, 1, TMO_FEVR);

		for(INT i = 0; i < 5; i++){
			out_w(GPIO_OUT_SET, (1<<25));
			tk_dly_tsk(100);
			out_w(GPIO_OUT_CLR, (1<<25));
			tk_dly_tsk(100);
		}

		tk_sig_sem(semid, 1);
	}
}

int usermain(void)
{
	tm_putstring("Start usermain!!\n");

	/* Create event flag */
	flgid = tk_cre_flg(&cflg);

	/* Create semaphore */
	semid = tk_cre_sem(&csem);

	/* Button task */
	tskid_btn = tk_cre_tsk(&ctsk_btn);
	tk_sta_tsk(tskid_btn, 0);

	/* LED task1 */
	tskid_led1 = tk_cre_tsk(&ctsk_led1);
	tk_sta_tsk(tskid_led1, 0);

	/* LED task2 */
	tskid_led2 = tk_cre_tsk(&ctsk_led2);
	tk_sta_tsk(tskid_led2, 0);

	return 0;
}



