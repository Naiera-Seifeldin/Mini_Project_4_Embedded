 /******************************************************************************
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for LCD driver
 *
 * Author: Naiera Seifeldin
 *******************************************************************************/
#include<stdlib.h>
#include <util/delay.h> /* For the delay functions */
#include "common_macros.h" /* For GET_BIT Macro */
#include "lcd.h"
#include "gpio.h"
/* we put it here not in lcd.h ,, since we want to call the functions of write pin
 * write ports and so on and we do this here in our code not in .h ,, if we include
 * it in lcd.h it will build ,, but it is useless as it use all definitions of GPIO in
 * lcd.h too and it doesn't need it */

/*************************** Functions definitions ****************************/


/* This function initialize the LCD by set the LCD pins directions using GPIO driver,
 * and set it at Data Mode 8-bits, we call setup from gpio.h and send to it the number
 * of port, number of pin and direction to be set as (in / out) and for data to be out from
 * port we use Setup port and send to it number of port and direction */

void LCD_init(void)
{
	/* Set RS, RW and E pins as output = 1 ,, as one will out from these pins from
	 * microprocessor and will in to LCD to set E and RS as required */
	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_RW_PORT_ID,LCD_RW_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,PIN_OUTPUT);
	_delay_ms(20);		/* LCD Power ON delay */
	GPIO_setupPortDirection(LCD_DATA_PORT_ID,PORT_OUTPUT);
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
	LCD_sendCommand(LCD_CURSOR_OFF); /* cursor off */
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* clear LCD at the beginning */
}


/* This function send the required command to the screen as we send to it the required
 * command to be written, we first activate command mode by write LOGIC_LOW (0) in RS,
 * Enable LCD, delay periods are important described in data-sheet, then write data
 * on the port, and then never forget to disable E (from data-sheet) */

void LCD_sendCommand(uint8 command)
{
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW); /* Instruction Mode RS=0 */
	GPIO_writePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LOGIC_LOW); /* write data to LCD so RW=0 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
	GPIO_writePort(LCD_DATA_PORT_ID,command); /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
}


/* This function display required character on screen, we send it data wanted to be
 * written, first set RS to 1 to choose data mode not command, Second set E to 1 to
 * have the data, third write data on port, then disable enable again */

void LCD_displayCharacter(uint8 data)
{
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_HIGH); /* Data Mode RS=1 */
	GPIO_writePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LOGIC_LOW); /* write data to LCD so RW=0 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
	GPIO_writePort(LCD_DATA_PORT_ID,data); /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */


}


/* This function to display a whole sentence or word by looping on the whole string
 * till reach null, we send the string which is the name of array which is address of first
 * place which is constant pointer to char */

void LCD_displayString(const char *Str)
{
	uint8 i = 0;
	for(i=0;Str[i]!='\0';i++)
	{
		LCD_displayCharacter(Str[i]);
	}
}


/* This function used when we need to move cursor to next row to continue displaying
 * the message we want (mapped on screen), function take number of row and column
 * example if we give row=0, then address is the sent column, if row =1 and column = 3
 * then means we enter to case 2 (add 0x40 to column number) as in this case address=0x43 */

void LCD_moveCursor(uint8 row,uint8 col)
{
	uint8 lcd_memory_address;
	// we store here the calculated address that we want to move to it,
	// then send command by it

	/* Calculate the required address in the LCD DDRAM */
	switch(row)
	{
		case 0:
			lcd_memory_address=col;
				break;
		case 1:
			lcd_memory_address=col+0x40;
				break;
		case 2:
			lcd_memory_address=col+0x10;
				break;
		case 3:
			lcd_memory_address=col+0x50;
				break;
	}
	/* Move the LCD cursor to this specific address by Oring address with 10000000 */
	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}


/* This function used to display the required string in a specified row and column
 *  index on the screen, it takes the required row and column with the pointer to char
 *  which is pointer to the string */

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_moveCursor(row,col); /* call to go to to the required LCD position */
	LCD_displayString(Str); /* call to display the string */
}


/* This function used to display the required number  */

void LCD_intgerToString(int data)
{
   char buff[16]; /* String to hold the ascii result */

   itoa(data,buff,10);
   // integer to ascii ,, takes data, base, and array to store ascii in, must include stdlib.h

   LCD_displayString(buff); /* Display the string, example: if we sent 124 it will save in buff
   the ascii of each number, ascii of 1 and of 2 and of 4 and then will send buff to
   displayString ,, we put base as if we put base 16 ass example for data = 255
   it will put ascii of FF if base 2 ,, ascii will be for 11111111 and so on */
}


/* This function is the most common used in LCD as when we want to display a new string we
 * first clear the screen thats why we do it an independent function */

void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* Send clear display command */
}


/* This function is used to display custom character in LCD */
void LCD_CustomChar (unsigned char location, unsigned char *msg)
{
	unsigned char i; // bitmap index which is 5x8 for one char to be written
	if(location<8)
	{
		LCD_sendCommand(0x40 + (location*8));/* send CGRAM address ,, 8 for 8 rows of bitmap */

		for(i=0;i<8;i++)
		{
			LCD_displayCharacter(msg[i]);
			// its not a display on screen ,, its a display on CGRAM
			// as if I say to him write it in memory
		}
	}
}
