/******************************************************************************
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for LCD driver
 *
 * Author: Naiera Seifeldin
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

/******************************** Includes ************************************/
#include "std_types.h"

/******************************* Definitions **********************************/
/* LCD HW Ports and Pins Ids */
#define LCD_RS_PORT_ID                 PORTB_ID
#define LCD_RS_PIN_ID                  PIN0_ID

#define LCD_RW_PORT_ID                 PORTB_ID
#define LCD_RW_PIN_ID                  PIN1_ID

#define LCD_E_PORT_ID                  PORTB_ID
#define LCD_E_PIN_ID                   PIN2_ID

#define LCD_DATA_PORT_ID               PORTA_ID


/* LCD Commands */
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80

/**************************** Functions Prototypes ****************************/
void LCD_init(void);
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const char *Str);
void LCD_moveCursor(uint8 row,uint8 col);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);
void LCD_intgerToString(int data);
void LCD_clearScreen(void);
void LCD_CustomChar (uint8 location, uint8 *msg);

#endif /* LCD_H_ */
