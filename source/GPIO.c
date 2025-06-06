/*
 * GPIO.c
 * Se definen las funciones con las cuales se configuran y controlan los pines
 * de la tarjeta.
 *
 *  Created on: 26 ene. 2024
 *  Author: Daniel Alfaro y Frida Hernandez.
 */

#include "Bits.h"
#include "GPIO.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_clock.h"
#include "stdbool.h"

static void (*gpio_A_callback)(uint32_t flags) = Zero; //apuntador global a funcion
static void (*gpio_D_callback)(uint32_t flags) = Zero;

static uint8_t gpio_swflag = 0;

//Función que selecciona el callback a usar segun el GPIO que active la ISR
void GPIO_callback_init(gpio_name_t gpio, void (*handler)(uint32_t flags))
{
	if(GPIO_d_f == gpio)
	{
		gpio_D_callback = handler;
	}
	else
	{
		gpio_A_callback = handler;
	}
}

//Funciones Handler de los puertos C y B del GPIO
void PORTA_IRQHandler(void)
{
	uint32_t irq_status = Zero;
	irq_status = GPIO_PortGetInterruptFlags(GPIOA); //Regresa un valor el cual indica que pin fue el que interrumpio
	if(gpio_A_callback)
	{
		gpio_A_callback(irq_status); //Aqui se activa la funcion a la que apunta el callback
	}
	GPIO_PortClearInterruptFlags(GPIOA, clean_all);
}

void PORTD_IRQHandler(void)
{
	uint32_t irq_status = Zero;
	irq_status = GPIO_PortGetInterruptFlags(GPIOD);
	if(gpio_D_callback)
	{
		gpio_D_callback(irq_status);
	}
	GPIO_PortClearInterruptFlags(GPIOD, clean_all);
}

//Funciones de configuracion de puerto y pin
void GPIO_init(void)
{
	gpio_pin_config_t gpio_input_config = {
					kGPIO_DigitalInput,
					0,
				};

	gpio_pin_config_t gpio_output_config = {
					kGPIO_DigitalOutput,
					1,
				};

	const port_pin_config_t button_config = {
			kPORT_PullUp,                     /* Internal pull-up resistor is enabled */
			kPORT_FastSlewRate,               /* Fast slew rate is configured */
			kPORT_PassiveFilterEnable,        /* Passive filter is enabled */
			kPORT_OpenDrainDisable,           /* Open drain is disabled */
			kPORT_HighDriveStrength,          /* High drive strength is configured */
			kPORT_MuxAsGpio,                  /* Pin is configured as PTA4 */
			kPORT_UnlockRegister              /* Pin Control Register fields [15:0] are not locked */
		  };

	//Struct de configuracion de la LCD
	gpio_pin_config_t led_config = {
		        kGPIO_DigitalOutput,
		        1,
		    };

	//Activar clock de cada puerto
	CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_PortB);
	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(kCLOCK_PortD);
	CLOCK_EnableClock(kCLOCK_PortE);

	//Config LED k66 - ya corregido
	PORT_SetPinMux(PORTA, bit_11, kPORT_MuxAsGpio);		//Inicializacion de
	GPIO_PinInit(GPIOB, bit_11, &gpio_output_config);	//INICIALIZA EL GPIO

	PORT_SetPinMux(PORTC, bit_9, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOC, bit_9, &gpio_output_config);

	PORT_SetPinMux(PORTE, bit_6, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOE, bit_6, &gpio_output_config);

	//Config botones
	//Botones K66 - ya corregido
	GPIO_PinInit(GPIOD, bit_11, &gpio_input_config);
	PORT_SetPinConfig(PORTD, bit_11, &button_config);
	PORT_SetPinInterruptConfig(PORTD, bit_11, kPORT_InterruptFallingEdge);

	GPIO_PinInit(GPIOA, bit_10, &gpio_input_config);
	PORT_SetPinConfig(PORTA, bit_10, &button_config);
	PORT_SetPinInterruptConfig(PORTA, bit_10, kPORT_InterruptFallingEdge);

	//Pines UART0
	PORT_SetPinMux(PORTB, 16U, kPORT_MuxAlt3);
	PORT_SetPinMux(PORTB, 17U, kPORT_MuxAlt3);

}

void GPIO_SetFlag()
{
	gpio_swflag = 1;
}

void GPIO_ClearFlag()
{
	gpio_swflag = 0;
}

uint8_t GPIO_GetFlag()
{
	return gpio_swflag;
}
