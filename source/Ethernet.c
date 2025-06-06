/*
 * Ethernet.c
 *
 *  Created on: 2 jun. 2025
 *      Author: sebal
 */
#include <stdlib.h>
#include "pin_mux.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_enet.h"
#include "fsl_phy.h"
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
#include "fsl_memory.h"
#endif
#include "fsl_enet_mdio.h"
#include "fsl_phyksz8081.h"
#include "fsl_sysmpu.h"

#include "Ethernet.h"

#define EXAMPLE_ENET        ENET
#define EXAMPLE_PHY_ADDRESS 0x00U
/* MDIO operations. */
#define EXAMPLE_MDIO_OPS enet_ops
/* PHY operations. */
#define EXAMPLE_PHY_OPS phyksz8081_ops
/* ENET clock frequency. */
#define EXAMPLE_CLOCK_FREQ CLOCK_GetFreq(kCLOCK_CoreSysClk)
#define ENET_RXBD_NUM          (4)
#define ENET_TXBD_NUM          (4)
#define ENET_RXBUFF_SIZE       (ENET_FRAME_MAX_FRAMELEN)
#define ENET_TXBUFF_SIZE       (ENET_FRAME_MAX_FRAMELEN)
#define ENET_DATA_LENGTH       (1000)
#define ENET_TRANSMIT_DATA_NUM (20)
#ifndef APP_ENET_BUFF_ALIGNMENT
#define APP_ENET_BUFF_ALIGNMENT ENET_BUFF_ALIGNMENT
#endif
#ifndef PHY_AUTONEGO_TIMEOUT_COUNT
#define PHY_AUTONEGO_TIMEOUT_COUNT (100000)
#endif
#ifndef PHY_STABILITY_DELAY_US
#define PHY_STABILITY_DELAY_US (0U)
#endif

AT_NONCACHEABLE_SECTION_ALIGN(enet_rx_bd_struct_t g_rxBuffDescrip[ENET_RXBD_NUM], ENET_BUFF_ALIGNMENT);
AT_NONCACHEABLE_SECTION_ALIGN(enet_tx_bd_struct_t g_txBuffDescrip[ENET_TXBD_NUM], ENET_BUFF_ALIGNMENT);
/*! @brief The data buffers can be in cacheable region or in non-cacheable region.
 * If use cacheable region, the alignment size should be the maximum size of "CACHE LINE SIZE" and "ENET_BUFF_ALIGNMENT"
 * If use non-cache region, the alignment size is the "ENET_BUFF_ALIGNMENT".
 */
SDK_ALIGN(uint8_t g_rxDataBuff[ENET_RXBD_NUM][SDK_SIZEALIGN(ENET_RXBUFF_SIZE, APP_ENET_BUFF_ALIGNMENT)],
          APP_ENET_BUFF_ALIGNMENT);
SDK_ALIGN(uint8_t g_txDataBuff[ENET_TXBD_NUM][SDK_SIZEALIGN(ENET_TXBUFF_SIZE, APP_ENET_BUFF_ALIGNMENT)],
          APP_ENET_BUFF_ALIGNMENT);

enet_handle_t g_handle;
uint8_t g_frame[ENET_DATA_LENGTH + HEADER_SIZE];

/*! @brief The MAC address for ENET device. */
uint8_t g_macAddr[6] = MAC_ADDRESS;
uint8_t pc_macAddress[6] = PC_MAC_ADDRESS;

/*! @brief Enet PHY and MDIO interface handler. */
static mdio_handle_t mdioHandle = {.ops = &EXAMPLE_MDIO_OPS};
static phy_handle_t phyHandle   = {.phyAddr = EXAMPLE_PHY_ADDRESS, .mdioHandle = &mdioHandle, .ops = &EXAMPLE_PHY_OPS};

