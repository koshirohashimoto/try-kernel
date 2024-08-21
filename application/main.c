#include <trykernel.h>

/* task control data */
UINT cur_task 	= 0;	// current task ID
UINT next_task 	= 0;	// next task ID

/* Stack info */
#define STACK_SIZE 1024
UW stack_1[STACK_SIZE/sizeof(UW)];
UW stack_2[STACK_SIZE/sizeof(UW)];


/* 時間待ち関数 */
static void delay_ms( UINT ms)
{
    UINT cnt = ms/TIMER_PERIOD;

    while(cnt) {
        if((in_w(SYST_CSR) & SYST_CSR_COUNTFLAG)!=0) {  /* TIMER_PERIOD経過するとフラグがセット */
            cnt--;
        }
    }
}

int main(void)
{
	tm_com_init();

	tm_putstring("hello,world\n");

    while(1) {
        out_w(GPIO_OUT_XOR, (1<<25));   /* LEDの表示反転 */
        delay_ms(500);                  /* 0.5秒待ち */
    }
    return 0;
}
