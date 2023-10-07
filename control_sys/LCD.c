#include <avr/io.h>
#include <util/delay.h>
#include "STD_Types.h"
#include "BIT_Math.h"
#include "DIO.h"
#include "LCD.h"

void LCD_voidInit(void){
	/* Data port -> output*/
	DIO_voidSetPortDirection(LCD_DATA_PORT, 0XFF);
	/* RS, RW, E  -> output */
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, RS, DIO_OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, RW, DIO_OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, EN, DIO_OUTPUT);
	
	_delay_ms(35);
	LCD_voidSendCommand(FUNCTION_SET);
	_delay_us(50);
	LCD_voidSendCommand(DISPLAY_ON_OFF);
	_delay_us(50);
	LCD_voidSendCommand(CLEAR);
	_delay_ms(2);
}


void LCD_voidSendCommand(u8 Copy_u8Command){
	
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RS, DIO_LOW);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RW, DIO_LOW);
	DIO_voidSetPortValue(LCD_DATA_PORT, Copy_u8Command);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, EN, DIO_HIGH);
	_delay_us(1);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, EN, DIO_LOW);	
}


void LCD_voidSendChar(u8 Copy_u8Char){
	
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RS, DIO_HIGH);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RW, DIO_LOW);
	DIO_voidSetPortValue(LCD_DATA_PORT, Copy_u8Char);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, EN, DIO_HIGH);
	_delay_us(1);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, EN, DIO_LOW);
	
}

void LCD_voidSendString	(u8 *Copy_u8String){

	u8 Local_U8Counter ;
	for (Local_U8Counter = 0 ; Copy_u8String[Local_U8Counter] != '\0' ; Local_U8Counter++){
		LCD_voidSendChar(Copy_u8String[Local_U8Counter]);}
	
	
}

void LCD_voidSetLocation(u8 Copy_u8LineNum, u8 Copy_u8CharNum){
	
	switch(Copy_u8LineNum)
	{
	case LCD_LINE1 : LCD_voidSendCommand(0x80 + Copy_u8CharNum); break;

	case LCD_LINE2 : LCD_voidSendCommand(0xC0 + Copy_u8CharNum); break;

	}
	
}

void LCD_voidSendNumber	(u32 Copy_u32Number){
	u8 Local_u8ASingleNum[11], Local_u8Count = 9;
	
	if (Copy_u32Number == 0) { LCD_voidSendChar('0');}
	else{
		Local_u8ASingleNum[10] = '\0' ;
		while (Copy_u32Number != 0)
		{
			Local_u8ASingleNum[Local_u8Count] = ((Copy_u32Number % 10) + '0') ;
			Copy_u32Number /= 10 ;
			Local_u8Count--;
		}
		/* send address of the first number in my array till the '\0' */
		LCD_voidSendString(Local_u8ASingleNum + Local_u8Count + 1);
	}
}


void LCD_voidDrawSpecialChar(u8 Copy_u8CharIndex, u8 *Copy_u8SpecialChar){
	
	LCD_voidSendCommand(0b01000000+(Copy_u8CharIndex * 8));
	_delay_us(40);
	u8 LCD_U8Counter ;
	for (LCD_U8Counter=0 ; LCD_U8Counter<8 ; LCD_U8Counter++)
	{
		LCD_voidSendChar(Copy_u8SpecialChar[LCD_U8Counter]);
	}


}

void LCD_voidSendSpecialChar(u8 Copy_u8CharIndex){
	
	LCD_voidSendChar(Copy_u8CharIndex);
}


