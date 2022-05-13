/*
 * game_logic.h
 *
 * Created: 2022-05-11 10:43:40
 *  Author: cid12bel
 */ 


#ifndef GAME_LOGIC_H_
#include <avr/io.h>

/* Screen width max values for x and y */
#define	MAX_X	63
#define MAX_Y	127

//#define BALL_POSITIONS { 0, 0, 1, 3 }
uint8_t	BALL_POSITIONS[] = { 0b00000011, 0b00000110, 0b00001100, 0b00011000, 0b00110000, 0b01100000, 0b11000000, 0b10000000};
	
/******************************************** 
 * this struct contains the ball used in the
 * labyrinth. The ball is 2x2 pixels in size.
 * When collision detecting you should check
 * posx + 1 when v_x is positive and posy + 1
 * when v_y is positive. For negative speeds
 * check posx and posy directly.
 *
 * posx - the X-position of the ball: 0 -- 63
 * posy - the Y-position of the ball: 0 -- 127
 * v_x - the ball's velocity in pixels direction x: -128 -- 127
 * v_y - the ball's velocity in pixels direction y: -128 -- 127
 *  */
typedef struct   
{
	int8_t posx;
	int8_t posy;
	int8_t v_x;
	int8_t v_y;
} ball;

typedef struct {
	
} labyrinth;

uint8_t ball_prev_x = 0;
uint8_t ball_prev_y = 0;

int8_t curr_x = 0;
int8_t curr_y = 0;
int8_t curr_page = 0;

#define GAME_LOGIC_H_





#endif /* GAME_LOGIC_H_ */