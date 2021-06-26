/*
 * UART_con_buffers.c
 *
 * Created: 23/06/2021 15:48:26
 *  Author: Agustín
 */ 
#include "serialPort.h"
#include <string.h>
#include <avr/io.h>
#include <stdint.h>
#define tam_buffer 256

volatile static char BufferRX[tam_buffer];
volatile static char BufferTX[tam_buffer];
unsigned static char nivel_bufferTx = 0;

void uart_cb_init(unsigned char serial_port_value)
{
	SerialPort_Init(serial_port_value);
	SerialPort_TX_Enable();
	SerialPort_RX_Enable();
	SerialPort_RX_Interrupt_Enable();
	SerialPort_Send_String("\n");
	sei();
}

void uart_cb_listo_para_transmitir()
{
	UCSR0B |= (1<<TXCIE0);
}

void uart_cb_transmision_completa()
{
	UCSR0B &=~ (1<<TXCIE0);
}


void uart_cb_enviar_dato(char dato)
{
	SerialPort_Wait_For_TX_Buffer_Free();
	UDR0 = dato;
}

char uart_cb_recibir_dato()
{
	return UDR0;
}

char uart_cb_isr_rx()
{
		volatile char RX_Data = '\r';
		static short int rxIndex=0;

		RX_Data = uart_cb_recibir_dato();

		if(RX_Data != '\r'){
			if(rxIndex >= tam_buffer)
			{
				rxIndex = 0;
			}
			BufferRX[rxIndex++] = RX_Data;
		}
		else{
			BufferRX[rxIndex] = '\0';
			rxIndex = 0;
			return 1;
		}
		return 0;
}

void uart_cb_ultima_recepcion(char *paquete)
{
	strcpy(paquete,BufferRX);
}

void uart_cb_isr_tx()
{
	static short int txIndex = 0;
	
	if(BufferTX[txIndex] != '\0' && txIndex < tam_buffer)
	{
		uart_cb_enviar_dato(BufferTX[txIndex++]);
	}
	else
	{
		uart_cb_enviar_dato('\r');
		uart_cb_enviar_dato('\n'); //ojo esto es posible porque tengo FIFO de 2 bytes en TX
		txIndex = 0;
		BufferTX[txIndex] = '\0';
		nivel_bufferTx = 0;
		
		uart_cb_transmision_completa();//deshabiito int de TXC hasta que necesite transmitir nuevamnete
	}
}

void uart_cb_preparar_transmision(char *paquete)
{
	nivel_bufferTx = nivel_bufferTx + strlen(paquete) + 1;
	if (nivel_bufferTx < tam_buffer)
	{
		strcat(BufferTX,paquete);
	}
	else
	{
		nivel_bufferTx = 0;
	}
}
