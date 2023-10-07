#ifndef LCD_H
#define LCD_H

/*********************************** Cfg ********************************************/
#define	LCD_DATA_PORT		DIO_PORTC
#define	LCD_CONTROL_PORT	DIO_PORTB
#define RS					DIO_PIN0
#define RW					DIO_PIN1
#define EN					DIO_PIN2
/***************************************************************************************************/
#define FUNCTION_SET		0b00111000
#define DISPLAY_ON_OFF		0b00001111
#define CLEAR				0b00000001
/***********************************************************************************************************/

#define LCD_LINE1  			1
#define LCD_LINE2  			2

/**********************************************APIs*************************************/

void LCD_voidInit			(void);
void LCD_voidSendCommand	(u8 Copy_u8Command);
void LCD_voidSendChar		(u8 Copy_u8Char);
void LCD_voidSendString		(u8 *Copy_u8String);
void LCD_voidSetLocation	(u8 Copy_u8LineNum, u8 Copy_u8CharNum);
void LCD_voidSendNumber		(u32 Copy_u32Number);
void LCD_voidDrawSpecialChar(u8 Copy_u8CharIndex, u8 *Copy_u8SpecialChar);
void LCD_voidSendSpecialChar(u8 Copy_u8CharIndex);

#endif
