/*
 *** Initialize Task
 */

#include <trykernel.h>
#include <knldef.h>

void initsk(INT stacd, void *exinf);		// program for init task
UW	tskstk_ini[256/sizeof(UW)];				// stack for init task
ID	tskid_ini;								// ID for init task

T_CTSK ctsk_ini = {
		.tskadr		= TA_HLNG | TA_RNG0 | TA_USERBUF,
		.task		= initsk,
		.itskpri	= 1,
		.stksz		= sizeof(tskstk_ini),
		.bugptr		= tskstk_ini,
};

void initsk(INT stacd, void *exinf)
{
	tm_com_init();							// Initialize serial communication
	tm_putstring("Start TryKernel!!\n");

	usermain();
	tk_ext_tsk();
}

int main(void)
{
	tskid_ini = tk_cre_tsk(&ctsk_ini);		// Create init task
	tk_sta_tsk(tskid_ini, 0);				// Start init task

	while(1);
}
