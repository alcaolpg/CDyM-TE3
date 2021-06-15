#include "Timer1.h"

//parametros de configuracion del timer
volatile uint8_t Preescaler=1;

//Funciones globales pero privadas al archivo TIMER1.c
void setOutPB1(){
	DDRB=(1<<PB1); //PB1=salida
}
void setModeTogle(){
	TCCR1A=(1<<COM1A0); //COM1A=Togle  no funciona en modo PWM
}
void setModeCTCnoClock(){
	TCCR1B=0; //Modo CTC no prescaler
}
void setModeCTCnoPreescaler(){
	TCCR1B=(1<<WGM12)|(1<<CS10); //Modo CTC no prescaler
}
/*
void setModeCTCPreescaler8(){
	TCCR1B=(1<<WGM12)|(1<<CS11); //Modo CTC prescaler 8
}
void setModeCTCPreescaler64(){
	TCCR1B=(1<<WGM12)|(1<<CS11)|(1<<CS10); //Modo CTC prescaler 64
}
void setModeCTCPreescaler256(){
	TCCR1B=(1<<WGM12)|(1<<CS12); //Modo CTC  prescaler 256
}
void setModeCTCPreescaler1024(){
	TCCR1B=(1<<WGM12)|(1<<CS12)|(1<<CS10); //Modo CTC prescaler 1024
}
*/
void setTopeDelContador(uint16_t frecuenciaDeseada){
	resetCounterOn= (F_CPU/(2*1*frecuenciaDeseada))-1;
}


//funciones publicas
void TIMER1_set_module(){
	TIMER1_reset_module();
	setOutPB1();
	setModeTogle();
	} 
void TIMER1_set_frequency(char frequency[] ){
	setTopeDelContador(atoi(frequency));
}
void TIMER1_set_on(){	
	setModeCTCnoPreescaler();
} 
void TIMER1_set_off(){
	setModeCTCnoClock();
}
void TIMER1_reset_module(){
	TIMER1_set_off();
	setTopeDelContador(6435);
}