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
	uint8_t message[] = "Hola Frida :)";
	size_t msg_lenght = strlen((char*)message);

	size_t encrypted_size;
	size_t decrypted_size;

	encrypted_size = Crypto_EncryptCbc(message, msg_lenght);
	decrypted_size = Crypto_DecryptCbc(message, encrypted_size);
}

void App_receive()
{

}
