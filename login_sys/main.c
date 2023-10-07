#include "STD_TYPES.h"
#include "BIT_Math.h"
#include <avr/io.h>
#include "DIO.h"
#include "LCD.h"
#include "KEYPAD.h"
#include "TMR1_Interface.h"
#include "UART.h"
#include <util/delay.h>


int main(){


	u8 input, i=0, wrong = 0, warning = 0;
	u8 currentPass[] = "1112";


	// Initialization
	LCD_voidInit();
	KPD_voidInit();
	TMR1_voidInit();
	UART_voidInit();

	// Servo motor setup
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN5, DIO_OUTPUT);

	// Warning LED
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN4, DIO_OUTPUT);

	 LCD_voidSendString("Enter pass:");

	while(1)
	{

		input =KPD_u8GetPressedKey();
		if(input != KPD_CHECK_BUTTON_PRESSED_OR_NOT	)
		{
			//LCD_voidSetLocation(2,0);
			/* Reset key is pressed
			 * Reset password characters counter and reset flag
			 * Reset warning LED
			 */
			if (input == 'C')
			{
				i = 0;
				wrong = 0;
				warning = 1;
				LCD_voidSendCommand(CLEAR);
			    _delay_ms(2);
			    LCD_voidSendString("RESET");
                DIO_voidSetPinValue(DIO_PORTA, DIO_PIN4, DIO_HIGH);
				_delay_ms(250);
				DIO_voidSetPinValue(DIO_PORTA, DIO_PIN4, DIO_LOW);
			    _delay_ms(250);
			    LCD_voidSendCommand(CLEAR);
			    _delay_ms(2);
			    LCD_voidSendString("Enter pass:");
			}

			/* Check the pressed input with the relative character in the reserved password
			 * Set the flag to 1 in case of wrong input
			 */
			else{


			LCD_voidSendChar('*');

			if(input != currentPass[i])
			{
				wrong = 1;
			}
			i++;

			// Check the flag and display the output on the LCD
			if (i == 4)
			{
				LCD_voidSendCommand(CLEAR);
					_delay_ms(2);

				if (wrong == 0)
				{
					 LCD_voidSendString("Welcome");
					 UART_voidSendData('A');
					 _delay_ms(1000);
					 TMR1_voidOCR1A(1500);
					_delay_ms(2000);
					TMR1_voidOCR1A(999);
					// DIO_voidSetPinValue(DIO_PORTD, DIO_PIN5,1);
					//_delay_ms(2000);
					//DIO_voidSetPinValue(DIO_PORTD, DIO_PIN5,0);
					LCD_voidSendCommand(CLEAR);
				    _delay_ms(2);
	               LCD_voidSendString("Enter password");

				}

				else
				{


					  LCD_voidSendString("WRONG PASS");
					  _delay_ms(500);
					  LCD_voidSendCommand(CLEAR);
					  _delay_ms(2);
					LCD_voidSendString("TRY AGAIN:");


				}

				// Reset variables to start a new loop (Ask for password again)
				i = 0;
				wrong = 0;

                   }


             }
		}

	}

	return 0;

}
