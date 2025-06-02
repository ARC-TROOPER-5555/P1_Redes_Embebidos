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

    Ethernet_Init();
    Ethernet_SendFrame();

    while (1)
    {
    	Ethernet_ReceiveFrame();
    }
}
