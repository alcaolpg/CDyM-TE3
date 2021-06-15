#include "string.h"

#define tam_maximo_comando 32
#define frecuencia_minima 100
#define frecuencia_maxima 10000

unsigned char estado = 1;
char frecuencia_actual[5] = "6435";
char frecuencia_nueva[5] = "6435";
char comando_detectado[tam_maximo_comando];
char indice_lectura = 0;

void mef_generador(char *buffer, int indice_escritura)
{
    switch (estado)
    {
    case 1:
        estado = set_rst();
        break;
    case 2:
        estado = captar(buffer, indice_escritura);
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
        break;
    }
}

unsigned char set_rst()
{
    unsigned char proximo_estado = 2;
    /*Se setean todos los parametros del estaddo por defecto*/
    TIMER1_reset_module();
    TIMER1_set_off();
    strcpy(frecuencia_actual, "6435");
    strcpy(frecuencia_nueva, "6435");
    
    return proximo_estado;
}

unsigned char captar(char *buffer, int indice_escritura) //Preguntar como se translada el indice de escritura
{
    /*Se espera el ingreso de la tecla ENTER*/
    unsigned char proximo_estado = 2;

    if (buffer[indice_escritura - 1] == "\0")
    {
        copiar_comando(buffer, indice_lectura);
        indice_lectura = indice_escritura;
        proximo_estado = 3;
    }

    return proximo_estado;
}

unsigned char interpretar()
{
    /* Se interpretan las cadenas de caracteres dentro del buffer circular, desde la posicion de la ultima lectura, hasta la
    posicion de la tecla ENTER*/
    unsigned char proximo_estado = 7;
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
    return proximo_estado;
}

unsigned char OFF()
{
    /*Se detiene la reproduccion de sonido*/
    unsigned char proximo_estado = 2;
    TIMER1_set_off();
    return proximo_estado;
}

unsigned char FREQ()
{
    /*Se establece la frecuencia a reproducior segun el valor recibido*/
    unsigned char proximo_estado = 2;
    TIMER1_set_frequency(frecuencia_nueva);
    strcpy(frecuencia_actual,frecuencia_nueva);
    return proximo_estado;   
}

unsigned char com_invalid()
{
    /*Se informa que el comando recibido es invalido*/
    unsigned char proximo_estado = 7;

    return proximo_estado;
}

void copiar_comando(char *buffer, int indice_lectura_local)
{
    char indice_copia = 0;
    while ((buffer[indice_lectura_local] != "\0") && (indice_copia < (tam_maximo_comando - 1)))
    {
        comando_detectado[indice_copia] = buffer[indice_lectura_local];
        indice_lectura_local++;
        indice_copia++;
    }
    comando_detectado[indice_copia] = "\0";
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