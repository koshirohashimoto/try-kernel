/*
 * syslib.c
 *
 *  Created on: 2024/08/20
 *      Author: KoshiroHashimoto
 */

#include <trykernel.h>
#include <knldef.h>

/* Initialize UART0 */
void tm_com_init(void)
{
	out_w(UART0_BASE+UARTx_IBRD, 67);
	out_w(UART0_BASE+UARTx_FBRD, 52);
	out_w(UART0_BASE+UARTx_LCR_H, 0x70);
	out_w(UART0_BASE+UARTx_CR, UART_CR_RXE|UART_CR_TXE|UART_CR_EN);
}

/* UART for debugging */
UINT tm_putstring(char* str)
{
	UINT	cnt = 0;

	while(*str)
	{
		while((in_w(UART0_BASE+UARTx_FR) & UART_FR_TXFF) != 0);
		out_w(UART0_BASE+UARTx_DR, *str++);
		cnt++;
	}
	return cnt;
}



