/*
 * TIMER1.h
 *
 * Created: 15/6/2021 10:01:46
 *  Author: UNLP
 */ 

//Contstantes
#ifdef 
#endif

void set_module(); //Al invocarse, debe setear todos los parámetros que sean necesarios.
void set_frequency(char arr[] );// Debe tener una función que reciba como parámetro una frecuencia en forma de string (arreglo de chars o puntero a char) y convertirla a lo que se necesite (ver atoi(), puede ser útil)
void set_on(); //Al invocarse la función, debe comenzar a producir un sonido.
void set_off(); //Al invocarse la función, debe parar de reproducir un sonido.
void reset_module(); //Deja de reproducir sonido y setea la frecuencia en la frecuencia por defecto.