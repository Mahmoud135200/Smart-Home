

#ifndef KEYPAD_H_
#define KEYPAD_H_

/*****************************************************************Cfg**************************************************************/

/******************Select kpd port*******************/
#define KPD_PORT		DIO_PORTC

/******************Row pins ( Output pins)***********/
#define KPD_R1_PIN		DIO_PIN0
#define KPD_R2_PIN		DIO_PIN1
#define KPD_R3_PIN		DIO_PIN2
#define KPD_R4_PIN		DIO_PIN3

/******************Columns pins ( Input pins)***********/
#define KPD_C1_PIN		DIO_PIN4
#define KPD_C2_PIN		DIO_PIN5
#define KPD_C3_PIN		DIO_PIN6
#define KPD_C4_PIN		DIO_PIN7

/******************My Keys Cfg**************************/

#define KPD_KEYS		{{ '7', '8', '9', '/'},\
						{ '4', '5', '6', '*'}, \
						{ '1', '2', '3', '-'},\
						{ 'C', '0', '=', '+'}}

/**************************************************************/

#define KPD_CHECK_BUTTON_PRESSED_OR_NOT		0XFF

/*****************************************************************APIs**************************************************************/

void KPD_voidInit(void);
u8   KPD_u8GetPressedKey(void);

#endif /* HAL_KEYPAD_KEYPAD_H_ */
