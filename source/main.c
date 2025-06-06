/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "pin_mux.h"
#include "board.h"
#include "clock_config.h"

#include "App.h"
#include "App_cfg.h"

int main(void)
{
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	App_Init();

	while(1)
	{
		if(Msg_GetFlag())
		{
			App_Send();
			Msg_CleanFlag();
		}

		App_Receive();
	}
	return 0;
}
