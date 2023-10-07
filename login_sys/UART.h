/*
 * UART.h
 *
 *  Created on: Aug 27, 2023
 *      Author: Salem Elfaidy
 */

#ifndef UART_H
#define UART_H



/************************************************************ APIs ************************************************************/

void UART_voidInit		(void);
void UART_voidSendData	(u8 Copy_u8Data);
u8	 UART_u8ReceiveData (void);



#endif /* MCAL_UART_UART_H_ */
