/*-------------------------------------------------------------------
 [FILE NAME]: app.c
 [AUTHOR(S)]: Zyad Nezar
 [DATE CREATED]: 15/10/2022
 [DESCRIPTION]: Source file for the Application
 -------------------------------------------------------------------*/

/*----------------------------INCLUDES----------------------------*/

#include "HAL/lcd.h"
#include "HAL/ultrasonic.h"
#include "avr/io.h"

int main(void) {
	uint16 distance = 0;
	SREG |= (1 << 7); /* Enable Global interrupts*/

	/* RW of the LCD is given 0 on PORTB1 */
	DDRB |= (1 << 1);
	PORTB &= ~(1 << 1);
	LCD_init();
	Ultrasonic_init();
	LCD_moveCursor(1, 3);
	LCD_displayString("Distance is");
	for (;;) {
		distance = Ultrasonic_readDistance();
		LCD_moveCursor(2, 3);
		LCD_intgerToString(distance);
		LCD_displayString("  cm");
	}
	return 0;
}
