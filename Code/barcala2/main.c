/*
 * barcala2.c
 *
 * Created: 11/4/2022 14:06:39
 * Author : Barcala
 */ 

#include "main.h"

static char msj_error[]= "Comando no valido\n\r";
volatile static unsigned char flag_registrador = 0;

void main_update(void){
	char cadena[6]=""; //En esta variable se va a guardar la cadena ingresada por el usuario
	SerialPort_Get_String_From_Buffer(cadena);
	if (strcmp((const char*)cadena,(const char*)"ON")==0) //Si el usuario ingreso el comando 'ON'
	{
		SerialPort_Send_String("Encendido\n\r");
		flag_registrador = 1; //Enciendo el flag para mostrar del sensor
	}
	else
	{
		if (strcmp((const char*)cadena,(const char*)"OFF")==0) //Si el usuario ingreso el comando 'OFF'
		{
			SerialPort_Send_String("Apagado\n\r");
			if (flag_registrador){	//Apago el flag para mostrar del sensor
				flag_registrador = 0;
			}
			SerialPort_TX_Interrupt_Disable();
		}
		else
		{
			if (strcmp((const char*)cadena,(const char*)"RST")==0) //Si el usuario ingreso el comando 'RST'
			{
				mostrarMenu();
				SerialPort_TX_Interrupt_Enable();
				if (flag_registrador){	//Apago el flag para mostrar del sensor
					flag_registrador = 0;
				}
			}
			else //Caso en el que el usuario no ingreso ningun comando valido
			{
				SerialPort_Send_String(msj_error);
			}
		}
	}
}

int main(void)
{
	DHT_init();			//configurar dht11
	
	uint8_t h_temp;
	uint8_t l_temp;
	uint8_t h_hum;
	uint8_t l_hum;
	char data[5];
	
	SerialPort_Init(0x67);						//Configuro el UART 9600bps, 8 bit data, 1 stop @ F_CPU = 16MHz.
												
	SerialPort_TX_Enable();						//Inicio el transmisor
	SerialPort_TX_Interrupt_Enable();
												
	SerialPort_RX_Enable();						//Inicio el receptor
	SerialPort_RX_Interrupt_Enable();			
												
	sei();										//Activo el flag global para interrupciones
												
	mostrarMenu();								//Muestro el menu principal
	
	while (1)
	{
		if(get_flag_enter()){		//El usuario ingreso la tecla ENTER
			main_update();			//El programa responde dependiendo del comando
			set_flag_enter(0);
			SerialPort_Send_String("\n\r");
		}
		else
		if (flag_registrador){	//Si se ingreso del comando ON
			DHT_Scan(&h_hum, &l_hum, &h_temp, &l_temp);
			
			if ((h_hum < (255)) & (h_temp < (255)) & (h_hum < (255)) & (h_temp < (255)))
			{
				itoa(h_hum,data,10);
				SerialPort_Send_String("Humedad: ");
				SerialPort_Send_String(data);
				SerialPort_Send_String(".");
				itoa(l_hum,data,10);
				SerialPort_Send_String(data);
				SerialPort_Send_String("\r\n");
				SerialPort_Send_String("Temperatura: ");
				itoa(h_temp,data,10);
				SerialPort_Send_String(data);
				SerialPort_Send_String(".");
				itoa(l_temp,data,10);
				SerialPort_Send_String(data);
				SerialPort_Send_String("\r\n");
			}
			else
			{
				SerialPort_Send_String("Error.");
			}
			_delay_ms(1200);
		}
	}
	return 0;
}
