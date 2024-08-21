#include <trykernel.h>

/* Task control data */
UINT cur_task 	= 0;		// current task ID
UINT next_task 	= 0;		// next task ID

#define MAX_FNC_ID 2		// number of tasks
void *ctx_tbl[MAX_FNC_ID];	// pointer to the registered context data

/* Stack info */
#define STACK_SIZE 1024
UW stack_1[STACK_SIZE/sizeof(UW)];
UW stack_2[STACK_SIZE/sizeof(UW)];


/* Delay function */
static void delay_ms(UINT ms)
{
    UINT cnt = ms / TIMER_PERIOD;

    while(cnt){
        if((in_w(SYST_CSR) & SYST_CSR_COUNTFLAG) != 0){
            cnt--;
        }
    }
}

/* Task1 */
void task_1(void)
{
	while(1){
		out_w(GPIO_OUT_SET, (1<<25));	// Turn on LED light
		delay_ms(500);					// Wait 500msec

		next_task = 2;
		dispatch();
	}
}

/* Task2 */
void task_2(void)
{
	while(1){
		out_w(GPIO_OUT_CLR, (1<<25));	// Turn off LED light
		delay_ms(500);					// Wait 500msec

		next_task = 1;
		dispatch();
	}
}

/* Main function */
int main(void)
{
	/* Initialize task */
	ctx_tbl[0] = make_context(stack_1, sizeof(stack_1), task_1);
	ctx_tbl[1] = make_context(stack_2, sizeof(stack_2), task_2);

	next_task = 1;
	dispatch();

	return 0;
}

/* Main function for Part2 */
/*
int main(void)
{
	tm_com_init();
	tm_putstring("Hello World!!\n");

    while(1){
        out_w(GPIO_OUT_XOR, (1<<25));	// Switch LED light
        delay_ms(500);                  // Wait 500msec
    }

    return 0;
}
*/
