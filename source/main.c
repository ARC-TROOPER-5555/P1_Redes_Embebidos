/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdint.h>
#include "pin_mux.h"
#include "board.h"
#include "clock_config.h"
#include "ethernet.h"

int main(void)
{

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();
    uint8_t MAC_PC[] = {0xf8, 0x75, 0xa4, 0xea, 0xb8, 0x42};
    uint8_t DATOS[] = {"Practica-1 de 6 hola como estas el dia de hoy"};


    Ethernet_Init();
    Ethernet_SendFrame(MAC_PC,DATOS,sizeof(DATOS));

    while (1)
    {
    	Ethernet_ReceiveFrame();
    }
}
