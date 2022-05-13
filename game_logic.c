/*
 * game_logic.c
 *
 * Created: 2022-05-13 16:22:03
 *  Author: cid12bel
 */ 

#include <avr/io.h>
#include <stdint.h>
#include "LCD_display.h"
#include "game_logic.h"

void draw_ball()
{
	curr_page = a_ball.posx / NBR_PAGES; /* To know what page we are on */
	curr_x = a_ball.posx % 8; /* Each page is 8 px high. */
	curr_y = a_ball.posy % 64;
	
	/* set which part of the screen to draw on */
	if (a_ball.posy < 64)
	{
		set_CS2(); /* left side */
	}
	else
	{
		set_CS1(); /* right side */
	}
	
	/***********************************************************
	 * First, erase the ball's previous position on the screen *
	 ***********************************************************/
	
	LCD_command(disp_ypos(curr_y));
	LCD_command(disp_page(curr_page));
	
	
	/*** B A L L   L E F T   H A L F  ***/
	LCD_data(0);	/* The '0' needs to be replaced with the tile background. In the real game only the ball needs to be erased. */
	
	if (curr_x == 7 && curr_page < NBR_PAGES - 1 ) /* only on pages 1--6 */
	{
		/* In case we are at the bottom border between pages, 
		   except the bottom page. */
		LCD_command(disp_ypos(curr_y)); /* reset y */
		LCD_command(disp_page(curr_page + 1)); /* move 1 page down */
		LCD_data(0);
		LCD_command(disp_page(curr_page)); /* we need to reset page position again */
	} 
/*
// 	else if (curr_x == 0 && curr_page > 0) / * only on pages 1--7 * /
// 	{
// 		/ * In case we are at the top border between pages, 
// 		   except the top page. * /	
// 		LCD_command(disp_ypos(a_ball.posy)); / * reset y * /
// 		LCD_command(disp_page(--curr_page)); / * move 1 page up * /
// 		LCD_data(0);
// 		LCD_data(0);
// 	}
*/

    /*** B A L L   R I G H T   H A L F  ***/
	if (a_ball.posy == 63)
	{
		set_CS1();
		LCD_command(disp_ypos(0));
		LCD_data(0);
		if (curr_x == 7 && curr_page < NBR_PAGES - 1 ) /* only on pages 1--6 */
		{
			/* In case we are at the bottom border between pages, 
			except the bottom page. */
			LCD_command(disp_ypos(0)); /* reset y */
			LCD_command(disp_page(curr_page + 1)); /* move 1 page down */
			LCD_data(0);
			LCD_command(disp_page(curr_page)); /* we need to reset page position again */
		}
		/* make sure we draw on the left half again when moving the other way */
		if (a_ball.v_y < 0)
		{
			set_CS2();
		}

	}
	else
	{
		LCD_data(0);
		if (curr_x == 7 && curr_page < NBR_PAGES - 1 ) /* only on pages 1--6 */
		{
		/* In case we are at the bottom border between pages, 
			except the bottom page. */
			LCD_command(disp_ypos(curr_y + 1)); /* reset y */
			LCD_command(disp_page(curr_page + 1)); /* move 1 page down */
			LCD_data(0);
			LCD_command(disp_page(curr_page)); /* we need to reset page position again */
		}
	}
		
	/*** B A L L   M O V E   X ***/
	/* set the position we want to draw the ball at */
	a_ball.posx += a_ball.v_x;
	
	/* The ball is 2 px tall. It hits the bottom at x = 62 */
	if ( a_ball.posx > MAX_X - 1 || a_ball.posx < 0)
	{
		a_ball.v_x *= -1;
		a_ball.posx += a_ball.v_x;
	}
		
	/* After the move, recalculate x pos and page */
	curr_x = a_ball.posx % 8;
	curr_page = a_ball.posx / 8;
	
	/*** B A L L   M O V E   Y ***/
	a_ball.posy += a_ball.v_y;
	if ((a_ball.posy == MAX_Y && a_ball.v_y > 0) || (a_ball.posy < 0 && a_ball.v_y < 0))
	{
		a_ball.v_y *= -1;
		a_ball.posy += a_ball.v_y;
	}
	curr_y = a_ball.posy % 64;
	
	if (a_ball.posy < 64)
	{
		set_CS2(); /* left side */
	}
	else
	{
		set_CS1(); /* right side */
	}
	
	/*****************************************************************
	 *    Time to draw the ball                                      *
	 *****************************************************************/


	/*** B A L L   L E F T   H A L F  ***/
	LCD_command(disp_ypos(curr_y));
	LCD_command(disp_page(curr_page));
	LCD_data(BALL_POSITIONS[curr_x]);
	
	
	if (curr_x == 7 && curr_page < NBR_PAGES - 1) /* only on pages 0--6 */
	{
		/* Next page */
		LCD_command(disp_page(curr_page + 1)); /* move to the next page */
		LCD_command(disp_ypos(curr_y)); /* reset y-position */
		LCD_data(0b00000001); /* Only the top pixel will be lit. */
		LCD_command(disp_page(curr_page));
	}
	
	
	/*** B A L L   R I G H T   H A L F  ***/
	
	if (a_ball.posy == 63)
	{
		set_CS1();
		LCD_command(disp_ypos(0));
		LCD_data(BALL_POSITIONS[curr_x]);
		if (curr_x == 7 && curr_page < NBR_PAGES - 1) /* only on pages 0--6 */
		{
			/* Next page */
			LCD_command(disp_page(curr_page + 1)); /* move to the next page */
			LCD_command(disp_ypos(0)); /* reset y-position */
			LCD_data(0b00000001); /* Only the top pixel will be lit. */
		}
	}
	else
	{
		LCD_data(BALL_POSITIONS[curr_x]);
		if (curr_x == 7 && curr_page < NBR_PAGES - 1) /* only on pages 0--6 */
		{
			/* Next page */
			LCD_command(disp_page(curr_page + 1)); /* move to the next page */
			LCD_command(disp_ypos(curr_y + 1)); /* reset y-position */
			LCD_data(0b00000001); /* Only the top pixel will be lit. */	
		}
	}	
}
