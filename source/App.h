/*
 * App.h
 *
 *  Created on: 1 jun. 2025
 *      Author: Frida Hernandez
 */
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "aes.h"
#include "Msg.h"
#include "Crypto.h"
#include "Ethernet.h"
#include "GPIO.h"
#include "NVIC.h"
#include "Bits.h"

#ifndef APP_H_
#define APP_H_

void App_Init();
void App_Send();
void App_Receive();

#endif /* APP_H_ */
