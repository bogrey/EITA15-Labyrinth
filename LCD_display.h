/*
 * IncFile1.h
 *
 * Created: 2022-05-05 10:50:18
 *  Author: cid12bel
 */ 
#include <avr/io.h>


#ifndef LCD_display_H_
#define LCD_display_H_

/***************************************
* According to our blueprint IO-ports PB
* handles the data communication and PD
* handles the commands to the display.
****************************************/
#define COMMAND_PORT PORTD
#define COMMAND_DIRECTION DDRD
#define DATA_PORT PORTB
#define DATA_DIRECTION DDRB

/* Some control commands */

/* Reset is on pin 16 -> PORTD2*/
#define LCD_RST PORTD2

/* Read/Write is on pin 17 -> PORTD3 */
#define LCD_RW PORTD3

/* Shift register for internal data i/o is on port 18.
*  maybe rename to DI instead, since that's what's it's
*  called in the data sheet..
*  Set LCD_RS to high when you want to send commands
*  to the display. Set to low when you want to send
*  data (y'know to, like, draw stuff on the screen)..
*/
#define LCD_RS PORTD4

/* LCD enable is on pin 19 -> PORTD5 */
#define LCD_EN PORTD5

/* CS1 part of the screen is pin 15 -> PORTD1
*  and CS2 part is pin 14 -> PORTD0 */
#define CS1 PORTD1
#define CS2 PORTD0

/* The display has 8 different pages that can be displayed.
*  Usually you need to know which one you want to display. */
#define NBR_PAGES 8u


#define DISPLAY_OFF 0b00111110
#define DISPLAY_ON 0b00111111 

/* Initializes the display */
void init_display();

/* Makes sure the screen is blank before we do anything and that
 * there is no garbage left in any of the 8 pages. */
void clear_display();

/* Use this function to send commands to the LCD-display. Shamelessly 
   "inspired" by a code example @ https://www.electronicwings.com/avr-atmega/graphical-lcd-128x64-interfacing-with-atmega1632 */
void LCD_command(uint8_t command);

/* Use this function to send data to be drawn to the LCD. "Inspiration" as above..
 * AFAIK the data represents an entire display column. Keep values between
 * 0 and 63 (max 0b0011111), since we only have 64 rows. */
void LCD_data(uint8_t data);

/* Use this function to get a the value that the display needs to
 * be able to set a new y-position 
 *
 * @return LCD command value to be sent over the data pins. */
uint8_t disp_ypos(uint8_t new_pos);

/* Use this function to get a the value that the display needs to
 * be able to set a new render page (called "x") 
 *
 * @return LCD command value to be sent over the data pins.*/
uint8_t disp_page(uint8_t new_line);

/* Use this function to get a the value that the display needs to
 * be able to set a new start line (called "z") 
 *
 * @return LCD command value to be sent over the data pins. */
uint8_t disp_start_line(uint8_t new_pos);

/* Use this function to enable drawing on CS1 half of the LCD */
void set_CS1();

/* Use this function to enable drawing on CS2 half of the LCD */
void set_CS2();

/* REMOVE */
void drawblack();

#endif /* INCFILE1_H_ */