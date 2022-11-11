/******************************************************************************
 * Module: ICU
 *
 * File Name: icu.c
 *
 * Description: Source file for ICU driver
 *
 * Author: Naiera Seifeldin
 *******************************************************************************/

/******************************** Includes ************************************/
#include "icu.h"
#include "gpio.h" // To set directions
#include "common_macros.h"
#include <avr/io.h> // To have access on Timer1 registers for ICU needs
#include <avr/interrupt.h> // for ICU ISR

/***************************** Global variables *******************************/
/* Global pointer to hold the address of the call back function ,, call back function
 * take and return void ,, we initialize it by null address ,, volatile for no compiler
 * optimization ,, static for scope limitation and to save its value till end of program */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*************************** Interrupts Functions *****************************/
ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* after the edge is detected ,, we here call for the Call-Back function using
		 * the pointer ,, since we can't call higher layer directly we can only call
		 * from higher to lower layer */

		(*g_callBackPtr)(); // we can call as : g_callBackPtr(); too
	}
}

/*************************** Functions Definitions ****************************/
/* Initialize the ICU */
void Icu_init(const Icu_ConfigType * Config_Ptr)
{
	/* Set ICP1/PD6 as i/p pin */
	GPIO_setupPinDirection(INPUT_CAPTURE_PORT, INPUT_CAPTURE_PIN, PIN_INPUT);

	/* Timer1 always operates in Normal Mode ,, So FOC1A:B are 1 for non PWM
	 * WGM11:10 == 00 for normal mode */
	SET_BIT(TCCR1A,FOC1A);
	SET_BIT(TCCR1A,FOC1B);

	/* insert the required clock value in the first three bits (CS10, CS11 and CS12)
	 * of TCCR1B Register ,, make first three bits = 0 by & ,, | with clock which I
	 * access it from pointer which is zeros */
	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->clock);

	/* insert the required edge type in ICES1 bit in TCCR1B ,, 1011 1111
	 * make bit 6 = 0 | edge I accessed by pointer which = 1 ,, left shifted by 6
	 *  to make bit 6 = 1 */
	TCCR1B = (TCCR1B & 0xBF) | ((Config_Ptr->edge)<<6);

	/* Initial Value for Timer1 */
	TCNT1 = 0;

	/* Initial Value for the input capture register */
	ICR1 = 0;

	/* Enable the Input Capture interrupt to generate an interrupt when
	 * edge is detected on ICP1/PD6 pin */
	SET_BIT(TIMSK,TICIE1);
}

/* Set the Call Back function address ,, this function return nothing but it takes a
 * pointer to function as an argument which points to a function I want to back to it
 * in upper layer ,, so it save the address of it to the global pointer we have created  */
void Icu_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}

/* Function to set required edge detection ,, as in ICU we change edge after each
 * detection from rising to falling and vice versa */
void Icu_setEdgeDetectionType(const Icu_EdgeType a_edgeType)
{
	/* insert the required edge type in ICES1 bit in TCCR1B Register */
	TCCR1B = (TCCR1B & 0xBF) | (a_edgeType<<6);
}

/* Get the Timer1 Value when the input is captured as when edge is detected by default
 * TCNT1 value stored at Input Capture Register ICR1  */
uint16 Icu_getInputCaptureValue(void)
{
	return ICR1; // return means I read it
}

/* Reset Timer1 to start count from zero again */
void Icu_clearTimerValue(void)
{
	TCNT1 = 0;
}

/* Disable Timer1 to stop ICU */
void Icu_DeInit(void)
{
	/* Clear all Timer1 registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* Disable the Input Capture interrupt */
	CLEAR_BIT(TIMSK,TICIE1);
}

