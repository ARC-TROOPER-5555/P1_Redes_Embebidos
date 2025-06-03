/*
 * Msg.h
 *
 *  Created on: 1 jun. 2025
 *      Author: Frida Hernandez
 */

#ifndef MSG_H_
#define MSG_H_

#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

const uint8_t* Msg_SendMessage(uint8_t id);
int Msg_ProcessMessage(const uint8_t* recibida);
void Msg_ButtonCounter();
uint8_t Msg_GetCounter();

#endif /* MSG_H_ */