void Ethernet_Init(void)
{
	enet_config_t config;
	phy_config_t phyConfig = {0};
	//uint32_t length        = 0;
	bool link              = false;
	bool autonego          = false;
	phy_speed_t speed;
	phy_duplex_t duplex;
	//uint32_t testTxNum = 0;
	status_t status;
	//enet_data_error_stats_t eErrStatic;
	volatile uint32_t count = 0;

    enet_buffer_config_t buffConfig[] = {{
        ENET_RXBD_NUM,
        ENET_TXBD_NUM,
        SDK_SIZEALIGN(ENET_RXBUFF_SIZE, APP_ENET_BUFF_ALIGNMENT),
        SDK_SIZEALIGN(ENET_TXBUFF_SIZE, APP_ENET_BUFF_ALIGNMENT),
        &g_rxBuffDescrip[0],
        &g_txBuffDescrip[0],
        &g_rxDataBuff[0][0],
        &g_txDataBuff[0][0],
        true,
        true,
        NULL,
    }};

    PRINTF("Initializing Ethernet...\r\n");

    SYSMPU_Enable(SYSMPU, false);
    CLOCK_SetRmii0Clock(1U);

    ENET_GetDefaultConfig(&config);
    config.miiMode = kENET_RmiiMode;

    /* Inicializar PHY */
    phyConfig.phyAddr = EXAMPLE_PHY_ADDRESS;
    phyConfig.autoNeg = true;
    mdioHandle.resource.base        = EXAMPLE_ENET;
    mdioHandle.resource.csrClock_Hz = EXAMPLE_CLOCK_FREQ;

    /* Initialize PHY and wait auto-negotiation over. */
   PRINTF("Wait for PHY init...\r\n");
   do
   {
	   status = PHY_Init(&phyHandle, &phyConfig);
	   if (status == kStatus_Success)
	   {
		   PRINTF("Wait for PHY link up...\r\n");
		   /* Wait for auto-negotiation success and link up */
		   count = PHY_AUTONEGO_TIMEOUT_COUNT;
		   do
		   {
			   PHY_GetAutoNegotiationStatus(&phyHandle, &autonego);
			   PHY_GetLinkStatus(&phyHandle, &link);
			   if (autonego && link)
			   {
				   break;
			   }
		   } while (--count);
		   if (!autonego)
		   {
			   PRINTF("PHY Auto-negotiation failed. Please check the cable connection and link partner setting.\r\n");
		   }
	   }
   } while (!(link && autonego));

#if PHY_STABILITY_DELAY_US
   /* Wait a moment for PHY status to be stable. */
   SDK_DelayAtLeastUs(PHY_STABILITY_DELAY_US, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
#endif

   /* Get the actual PHY link speed. */
   PHY_GetLinkSpeedDuplex(&phyHandle, &speed, &duplex);
   /* Change the MII speed and duplex for actual link status. */
   config.miiSpeed  = (enet_mii_speed_t)speed;
   config.miiDuplex = (enet_mii_duplex_t)duplex;

   ENET_Init(EXAMPLE_ENET, &g_handle, &config, &buffConfig[0], &g_macAddr[0], EXAMPLE_CLOCK_FREQ);
   ENET_ActiveRead(EXAMPLE_ENET);//Empeiza a leer paquetes
}

void Ethernet_SetFrame(uint8_t *adr, uint8_t *data, size_t length_data)
{
	uint32_t count;
    uint32_t length = length_data;

    // Dirección MAC destino (broadcast o destino específico)
    for (count = 0; count < 6U; count++)
    {
        g_frame[count] = adr[count]; // Dirección MAC destino
    }

    // Dirección MAC origen
    memcpy(&g_frame[6], &g_macAddr[0], 6U);

    // Campo de longitud o tipo (IEEE 802.3 usa longitud)
    g_frame[12] = (length >> 8) & 0xFFU;
    g_frame[13] = length & 0xFFU;

    // Copiar los datos al frame
    for (count = 0; count < length; count++)
    {
        g_frame[count + HEADER_SIZE] = data[count];
    }
}

void Ethernet_SendFrame(size_t size_payload)
{
	bool link = false;
	uint32_t testTxNum = FALSE;
	uint8_t size_header = HEADER_SIZE;

	if(size_payload < ETHERNET_MIN_SIZE)
	{
		size_payload = ETHERNET_MIN_SIZE;
	}

	if (testTxNum < ENET_TRANSMIT_DATA_NUM)
	{
		/* Send a multicast frame when the PHY is link up. */
		if (kStatus_Success == PHY_GetLinkStatus(&phyHandle, &link))
		{
			if (link)
			{
				//SDK_DelayAtLeastUs(1000,EXAMPLE_CLOCK_FREQ);
				testTxNum++;
				if (kStatus_Success ==
					ENET_SendFrame(EXAMPLE_ENET, &g_handle, &g_frame[0], size_header + size_payload, 0, false, NULL))
				{
					PRINTF("The %d frame transmitted success!\r\n", testTxNum);
				}
				else
				{
					PRINTF(" \r\nTransmit frame failed!\r\n");
				}
			}
		}
	}
}

void Ethernet_ReceiveFrame(void)
{
	uint32_t length = FALSE;
	status_t status;
	enet_data_error_stats_t eErrStatic;
	/* Get the Frame size */
	status = ENET_GetRxFrameSize(&g_handle, &length, FALSE);

	/* Call ENET_ReadFrame when there is a received frame. */
	if (length != FALSE)
	{
		/* Received valid frame. Deliver the rx buffer with the size equal to length. */
		uint8_t *data = (uint8_t *)malloc(length);
		if (data == NULL)
		{
			PRINTF("Error: Could not allocate memory for the frame.\r\n");
			return;
		}

		status = ENET_ReadFrame(EXAMPLE_ENET, &g_handle, data, length, FALSE, NULL);
		if (status == kStatus_Success)
		{
			// Filtrar mensaje por MAC k66
			bool dirigido_a_mi = true;
			for (int i = 0; i < 6; i++) {
			    if (data[i] != g_macAddr[i]) {
			        dirigido_a_mi = false;
			        break;
			    }
			}
			if (!dirigido_a_mi) {
				//PRINTF("⚠️ Package not relevant. Ignored.\n");
				free(data);
				return;
			}

			//Imprime direccion fuente y destino
			PRINTF("\nA frame received. The length %d ", length);
			PRINTF(" Dest Address %02x:%02x:%02x:%02x:%02x:%02x Src Address %02x:%02x:%02x:%02x:%02x:%02x \r\n",
				   data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9],
				   data[10], data[11]);


			// Contenido paquete recibido
			/*PRINTF("Received Data:\n");
			for (size_t i = 0; i < length; i++)
			{
				PRINTF("%02X ", data[i]);
				if ((i + 1) % 16 == 0) PRINTF("\n");
			}*/

			// Saltarse encabezado Ethernet (14 bytes) y obtener tamaño de frase
			uint8_t* mensaje = data + HEADER_SIZE;
			size_t mensaje_len = ((uint16_t)data[12] << 8) | data[13];

			// Decriptar mensaje y quitar padding
			size_t length_org_msg = Crypto_DecryptCbc(mensaje, mensaje_len);

			// Copiar mensaje decriptado para procesarlo
			char mensaje_str[300];
			memcpy(mensaje_str, mensaje, length_org_msg);
			mensaje_str[length_org_msg] = '\0';
			int num_msg = Msg_ProcessMessage(mensaje_str);
			PRINTF("The response phrase received was number: %d -> %s\n\n", num_msg, mensaje_str);
		}
		free(data);
	}
	else if (status == kStatus_ENET_RxFrameError)
	{
		/* Update the received buffer when error happened. */
		/* Get the error information of the received g_frame. */
		ENET_GetRxErrBeforeReadFrame(&g_handle, &eErrStatic, FALSE);
		/* update the receive buffer. */
		ENET_ReadFrame(EXAMPLE_ENET, &g_handle, NULL, FALSE, FALSE, NULL);
	}
}
