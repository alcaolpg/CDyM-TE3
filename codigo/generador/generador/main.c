/*
 * generador.c
 *
 * Created: 11/06/2021 18:54:46
 * Author : Agustín
 */ 

#include "serialPort.h"
#include "UART_con_buffers.h"
#include "mef.h"
#include <string.h>
#include <avr/io.h>
#include <stdint.h>
#define  F_CPU 8000000L

volatile static char Buffer[64];
char FLAG_linea_recibida=0;

int main(void)
{

	uart_cb_init(51);

	while(1)
	{
		mef_generador(&FLAG_linea_recibida);
	}
	return 0;
}


ISR(USART_RX_vect)
{
	FLAG_linea_recibida = uart_cb_isr_rx();
}

ISR(USART_TX_vect)
{
	uart_cb_isr_tx();
}