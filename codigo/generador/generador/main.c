

#include <avr/io.h>
#include "Timer1.h"

#include <stdio.h>
#include <util/delay.h>

int main(void)
{
	
	
    /* Test
	Se probara todas las frecuencias porque si
	 */
	
	TIMER1_set_module();
	TIMER1_set_on();
	uint16_t fr=1;
	char text[20];
    while (1) 
    {
		
		sprintf(text, "%d", fr++);
		TIMER1_set_frequency(text);
		_delay_ms(100);
	//	TIMER1_set_off();
	//	
    }
	
}

