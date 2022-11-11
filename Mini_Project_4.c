 /******************************************************************************
 * Name       : MiniProject4.c
 *
 * Author     : Naiera Seifeldin
 *
 * Description: System measure the distance using ULTRASONIC Sensor
 *
 * Date       : October 12, 2022
 *******************************************************************************/

#include "ultrasonic.h"
#include "lcd.h"
#include <avr/io.h> // for I-bit access

int main()
{
	uint16 calc_distance = 0; // variable to hold the calculated distance

	/* Initialize LCD */
	LCD_init();

	/* Initialize Ultrasonic  */
	Ultrasonic_init();

	/* Enable I-Bit */
	SREG |= (1<<7);

	/* Display the distance on LCD screen */
	LCD_displayString("Distance=     cm"); // leave space after


	while(1)
	{
		/* Read the distance from Ultrasonic */
		calc_distance = Ultrasonic_readDistance();
		LCD_moveCursor(0,10);
		LCD_intgerToString(calc_distance);
		if(calc_distance<100)
		{
			LCD_displayCharacter(' ');
			//for case of count down to avoid overwrite
		}

	}
}


