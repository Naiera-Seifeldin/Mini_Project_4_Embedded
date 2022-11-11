/******************************************************************************
 * Module: ICU
 *
 * File Name: icu.h
 *
 * Description: Header file for ICU driver
 *
 * Author: Naiera Seifeldin
 *******************************************************************************/

#ifndef ICU_H_
#define ICU_H_

/******************************** Includes ************************************/
#include "std_types.h"

/******************************* Definitions **********************************/
#define INPUT_CAPTURE_PORT PORTD_ID
#define INPUT_CAPTURE_PIN  PIN6_ID

/***************************** Types Declaration ******************************/
typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Icu_Clock; // 0,1,2,3,4,5 >> for CS12 : CS11 : CS00

typedef enum
{
	FALLING,RISING
}Icu_EdgeType; //0,1 >>ICES1

typedef struct
{
	Icu_Clock clock;
	/* when in main say it wants F_CPU_CLOCK, we access structure clock and store it in it
	 * so text replace occur by its value which is = 0 */
	Icu_EdgeType edge;
}Icu_ConfigType;

/* Very IMP: any module now take pointer to configuration structure, pass structure by address
 * to don't duplicate memory, constant structure to don't edit on it */

/**************************** Functions Prototypes ****************************/

void Icu_init(const Icu_ConfigType * Config_Ptr);
void Icu_setCallBack(void(*a_ptr)(void));
void Icu_setEdgeDetectionType(const Icu_EdgeType edgeType);
uint16 Icu_getInputCaptureValue(void);
void Icu_clearTimerValue(void);
void Icu_DeInit(void);

#endif /* ICU_H_ */
