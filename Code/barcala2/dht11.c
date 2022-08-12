/*
 * dht11.c
 *
 * Created: 6/6/2022 14:50:31
 *  Author: Barcala
 */ 

#include "dht11.h"

void DHT_init() {
	DDRC |= (1<<PORTC0);	//Salida
	PORTC |= (1<<PORTC0);
		
}

uint8_t Cargar_dato()						/* Leer 8 bits en 4ms aproximadamente*/
{
	uint8_t contador;
	uint8_t aux = 0;
	for (int i=0; i<8; i++)
	{
		while((PINC & (1<<PORTC0)) == 0)		// descarto la parte en bajo de la señal del dato.
				{
					_delay_us(1);
					contador++;
				}

		contador = 0;							// Inicio el contador en 0.
		while(PINC & (1<<PORTC0))				// Mientras la señal esta en 1.
		{
			_delay_us(1);
			contador++;
		}
		if((contador)<40){				//si el tiempo es mayor a 28us, entonces almacenamos un 1. En caso contrario es un 0.
			aux = (aux<<1);					//shift de la variable una unidad a la izquierda
		}
		else
		{
			aux = (aux<<1)|(0x01);			// shift y hacemos un or con 1 en la posicion final. para ingresar el 1.
		}
	}
	return aux;
}


void DHT_Scan(uint8_t *h_hum, uint8_t *l_hum, uint8_t *h_temp, uint8_t *l_temp) //Retorna 2 datos enteros.
{	
	uint8_t check_sum;
	
	PORTC &=~(1<<PORTC0);				// colocamos en 0 la salida durante 18ms
	_delay_ms(20);
	PORTC |= (1<<PORTC0);				// colocamos en 1 la salida
	DDRC &=~(1<<PORTC0);				//Convertimos el puerto en entrada.
	
	while(PINC & (1<<PORTC0));			//Espero a que llegue el 0 en la parte baja de la respuesta.
	while((PINC & (1<<PORTC0))==0);		//cuando lee 0 espera durante 80us.
	while(PINC & (1<<PORTC0));			//cuando lee 1 espera durante 80us.  Tiempos, donde en dispositivo informa q va a transmitir.
	
	*h_hum = Cargar_dato();
	*l_hum = Cargar_dato();
	*h_temp= Cargar_dato();
	*l_temp = Cargar_dato();
	check_sum = Cargar_dato();
	

	
	if (check_sum == (*h_hum + *l_hum + *h_temp + *l_temp))  // sumar todos h y l hum y temp. y verificar que sea igual a check_sum.
	{
		
	}
	else
	{
		*h_hum = 255;
		*l_hum = 255;
		*h_temp = 255;
		*l_temp = 255;
	}	
	PORTC |= (1<<PORTC0);
	DDRC |= (1<<PORTC0);	//Salida	
	
}