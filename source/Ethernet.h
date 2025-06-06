/*
 * Ethernet.h
 *
 *  Created on: 2 jun. 2025
 *      Author: sebal
 */

#ifndef ETHERNET_H_
#define ETHERNET_H_

#include <stdint.h>

#include "Crypto.h"
#include "Msg.h"
#include "Bits.h"
#include "App_cfg.h"

#define ETHERNET_MIN_SIZE 60U
#define HEADER_SIZE 14U

void Ethernet_Init(void);
void Ethernet_SetFrame(uint8_t *adr, uint8_t *data, size_t length_data);
void Ethernet_SendFrame(size_t size_payload);
void Ethernet_ReceiveFrame(void);

#endif /* ETHERNET_H_ */
