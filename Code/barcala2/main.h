/*
 * main.h
 *
 * Created: 25/4/2022 14:53:59
 *  Author: Barcala
 */ 


#ifndef MAIN_H_
#define MAIN_H_
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdlib.h>
#include <string.h>

#include "serialPort.h"		// Para trabajar con el Puerto serial
#include "lcd.h"			// Para utilizar libreria de LCD
#include "dht11.h"			// Para utilizar libreria de DHT11.
#endif /* MAIN_H_ */