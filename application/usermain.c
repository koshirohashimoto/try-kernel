/*
 *** usermain.c
 */

#include <trykernel.h>

UW	tskstk_1[1024/sizeof(UW)];	// Stack for Task1
ID	tskid_1;

/* Task1 create info */
void task_1(INT stacd, void *exinf);
T_CTSK ctsk_1 = {
		.tskatr		= TA_HLNG | TA_RNG3 | TA_USERBUF,
		.task		= task_1,
		.itskpri	= 10,
		.stksz		= 1024,
		.bufptr		= tskstk_1,
};

UW	tskstk_2[1024/sizeof(UW)];	// Stack for Task2
ID	tskid_2;

/* Task2 create info */
void task_2(INT stacd, void *exinf);
T_CTSK ctsk_2 = {
		.tskatr		= TA_HLNG | TA_RNG3 | TA_USERBUF,
		.task		= task_2,
		.itskpri	= 10,
		.stksz		= 1024,
		.bufptr		= tskstk_2,
};

/* Task1 function */
void task_1(INT stacd, void *exinf)
{
	tm_putstring("Start Task1!!\n");
	tk_ext_tsk();
}

/* Task2 function */
void task_2(INT stacd, void *exinf)
{
	tm_putstring("Start Task2!!\n");
	tk_ext_tsk();
}

int usermain(void)
{
	tm_putstring("Start usermain!!\n");

	/* Task1 */
	tskid_1 = tk_cre_tsk(&ctsk_1);
	tk_sta_tsk(tskid_1, 0);

	/* Task2 */
	tskid_2 = tk_cre_tsk(&ctsk_2);
	tk_sta_tsk(tskid_2, 0);

	return 0;
}



