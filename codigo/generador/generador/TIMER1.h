//incluciones
#include <avr/io.h>
#include <stdlib.h>
//definiciones
#ifndef F_CPU
#define F_CPU 8000000L
#endif
#define resetCounterOn OCR1A

/*******************************************************************************************************************
Este "objeto" permite administrar una onda cuadrada, generada por el TIMER1, esta onda es tiene una salida por el 
bit1 del puerto B, tambien llamado OC1A, del atmega328P 
*******************************************************************************************************************/

//funciones publicas
void TIMER1_set_module(); //Configuracion inicial del Timer1
void TIMER1_set_frequency(char frequencyStr[] );// recibe la frecuencia por string que tendra la onda generada por el timer1
void TIMER1_set_on(); //Al invocarse la función, comienza a producir un sonido.
void TIMER1_set_off(); //Al invocarse la función, parar de reproducir un sonido.
void TIMER1_reset_module(); //Deja de reproducir sonido y setea la frecuencia en la frecuencia por defecto.