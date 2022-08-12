# avr-dht11-uart
Implementacion de un registrador de datos de temperatura y humedad ambiente a partir del sensor digital DHT11 y el periférico de comunicación serie. El archivo de Proteus realizado en Proteus 8 Professional 8.10 SP0.

# Funcionamiento
Al iniciar el sistema deberá presentarte en la pantalla de una terminal serie el menú de opciones para que el usuario comande el registrador.

Los comandos son:

![imagen](https://user-images.githubusercontent.com/42872959/184392265-96feb7d2-16d6-42a8-8e5e-7a1da563f923.png)

Cuando el usuario encienda el registrador, el MCU obtendrá los datos del sensor DHT11 y los presentará en la terminal serie cada 1 segundo hasta que el usuario decida enviar otro comando. El programa realiza una verificacion de los comandos recibidos, en caso de que el usuario ingrese un comando que no corresponda a los comandos especificados, el programa respondera con un mensaje informando que el comando no es valido.
