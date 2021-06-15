//incluciones
#include <avr/io.h>
#include <stdlib.h>
//definiciones
#ifndef F_CPU
#define F_CPU 8000000L
#endif
#define resetCounterOn OCR1A
#define F_min 100
#define F_max 10000

/*******************************************************************************************************************
Este "objeto" permite administrar una onda cuadrada, generada por el TIMER1, esta onda es tiene una salida por el 
bit1 del puerto B, tambien llamado OC1A, del atmega328P 
*******************************************************************************************************************/

//funciones publicas
void TIMER1_set_module(); //Configuracion inicial del Timer1
uint8_t TIMER1_set_frequency(char frequencyStr[] );// recibe la frecuencia por string que tendra la onda generada por el timer1, retorna 1 si esta entre 100 y 10000, 0 en caso contrario
void TIMER1_set_on(); //Al invocarse la funci�n, comienza a producir un sonido.
void TIMER1_set_off(); //Al invocarse la funci�n, parar de reproducir un sonido.
void TIMER1_reset_module(); //Deja de reproducir sonido y setea la frecuencia en la frecuencia por defecto.