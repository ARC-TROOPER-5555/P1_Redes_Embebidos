/*
 * Crypto.c
 *
 *  Created on: 1 jun. 2025
 *      Author: Frida Hernandez
 */

#include "Crypto.h"

static const uint8_t key[16] = AES_KEY_STR;
static const uint8_t iv[16]  = AES_IV_STR;

// Prints string as hex
void phex(uint8_t* str, size_t lenght)
{
    unsigned char i;
    for (i = 0; i < lenght; ++i)
        printf("%.2x ", str[i]);
    printf("\n");
}

// Functions for decrypt and encrypt
size_t Crypto_AddPadding(uint8_t *msg_input, size_t input_size)
{
	//Calcula relleno que se necesita para multiplo de 16 bytes
	size_t padding_size = 16 - (input_size % 16);

	//Calcula el tamaño total del arreglo final
	size_t aes_padded_size = input_size + padding_size;

	//Agrega padding total al mensaje
	for(size_t i = 0; i < padding_size; i++)
	{
		msg_input[input_size + i] = (uint8_t) padding_size;
	}

	return aes_padded_size;
}

size_t Crypto_RemovePadding(uint8_t *msg_buffer, size_t buffer_size)
{
	//Si el mensaje esta vacio sale de la funcion
	if(buffer_size == 0)
		return 0;

	//Verifica el ultimo byte para saber cuantos bits de padding hay
	uint8_t padding_size = msg_buffer[buffer_size - 1];

	//Verifica que el tamaño del padding no sea mayor al tamaño total
	if(padding_size == 0 || padding_size > buffer_size)
		return 0;

	// Verifica que todos los bytes de padding tengan el mismo valor
	for (size_t i = 0; i < padding_size; i++)
	{
		if (msg_buffer[buffer_size - 1 - i] != padding_size)
			return 0; // padding incorrecto
	}

	return (buffer_size - padding_size);
}

size_t Crypto_DecryptCbc(uint8_t *enmsg_input, size_t enmsg_size)
{
    struct AES_ctx ctx;

    printf("\n\nEncrypted phrase received (hex format): ");
    //Ver mensaje encriptado recibido
    phex(enmsg_input, enmsg_size);

    //Decripta el mensaje recibido
    AES_init_ctx_iv(&ctx, key, iv);
	AES_CBC_decrypt_buffer(&ctx, enmsg_input, enmsg_size);

	//Obtiene el tamaño del mensaje original
	size_t demsg_size = Crypto_RemovePadding(enmsg_input, enmsg_size);

	printf("Decrypted phrase received(hex format): ");
	//Ver mensaje decriptado
	phex(enmsg_input, demsg_size);

	return demsg_size;
}

size_t Crypto_EncryptCbc(uint8_t *dcmsg_input, size_t dcmsg_size)
{
	//Obtiene tamaño total del mensaje a encriptar
	size_t encmsg_size = Crypto_AddPadding(dcmsg_input, dcmsg_size);

	printf("\n");
	printf("Original phrase: %s\n", dcmsg_input);
	printf("Decrypted phrase to send (hex format): ");
	//Ver mensaje original + padding
	phex(dcmsg_input, encmsg_size);

	struct AES_ctx ctx;

	//Encripta el mensaje por enviar
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_encrypt_buffer(&ctx, dcmsg_input, encmsg_size);

    printf("Encrypted phrase to send: ");
    //Ver mensaje encriptado
    phex(dcmsg_input, encmsg_size);

    return encmsg_size;
}


