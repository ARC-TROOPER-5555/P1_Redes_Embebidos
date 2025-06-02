/*
 * Ethernet.h
 *
 *  Created on: 2 jun. 2025
 *      Author: sebal
 */

#ifndef ETHERNET_H_
#define ETHERNET_H_

#include <stdint.h>

void Ethernet_Init(void);
void Ethernet_SendFrame(void);
void Ethernet_ReceiveFrame(void);

#endif /* ETHERNET_H_ */
