/*
 * App.c
 *
 *  Created on: 1 jun. 2025
 *      Author: Frida Hernandez
 */

#include "App.h"
#include "Crypto.h"
#include "Msg.h"

void App_init()
{

}

void App_send()
{
	const uint8_t* message = Msg_SendMessage(1);

	uint8_t message_temp[64];
	strcpy((char*)message_temp, (const char*)message);

	size_t msg_lenght = strlen((char*)message_temp); //Obtiene solo el tamaño de la cadena
	size_t encrypted_size;
	size_t decrypted_size;

	encrypted_size = Crypto_EncryptCbc(message_temp, msg_lenght);

	decrypted_size = Crypto_DecryptCbc(message_temp, encrypted_size);
}

void App_receive()
{

}
