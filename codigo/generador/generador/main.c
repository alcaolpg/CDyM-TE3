/*
 * generador.c
 *
 * Created: 11/06/2021 18:54:46
 * Author : Agustín
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart_rx.h"
#include "uart_tx.h"
#include <string.h>
#define tam_buffer 64

char bufferRX[tam_buffer];
char bufferTX[tam_buffer];

char msg[] = "Hola Mundo";


int main(void)
{
    /* Replace with your application code */
	UCSR0B = 0;
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
	UBRR0H = (unsigned char)(0x33>>8);
	UBRR0L = (unsigned char)0x33;
	
	set_uart_rx(bufferRX, tam_buffer);
	set_uart_tx(tam_buffer, bufferTX);
	
	strcpy(bufferTX,msg);
	ready_to_send();
	
    while (1) 
    {
    }
}

ISR(USART_RX_vect)
{
	recive_buffer_content();
	strcpy(bufferTX,bufferRX);
	ready_to_send();
}

ISR(USART_TX_vect)
{
	send_buffer_content();
}

