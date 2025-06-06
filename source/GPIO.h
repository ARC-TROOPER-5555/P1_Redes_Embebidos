/*
 * GPIO.h
 * Declaración de funciones, estructuras y direcciones para manipular y confugurar
 * los puertos de la k64.
 *
 *  Created on: 26 ene. 2024
 *   Author: Daniel Alfaro y Frida Hernandez.
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "fsl_gpio.h"
#include "stdint.h"
#include "bits.h"

#define PIN0_IDX        0u   /*!< Pin number for pin 0 in a port */
#define PIN1_IDX        1u   /*!< Pin number for pin 1 in a port */
#define PIN2_IDX        2u   /*!< Pin number for pin 2 in a port */
#define PIN3_IDX        3u   /*!< Pin number for pin 3 in a port */
#define PIN16_IDX       16u   /*!< Pin number for pin 16 in a port */
#define PIN17_IDX       17u   /*!< Pin number for pin 17 in a port */

#define PORT_DATA_OR_CMD_PIN PORTC
#define GPIO_DATA_OR_CMD_PIN GPIOC
#define DATA_OR_CMD_PIN 	5U
#define RESET_PIN 			7U
#define PORT_RESET_PIN 		PORTC
#define GPIO_RESET_PIN 		GPIOC

typedef enum
{
	GPIO_a_f, /*!< Definition to select GPIO A */
	GPIO_b_f, /*!< Definition to select GPIO B */
	GPIO_c_f, /*!< Definition to select GPIO C */
	GPIO_d_f, /*!< Definition to select GPIO D */
	GPIO_e_f, /*!< Definition to select GPIO E */
	GPIO_f_f  /*!< Definition to select GPIO F */
} gpio_name_t;

//Tipo enumerado con valores del 0 al 9
typedef enum
{
	Zero,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine
}number_name_t;

#define value_zero 	0U
#define turn_on		1U
#define clean_all 	0xFFFFFFFF

void GPIO_init(void);
void GPIO_callback_init(gpio_name_t gpio, void (*handler)(uint32_t flags));

void GPIO_SetFlag();
void GPIO_ClearFlag();
uint8_t GPIO_GetFlag();


#endif /* GPIO_H_ */
