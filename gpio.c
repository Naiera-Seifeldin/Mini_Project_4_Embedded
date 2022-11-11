/******************************************************************************
 * Module: GPIO
 *
 * File Name: gpio.c
 *
 * Description: Source file for the AVR GPIO driver
 *
 * Author: Naiera Seifeldin
 *******************************************************************************/

#include "gpio.h" /* To have access to all functions and defines and enums */
#include "common_macros.h" /* To have access on the macros */
#include "avr/io.h"
/* To have access on the Registers or we can use our registers by include its file */

/*************************** Functions definitions ****************************/

/* This function to set the direction of pin in or out we send to it the port that
 * has the pin, the pin number, and what direction we want, when it by switch get
 * required port, it set the bit by sending the direction register of this port
 * and number of required pin */

void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction)
{
	if((pin_num >= NUM_OF_PINS) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRA,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRA,pin_num);
			}
			break;
		case PORTB_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRB,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRB,pin_num);
			}
			break;
		case PORTC_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRC,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRC,pin_num);
			}
			break;
		case PORTD_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRD,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRD,pin_num);
			}
			break;
		}
	}
}


/* This function write what we want on pin, so it takes port, pin num and value
 * wanted to be written which is either logic low=0 or high=1, so we use switch
 * and when we find the matched case of port, we check the value and either set
 * bit or clear it depend on this value, when we call clear or set we send to it
 * the port register not the macro (port number) to access the pin in it */

void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
	if((pin_num >= NUM_OF_PINS) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTA,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTA,pin_num);
			}
			break;
		case PORTB_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTB,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTB,pin_num);
			}
			break;
		case PORTC_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTC,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTC,pin_num);
			}
			break;
		case PORTD_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTD,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTD,pin_num);
			}
			break;
		}
	}
}


/* This function read pin and store its value in a local variable that we create,
 * we send to it the port and pin number which we want to read, then we check if
 * pin was set = 1, so we store this 1 (Logic high) at our local variable  */

uint8 GPIO_readPin(uint8 port_num, uint8 pin_num)
{
	uint8 pin_value = LOGIC_LOW;

	if((pin_num >= NUM_OF_PINS) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			if(BIT_IS_SET(PINA,pin_num))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		case PORTB_ID:
			if(BIT_IS_SET(PINB,pin_num))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		case PORTC_ID:
			if(BIT_IS_SET(PINC,pin_num))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		case PORTD_ID:
			if(BIT_IS_SET(PIND,pin_num))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		}
	}

	return pin_value;
}


/* This function setup port direction by sending to it the port number, and the
 * direction we want(in / out), so it switch for which port then put its direction
 * value (direction) at its register DDR to set the whole port with this direction  */

void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction)
{
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			DDRA = direction;
			break;
		case PORTB_ID:
			DDRB = direction;
			break;
		case PORTC_ID:
			DDRC = direction;
			break;
		case PORTD_ID:
			DDRD = direction;
			break;
		}
	}
}


/* This function write whatever value we want on the whole port as 0x55=0b01010101
 * to flash even LEDs as example, so we send to it the port number and value to be
 * written, we use switch to find needed port, then access the port register and
 * write the value in it */

void GPIO_writePort(uint8 port_num, uint8 value)
{
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Write the port value as required */
		switch(port_num)
		{
		case PORTA_ID:
			PORTA = value;
			break;
		case PORTB_ID:
			PORTB = value;
			break;
		case PORTC_ID:
			PORTC = value;
			break;
		case PORTD_ID:
			PORTD = value;
			break;
		}
	}
}


/* This function read port by sending to it the port number to store it in its
 * created local variable, using switch to find required port, then access the port
 * register and read it by using PIN and store it in value */

uint8 GPIO_readPort(uint8 port_num)
{
	uint8 value = LOGIC_LOW;

	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			value = PINA;
			break;
		case PORTB_ID:
			value = PINB;
			break;
		case PORTC_ID:
			value = PINC;
			break;
		case PORTD_ID:
			value = PIND;
			break;
		}
	}

	return value;
}
