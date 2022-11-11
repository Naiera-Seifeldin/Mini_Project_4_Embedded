/******************************************************************************
 * Module: ULTRASONIC SENSOR
 *
 * File Name: ultrasonic.h
 *
 * Description: Header file for ULTRASONIC SENSOR driver
 *
 * Author: Naiera Seifeldin
 *******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

/******************************** Includes ************************************/
#include "std_types.h"

/******************************* Definitions **********************************/
#define ULTRASONIC_TRIGGER_PORT         PORTB_ID
#define ULTRASONIC_TRIGGER_PIN          PIN5_ID

#define ULTRASONIC_ECHO_PORT            PORTD_ID
#define ULTRASONIC_ECHO_PIN             PIN6_ID

#define NUM_OF_EDGES                    2

/**************************** Functions Prototypes ****************************/
void Ultrasonic_init(void);
void Ultrasonic_Trigger(void);
uint16 Ultrasonic_readDistance(void);
void Ultrasonic_edgeProcessing(void);


#endif /* ULTRASONIC_H_ */
