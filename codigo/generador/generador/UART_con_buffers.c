/*
 * UART_con_buffers.c
 *
 * Created: 23/06/2021 15:48:26
 *  Author: Agustín
 */ 
#include "serialPort.h"

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