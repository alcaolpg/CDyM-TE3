/*
 * uart_rx.c
 *
 * Created: 18/06/2021 23:58:32
 *  Author: GOD
 */ 

//recepción de datos de la uart

#include "avr/io.h"
#include "avr/interrupt.h"

void RX_enable(void);
void RX_interrupt_enable(void);
void set_uart_rx(unsigned char *buff_adress, int buff_size);
void recive_data(void);
void ready_to_recive(void);
void done_reciving(void);
void recive_buffer_content(char);

unsigned char *buffer;
unsigned char index; //puntero de lectura para el buffer
unsigned char size_buff;
unsigned char FLAGRECIVE;

void RX_enable(void)
{
	UCSR0B |= (1<<RXEN0);
}

void RX_interrupt_enable(void)
{
	UCSR0B |= (1<<UDRIE0); //ver esto
}

void done_reciving(void)
{
	FLAGRECIVE = 1;
}
void recive_data(char * RX_Data){
	RX_Data = UDR0;
}
void set_uart_rx(unsigned char *buff_adress, int buff_size){
	buffer = buff_adress;
	index = 0;
	size_buff = buff_size;
	RX_enable();
	RX_interrupt_enable();
}

char recive_buffer_content(char * c)
{
	volatile char RX_Data = 0;

	recive_data(RX_Data);
	if(RX_Data!='\r' && index < size_buff){
		buffer[index++]=RX_Data;
	}
	else{
		//	    BufferRX[Index++]='\r'; //opcional
		//		BufferRX[Index++]='\n';
		buffer[index]='\0';
		index=0;
		done_reciving();
	}
}

