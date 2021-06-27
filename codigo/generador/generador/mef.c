#include "string.h"
#include "UART_con_buffers.h"
#include "TIMER1.h"
#include <stdlib.h>

#define tam_maximo_comando 7
#define frecuencia_minima 100
#define frecuencia_maxima 10000
#define tam_buffer 256

void mef_generador(char *comando_entrante);
unsigned char set_rst();
unsigned char captar(char *comando_entrante);
unsigned char interpretar();
unsigned char ON();
unsigned char OFF();
unsigned char FREQ();
unsigned char com_invalid();
char es_comando(char *comando_esperado);
char es_frecuencia();
void mensaje_inicial();

unsigned char estado = 1;
char frecuencia_actual[6] = "6435";
char comando_detectado[tam_buffer];

void mef_generador(char *comando_entrante)
{
    switch (estado)
    {
    case 1:
        estado = set_rst();
        break;
    case 2:
        estado = captar(comando_entrante);
        break;
    case 3:
        estado = interpretar();
        break;
    case 4:
        estado = ON();
        break;
    case 5:
        estado = OFF();
        break;
    case 6:
        estado = FREQ();
        break;
    case 7:
        estado = com_invalid();
        break;
    }
}

unsigned char set_rst()
{
    unsigned char proximo_estado = 2;
    /*Se setean todos los parametros del estaddo por defecto*/
    TIMER1_reset_module();
    strcpy(frecuencia_actual, "6435");
	mensaje_inicial();
    
    return proximo_estado;
}

unsigned char captar(char *comando_entrante)
{
    /*Se espera el ingreso de la tecla ENTER*/
    unsigned char proximo_estado = 2;
	
	if (*comando_entrante)
	{
		*comando_entrante = 0;
		proximo_estado = 3;
	}
    return proximo_estado;
}

unsigned char interpretar()
{
    /* Se interpretan las cadenas de caracteres dentro del buffer circular, desde la posicion de la ultima lectura, hasta la
    posicion de la tecla ENTER*/
    unsigned char proximo_estado = 7;
	uart_cb_ultima_recepcion(comando_detectado);
	
    if(es_comando("ON"))
    {
        proximo_estado = 4;
        return proximo_estado;
    }
    if(es_comando("OFF"))
    {
        proximo_estado = 5;
        return proximo_estado;
    }
    if (es_comando("RST"))
    {
        proximo_estado = 1;
        return proximo_estado;
    }
    if (es_frecuencia())
    {
        proximo_estado = 6;
        return proximo_estado;
    }

    return proximo_estado;
}

unsigned char ON()
{
    /*Se comienza a reproducir un sonido*/
    unsigned char proximo_estado = 2;
    TIMER1_set_on();
	uart_cb_preparar_transmision("Encendido\r\n");
	uart_cb_listo_para_transmitir();
    return proximo_estado;
}

unsigned char OFF()
{
    /*Se detiene la reproduccion de sonido*/
    unsigned char proximo_estado = 2;
    TIMER1_set_off();
	uart_cb_preparar_transmision("Apagado\r\n");
	uart_cb_listo_para_transmitir();
    return proximo_estado;
}

unsigned char FREQ()
{
    /*Se establece la frecuencia a reproducior segun el valor recibido*/
    unsigned char proximo_estado = 2;
    strcpy(frecuencia_actual,comando_detectado);
	TIMER1_set_frequency(frecuencia_actual);
	uart_cb_preparar_transmision("Frecuencia: ");
	uart_cb_preparar_transmision(frecuencia_actual);
	uart_cb_preparar_transmision("\r\n");
	uart_cb_listo_para_transmitir();
    return proximo_estado;   
}

unsigned char com_invalid()
{
    /*Se informa que el comando recibido es invalido*/
    unsigned char proximo_estado = 2;
    uart_cb_preparar_transmision("Comando invalido\r\n");
	uart_cb_listo_para_transmitir();
    return proximo_estado;
}


char es_comando(char *comando_esperado)
{
    return !strcmp(comando_esperado,comando_detectado);
}

char es_frecuencia()
{
    char i = 0;
    char es_frec = 1;
    unsigned int frec;

    while((comando_detectado == "\0") && (i < tam_maximo_comando))
    {
        if((comando_detectado[i] < "0") || (comando_detectado[i] > "9"))
        {
            es_frec = 0;
            return es_frec;
        }
    }

    frec = atoi(comando_detectado);
    if ((frec < frecuencia_minima) || (frec > frecuencia_maxima))
    {
        es_frec = 0;
    }
    return es_frec;
}

void mensaje_inicial()
{
	uart_cb_preparar_transmision("Generador de sonidos digitales programable\r\n");
	uart_cb_preparar_transmision("Ingrese frecuencia (100 - 10000 Hz)\r\n");
	uart_cb_preparar_transmision("ON: Encendido | OFF: Apagado | RST: Reiniciar\r\n");
	uart_cb_listo_para_transmitir();
}