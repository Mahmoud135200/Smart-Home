
#include "BIT_Math.h"
#include "STD_Types.h"
#include <avr/io.h>
#include "UART.h"


void UART_voidInit	(void){

	u16 Local_u16BaudRate = 51;
	u8 Local_u8UCSRCvalue = 0b10000000;

	/*1- Set baud rate */
	UBRRL = (u8) Local_u16BaudRate;
	UBRRH = (u8) (Local_u16BaudRate >> 8);

	/*2- Select normal speed */
	CLR_BIT(UCSRA, U2X);

	/*3- disable Mluti-Processor mode */
	CLR_BIT(UCSRA, MPCM);

	/*4- enable receiver & Transmitter */
	SET_BIT(UCSRB, RXEN);
	SET_BIT(UCSRB, TXEN);

	/*5- select 8 bite data */
	CLR_BIT(UCSRB, UCSZ2);
	SET_BIT(Local_u8UCSRCvalue, UCSZ1);
	SET_BIT(Local_u8UCSRCvalue, UCSZ0);

	/*6- select Asynchronous */
	CLR_BIT(Local_u8UCSRCvalue, UMSEL);

	/*7- Disabled parity */
	CLR_BIT(Local_u8UCSRCvalue, UPM0);
	CLR_BIT(Local_u8UCSRCvalue, UPM1);

	/*8- Set 2 stop bits */
	SET_BIT(Local_u8UCSRCvalue, USBS);

	/*9- disable clock polarity */
	CLR_BIT(Local_u8UCSRCvalue, UCPOL);

	/*10- assign Local_u8UCSRCvalue to UCSRC */
	UCSRC = Local_u8UCSRCvalue;

}


void UART_voidSendData	(u8 Copy_u8Data){

	/* Wait for empty transmit buffer */
	while(GET_BIT(UCSRA, UDRE) == 0);

	/* Put data into buffer, sends the data */
	UDR = Copy_u8Data;
}


u8	 UART_u8ReceiveData (void){

	/* Wait for data to be received */
	while(GET_BIT(UCSRA, RXC) == 0);

	/* Get and return received data from buffer */
	return UDR;
}

