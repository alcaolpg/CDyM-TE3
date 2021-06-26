/*
 * generador.c
 *
 * Created: 11/06/2021 18:54:46
 * Author : Agustín
 */ 

#include "serialPort.h"
#include "UART_con_buffers.h"
#include <string.h>
#define  F_CPU 16000000L
//variables de comunicaci�n Back/Foreground
//volatile static char BufferRX[64];
volatile static char Buffer[64];
volatile unsigned char FLAG_linea_recibida=0;

//Mensaje de bienvenida
char msg1[] = "Programa con interrupciones de RX \n\r";

int main(void)
{
	// INICIALIZACIONES
// 	SerialPort_Init(103); 		// Inicializo el Puerto Serie. Con 103 para BAUDRATE = 9600 @ 16MHz
// 	SerialPort_TX_Enable();		// Activo el Transmisor del Puerto Serie
// 	SerialPort_RX_Enable();		// Activo el Receptor del Puerto Serie
// 	SerialPort_RX_Interrupt_Enable();	// Activo Interrupci�n de recepcion.
// 	sei();								// Activo la mascara global de interrupciones (Bit I del SREG en 1)
	uart_cb_init(103);
	//strcpy(Buffer,msg1);
	//uart_cb_preparar_transmision(Buffer);
	//uart_cb_listo_para_transmitir();
	// Envio el mensaje de Bienvenida

	while(1)
	{
		if( FLAG_linea_recibida == 1)
		{
			//SerialPort_Send_String((char *)BufferRX);  // Eco del string (inciso a)
			//strcpy(BufferTX,BufferRX);	// Eco del string usando int TX (inciso b)
			uart_cb_ultima_recepcion(Buffer);
			uart_cb_preparar_transmision(Buffer);
			//UCSR0B |= (1<<TXCIE0);
			uart_cb_listo_para_transmitir();
			uart_cb_preparar_transmision("\r\nHasta aca, todo bien");
			uart_cb_listo_para_transmitir();
			FLAG_linea_recibida=0;
		}
		//otras tareas
	}
	return 0;
}

//*************************************************
//Handler de Interrupcion de byte Recibido
//**************************************************

ISR(USART_RX_vect){

	FLAG_linea_recibida = uart_cb_isr_rx();
	
// 	volatile char RX_Data = 0;
// 	static short int Index=0;
// 
// 	RX_Data = UDR0;
// 	if(RX_Data!='\r'){
// 		BufferRX[Index++]=RX_Data;
// 	}
// 	else{
// 		//	    BufferRX[Index++]='\r'; //opcional
// 		//		BufferRX[Index++]='\n';
// 		BufferRX[Index]='\0';
// 		Index=0;
// 		FLAG_linea_recibida=1;
// 	}
}

//*************************************************
//Handler de Interrupcion de Transmisi�n Completa TXC
//**************************************************

ISR(USART_TX_vect){ //handler de interrupci�n de TXC 

	uart_cb_isr_tx();
// 	static short int Txindex=0;
// 	
// 	if(BufferTX[Txindex]!='\0'){
// 		UDR0=BufferTX[Txindex];
// 		Txindex++;
// 	}
// 	else{
// 		UDR0='\r';
// 		UDR0='\n'; //ojo esto es posible porque tengo FIFO de 2 bytes en TX
// 		Txindex=0;
// 		uart_cb_transmision_completa();//deshabiito int de TXC hasta que necesite transmitir nuevamnete
// 	}
}