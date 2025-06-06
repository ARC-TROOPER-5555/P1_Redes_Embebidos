/*
 * App.c
 *
 *  Created on: 1 jun. 2025
 *      Author: Frida Hernandez
 */

#include "App.h"

uint8_t pc_macAddr[6] = PC_MAC_ADDRESS;

void App_Init()
{
	GPIO_init();
	Ethernet_Init();

	//Activacion y clasificacion de interrupciones del puerto A,B y C
	NVIC_set_basepri_threshold(PRIORITY_10); 					//Establece un rango de prioridad de 0 a 9
	NVIC_enable_interrupt_and_priotity(PORTA_IRQ,PRIORITY_1);
	NVIC_enable_interrupt_and_priotity(PORTD_IRQ,PRIORITY_1);
	NVIC_global_enable_interrupts;

	GPIO_callback_init(GPIO_a_f, Msg_ButtonCounter);
}

void App_Send()
{
	const uint8_t* message = Msg_SendMessage(Msg_GetCounter());

	uint8_t message_temp[300]; //Arreglo con espacio suficiente para poder guardar la frase con padding
	strcpy((char*)message_temp, (const char*)message);

	size_t msg_lenght = strlen((char*)message_temp); //Obtiene solo el tamaño de la cadena
	size_t encrypted_size;

	encrypted_size = Crypto_EncryptCbc(message_temp, msg_lenght);

	Ethernet_SetFrame(pc_macAddr,message_temp,encrypted_size);

	Ethernet_SendFrame(encrypted_size);
}

void App_Receive()
{
	Ethernet_ReceiveFrame();
}
