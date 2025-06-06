/*
 * Crypto.h
 *
 *  Created on: 1 jun. 2025
 *      Author: Frida Hernandez
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "aes.h"
#include "App_cfg.h"

#ifndef CRYPTO_H_
#define CRYPTO_H_

void phex(uint8_t* str, size_t lenght);
size_t Crypto_AddPadding(uint8_t *msg_input, size_t input_size);
size_t Crypto_RemovePadding(uint8_t *msg_buffer, size_t buffer_size);
size_t Crypto_DecryptCbc(uint8_t *enmsg_input, size_t enmsg_size);
size_t Crypto_EncryptCbc(uint8_t *dcmsg_input, size_t dcmsg_size);

#endif /* CRYPTO_H_ */
