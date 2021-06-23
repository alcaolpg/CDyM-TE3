/*
 * generador.c
 *
 * Created: 11/06/2021 18:54:46
 * Author : Agustín
 */ 

#include "serialPort.h"
#include <string.h>
#define  F_CPU 16000000L
//variables de comunicaci�n Back/Foreground
volatile static char BufferRX[64];
volatile static char BufferTX[64];
volatile unsigned char FLAG_linea_recibida=0;

//Mensaje de bienvenida
char msg1[] = "Programa con interrupciones de RX \n\r";

int main(void)
{
	// INICIALIZACIONES
	SerialPort_Init(103); 		// Inicializo el Puerto Serie. Con 103 para BAUDRATE = 9600 @ 16MHz
	SerialPort_TX_Enable();		// Activo el Transmisor del Puerto Serie
	SerialPort_RX_Enable();		// Activo el Receptor del Puerto Serie
	SerialPort_RX_Interrupt_Enable();	// Activo Interrupci�n de recepcion.
	sei();								// Activo la mascara global de interrupciones (Bit I del SREG en 1)

	SerialPort_Send_String(msg1);    // Envio el mensaje de Bienvenida

	while(1)
	{
		if( FLAG_linea_recibida == 1)
		{
			//SerialPort_Send_String((char *)BufferRX);  // Eco del string (inciso a)
			strcpy(BufferTX,BufferRX);	// Eco del string usando int TX (inciso b)
			UCSR0B |= (1<<TXCIE0);
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
	
	volatile char RX_Data = 0;
	static short int Index=0;

	RX_Data = UDR0;
	if(RX_Data!='\r'){
		BufferRX[Index++]=RX_Data;
	}
	else{
		//	    BufferRX[Index++]='\r'; //opcional
		//		BufferRX[Index++]='\n';
		BufferRX[Index]='\0';
		Index=0;
		FLAG_linea_recibida=1;
	}
}

//*************************************************
//Handler de Interrupcion de Transmisi�n Completa TXC
//**************************************************

ISR(USART_TX_vect){ //handler de interrupci�n de TXC 

	static short int Txindex=0;
	
	if(BufferTX[Txindex]!='\0'){
		UDR0=BufferTX[Txindex];
		Txindex++;
	}
	else{
		UDR0='\r';
		UDR0='\n'; //ojo esto es posible porque tengo FIFO de 2 bytes en TX
		Txindex=0;
		UCSR0B &=~(1<<TXCIE0);//deshabiito int de TXC hasta que necesite transmitir nuevamnete
	}
}