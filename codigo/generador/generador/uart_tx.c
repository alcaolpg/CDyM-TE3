/*
 * CFile1.c
 *
 * Created: 14/06/2021 14:46:17
 *  Author: Agustín
 */ 
#include "avr/io.h"
#include "avr/interrupt.h"

void TX_enable(void);
void TX_interrupt_enable(void);
void set_uart_tx(int buff_size, unsigned char *buff_adress);
void send_data(char data);
void ready_to_send(void);
void done_sending(void);
void send_buffer_content(void);

unsigned int buffer_size;
unsigned char *buffer;

void TX_enable(void)
{
	UCSR0B |= (1<<TXEN0);
}

void TX_interrupt_enable(void)
{
	UCSR0B |= (1<<UDRIE0);
}

void set_uart_tx(int buff_size, unsigned char *buff_adress)
{
	buffer_size = buff_size;
	buffer = buff_adress;
	TX_enable();
	TX_interrupt_enable();
}

void send_data(char data)
{
	UDR0 = data;
}

void ready_to_send(void)
{
	UCSR0B |= (1<<TXCIE0);
}

void done_sending(void)
{
	UCSR0B &=~(1<<TXCIE0);	
}

void send_buffer_content(void)
{
	static unsigned int i = 0;
	
	if ((buffer[i] != "\0") && (i < buffer_size))
	{
		send_data(buffer[i]);
		i++;
	}
	else
	{
		send_data("\r");
		send_data("\n");
		i = 0;
		done_sending();
	}
}

