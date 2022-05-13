/*
 * LCD_Test.c
 *
 * Created: 2022-05-05 10:43:03
 * Author : cid12bel
 */ 

#define F_CPU 16000000u

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "LCD_display.h"

void init_display()
{
	DATA_DIRECTION = 0xFF;
	COMMAND_DIRECTION = 0xFF; /*set all to high*/
	
	/* Select both halves of the screen and set reset flag to high. 
	 * Note that all this happens simultaneously on both cs1 and cs2. */
	COMMAND_PORT |= (1 << CS1) | (1 << CS2) | (1 << LCD_RST);
	
	_delay_us(20); /* from code example. 20 ms should be safe */
	
	LCD_command(DISPLAY_OFF);
	LCD_command(disp_ypos(0));
	LCD_command(disp_page(0));
	LCD_command(disp_start_line(0));
	LCD_command(DISPLAY_ON);
	
}

void clear_display()
{
	int i, j; 
	
	/* Write to both halves of the screen at the same time */
	COMMAND_PORT |= (1 << CS1) | (1 << CS2);
	
	for (i = 0; i < NBR_PAGES; ++i)
	{
		LCD_command(disp_page(i)); /* each page needs to be cleared */
		
		for (j = 0; j < 64; ++j)
		{
			/* Write zeros to each column. Note that the column
			value increments automatically each time data is 
			written to the LCD display. That's why we don't have
			to set a new start line for each iteration of the loop.*/
			LCD_data(0);
		}
	}
	LCD_command(disp_ypos(0)); /* Make sure the display will start drawing at pos 0 again */
	LCD_command(disp_page(0)); /* Start drawing at page 0 again */
	
}

void LCD_command(uint8_t command)
{
	DATA_PORT = command; /* Send the command you want to execute to the data pins */
	COMMAND_PORT &= ~(1 << LCD_RS);  /* set shift register to low to send commands*/
	COMMAND_PORT &= ~(1 << LCD_RW); /* set RW low to enable write */
	COMMAND_PORT |= (1 << LCD_EN); /* set enable to high */
	_delay_us(5); /* allow some time to pass. 5us in code example. Hopefully enough..*/
	COMMAND_PORT &= ~(1 << LCD_EN); /* set enable to low, to stop sending commands */
	_delay_us(5); /* wait, see above */
}

void LCD_data(uint8_t data)
{
	DATA_PORT = data;
	COMMAND_PORT |= (1 << LCD_RS); /* set shift register high to send data */
	COMMAND_PORT &= ~(1 << LCD_RW); /* set RW low to enable write */
	COMMAND_PORT |= (1 << LCD_EN); /* set enable to high */
	_delay_us(5); /* allow some time to pass. 5us in code example. Hopefully enough..*/
	COMMAND_PORT &= ~(1 << LCD_EN); /* set enable to low, to stop sending commands */
	_delay_us(5); /* wait, see above */
}

uint8_t disp_ypos(uint8_t new_pos)
{
	return 0b01000000 + new_pos;
}

uint8_t disp_page(uint8_t new_page)
{
	return 0b10111000 + new_page;
}

uint8_t disp_start_line(uint8_t new_line)
{
	return 0b11000000 + new_line;
}


void set_CS1()
{
	COMMAND_PORT |= (1 << CS1);
	COMMAND_PORT &= ~(1 << CS2);
}

void set_CS2()
{
	COMMAND_PORT |= (1 << CS2);
	COMMAND_PORT &= ~(1 << CS1);
}

void drawblack()
{
	uint8_t i, j;
	/******************************************************
	* Paint it black, just to see if something happens
	******************************************************/
	
	
	for (i = 0; i < NBR_PAGES; ++i)
	{
		LCD_command(disp_page(i));
		for (j = 0; j < 64; ++j)
		{
			LCD_data(0b00111111);
		}
	}
	LCD_command(disp_ypos(0));
	LCD_command(disp_page(0)); 

}



