/*
 *** main.c
 */

#include <trykernel.h>

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

/* LED task */
UW	tskstk_led[1024/sizeof(UW)];	// Stack for LED task
ID	tskid_led;

void task_led(INT stacd, void *exinf);
T_CTSK	ctsk_led = {
	.tskatr		= TA_HLNG | TA_RNG3 | TA_USERBUF,
	.task		= task_led,
	.itskpri	= 10,
	.stksz		= 1024,
	.bufptr		= tskstk_led,
};

/* Button task function */
void task_btn(INT stacd, void *exinf)
{
	UW btn, btn0;

	/* Set GP14 to switch input */
	out_w(GPIO(14), (in_w(GPIO(14)) | GPIO_PUE) & ~GPIO_PDE);	// Pull-up setting
	out_w(GPIO_OE_CLR, (1<<14));								// Invalidate output
	out_w(GPIO_CTRL(14), 5);									// SIO function

	btn0 = in_w(GPIO_IN) & (1<<14);			// Set init value to GPIO_IN

	while(1){
		btn = in_w(GPIO_IN) & (1<<14);		// Read switch value
		if(btn != btn0){
			if(btn == 0){
				tm_putstring("Button ON");
				tk_wup_tsk(tskid_led);
			}
			btn0 = btn;
		}
		tk_dly_tsk(100);
	}
}

/* LED task function */
void task_led(INT stacd, void *exinf)
{
	while(1){
		tk_slp_tsk(TMO_FEVR);
		out_w(GPIO_OUT_SET, (1<<25));
		tk_dly_tsk(1000);
		out_w(GPIO_OUT_CLR, (1<<25));
	}
}

int usermain(void)
{
	tm_putstring("Start usermain!!\n");

	/* Button task */
	tskid_btn = tk_cre_tsk(&ctsk_btn);
	tk_sta_tsk(tskid_btn, 0);

	/* LED task */
	tskid_led = tk_cre_tsk(&ctsk_led);
	tk_sta_tsk(tskid_led, 0);

	return 0;
}



