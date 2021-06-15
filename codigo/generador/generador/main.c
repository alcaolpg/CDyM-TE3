

#include <avr/io.h>
#include "Timer1.h"

int main(void)
{
    /* Replace with your application code */
	TIMER1_set_module();
	TIMER1_set_frequency("100");
	TIMER1_set_on();

    while (1) 
    {
    }
	
}

