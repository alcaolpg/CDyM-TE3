/*
 * UART_con_buffers.c
 *
 * Created: 23/06/2021 15:48:26
 *  Author: Agustín
 */ 
#include "serialPort.h"
#include <string.h>

volatile static char BufferRX[64];
volatile static char BufferTX[64];

void uart_cb_init(uint8_t serial_port_value)
{
	SerialPort_Init(serial_port_value); 		// Inicializo el Puerto Serie. Con 103 para BAUDRATE = 9600 @ 16MHz
	SerialPort_TX_Enable();		// Activo el Transmisor del Puerto Serie
	SerialPort_RX_Enable();		// Activo el Receptor del Puerto Serie
	SerialPort_RX_Interrupt_Enable();	// Activo Interrupci�n de recepcion.
	sei();
}

void uart_cb_listo_para_transmitir()
{
	UCSR0B |= (1<<TXCIE0);
}

void uart_cb_transmision_completa()
{
	UCSR0B &=~(1<<TXCIE0);
}

char uart_cb_isr_rx()
{
		volatile char RX_Data = 0;
		static short int Index=0;

		RX_Data = UDR0;
		if(RX_Data!='\r'){
			BufferRX[Index++]=RX_Data;
		}
		else{
			BufferRX[Index]='\0';
			Index=0;
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
	static short int Txindex=0;
	
	if(BufferTX[Txindex]!='\0'){
		UDR0=BufferTX[Txindex];
		Txindex++;
	}
	else{
		UDR0='\r';
		UDR0='\n'; //ojo esto es posible porque tengo FIFO de 2 bytes en TX
		Txindex=0;
		uart_cb_transmision_completa();//deshabiito int de TXC hasta que necesite transmitir nuevamnete
	}
}

void uart_cb_preparar_transmision(char *paquete)
{
	strcpy(BufferTX,paquete);
}
