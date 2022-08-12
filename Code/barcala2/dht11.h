/*
 * dht11.h
 *
 * Created: 6/6/2022 14:50:54
 *  Author: Barcala
 */ 


#ifndef DHT11_H_
#define DHT11_H_
#include "main.h"

void DHT_init();
uint8_t Cargar_dato();
void DHT_Scan(uint8_t *h_hum, uint8_t *l_hum, uint8_t *h_temp, uint8_t *l_temp);


#endif /* DHT11_H_ */