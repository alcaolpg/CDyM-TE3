

#include <avr/io.h>
#include "Timer1.h"

#include <stdio.h>
#include <util/delay.h>

 /* Test
	Se probara todas las frecuencias porque si
	 */

void testTodasLasFrecuencias(){
	TIMER1_set_module();		
	uint16_t frecuencia=90;
	char frecuenciaStr[20];
	TIMER1_set_on();
	while (1)
	{	
		sprintf(frecuenciaStr, "%d", frecuencia++);
		TIMER1_set_frequency(frecuenciaStr);
		_delay_ms(100);
	}
}
void testUnaFrecuencia(uint16_t frecuencia){
	TIMER1_set_module();
	char text[20];
	sprintf(text, "%d", frecuencia);
	TIMER1_set_frequency(text);
	TIMER1_set_on();
	//while (1);
}
int main(void)
{
	testTodasLasFrecuencias();
	//testUnaFrecuencia(100);
}

