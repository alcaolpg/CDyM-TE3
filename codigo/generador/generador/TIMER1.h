//incluciones
#include <avr/io.h>
#include <stdlib.h>
//definiciones
#ifndef F_CPU
#define F_CPU 8000000L
#endif

#define resetCounterOn OCR1A


//funciones publicas
void TIMER1_set_module(); //Al invocarse, debe setear todos los parámetros que sean necesarios.
void TIMER1_set_frequency(char arr[] );// Debe tener una función que reciba como parámetro una frecuencia en forma de string (arreglo de chars o puntero a char) y convertirla a lo que se necesite (ver atoi(), puede ser útil)
void TIMER1_set_on(); //Al invocarse la función, debe comenzar a producir un sonido.
void TIMER1_set_off(); //Al invocarse la función, debe parar de reproducir un sonido.
void TIMER1_reset_module(); //Deja de reproducir sonido y setea la frecuencia en la frecuencia por defecto.