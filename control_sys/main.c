

#include "STD_TYPES.h"
#include "BIT_Math.h"
#include <avr/io.h>
#include "DIO.h"
#include "LCD.h"
#include "GIE_Interface.h"
#include "ADC.h"
#include "TIM0.h"
#include "TMR1_Interface.h"
#include "UART.h"
#include <util/delay.h>
void start(void);
u16 temperature=0 , LDR_OUT , LDR_room1 , LDR_room2 , LDR_room3;
u16 factor , curtain;
u8 Receive =0;
u8 flag=0;
int main()
{


	LCD_voidInit();   	    //LCD Initialized
	ADC_voidInit(ADC_DIV_64);      //ADC Initialized



	// EXT_voidGIE_Enable();
	 TIM0_voidTimerStart(TIM0_PRESCALER_8);
	 TIM0_voidInit();     //Timer0 Initialized

	 DIO_voidSetPinDirection(DIO_PORTB , DIO_PIN3 ,DIO_OUTPUT);

	DIO_voidSetPinDirection(DIO_PORTD , DIO_PIN5 ,DIO_OUTPUT);

	TMR1_voidInit();     //Timer1 Initialized

	UART_voidInit();

	DIO_voidSetPinDirection(DIO_PORTB , DIO_PIN5 ,DIO_OUTPUT);    /*warning led if there is fire*/

	/*leds of 3 Rooms*/
	DIO_voidSetPinDirection(DIO_PORTD , DIO_PIN3 ,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTD , DIO_PIN7 ,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTD , DIO_PIN6 ,DIO_OUTPUT);

	_delay_ms(500);

	Receive=UART_u8ReceiveData();

			while(1){

if(Receive=='A'){
	start();
flag=1;
}
else if(flag==0){
Receive=UART_u8ReceiveData();
}

		}


	return 0;
}



/*FUNCTION TO START THE WHOLE PROJECT*/
void start(void){

	//_________________________controlling fan using temperature sensor______________________

				/*take analog value from temperature sensor , converting it into degree*/

temperature = ADC_u16GetDigitalValue( ADC_Channel_0);
temperature = ( ((u32)temperature*5000)/(u16)1023 ) / 10;         //degree

/*display temperature value over an LCD*/
LCD_voidSendCommand(CLEAR);
	_delay_ms(2);
    LCD_voidSendString("Temp = ");
	LCD_voidSendNumber(temperature);
	LCD_voidSendString("C");

/*control motor of fan depending on the temperature*/
if ((temperature >= 20) && (temperature <= 25))
{
	TIM0_voidPWMGenerator(50, TIM0_OC0_CLR_CMP_SET_OVF );
	LCD_voidSetLocation(2,0);
	LCD_voidSendString("Fan : half speed");
	DIO_voidSetPinValue(DIO_PORTB , DIO_PIN5 , DIO_LOW);
}

else if ((temperature > 25) && (temperature <= 30))
{
	TIM0_voidPWMGenerator(75, TIM0_OC0_CLR_CMP_SET_OVF );
	LCD_voidSetLocation(2,0);
	LCD_voidSendString("Fan : 75% speed");
	DIO_voidSetPinValue(DIO_PORTB , DIO_PIN5 , DIO_LOW);
}

else if ((temperature > 30) && (temperature <= 45))   //high temperatureerature
{
	TIM0_voidPWMGenerator(100, TIM0_OC0_CLR_CMP_SET_OVF );
	LCD_voidSetLocation(2,0);
	LCD_voidSendString("Fan : full speed");
	DIO_voidSetPinValue(DIO_PORTB , DIO_PIN5 , DIO_LOW);
}

/*very high temperature(fire warning)*/
else if(temperature > 45)
{
	TIM0_voidPWMGenerator(0,  TIM0_OC0_CLR_CMP_SET_OVF);
	LCD_voidSetLocation(2,0);
	LCD_voidSendString("Fire warning!!");
	DIO_voidSetPinValue(DIO_PORTB , DIO_PIN5 , DIO_HIGH); //red led ON
	//USART_voidSendData('1');
}

else
{
	TIM0_voidPWMGenerator(0,  TIM0_OC0_CLR_CMP_SET_OVF);
	LCD_voidSetLocation(2,0);
	LCD_voidSendString("Fan OFF");
	DIO_voidSetPinValue(DIO_PORTB , DIO_PIN5 , DIO_LOW);
}

_delay_ms(500);

//__________________controlling a servo motor of the curtain using an LDR_________//

/*
LDR_OUT = ADC_u16GetDigitalValue(ADC_Channel_1);
factor = ( (999-0) / (1023-0) );
curtain = (LDR_OUT*factor)+999;
//Openning or Closing the curtain
TMR1_voidOCR1A(curtain);
_delay_ms(200);
*/


//_____________controlling leds of 3 Rooms using 3 LDR (one in each room)__________________
//___________________________ROOM_1___________________________
/*take value of LDR of room1 , converting them into m_volt*/

LDR_room1 = ADC_u16GetDigitalValue(ADC_Channel_2);
LDR_room1 = ((u32)LDR_room1*5000)/(u16)1023  ; //m-volt

/*condition for led to turn it ON or OFF depending on readings of LDR of room1*/
 if (LDR_room1 < 2500)
{
	DIO_voidSetPinValue(DIO_PORTD ,DIO_PIN3 , DIO_HIGH);
}
else
{
	DIO_voidSetPinValue(DIO_PORTD ,DIO_PIN3 , DIO_LOW);
}
//___________________________ROOM_2____________________________
/*take value of LDR of room2 , converting them into m_volt*/
LDR_room2 =ADC_u16GetDigitalValue(ADC_Channel_3);
LDR_room2 = ((u32)LDR_room2*5000)/(u16)1023  ; //m-volt

/*condition for led to turn it ON or OFF depending on readings of LDR of room2*/
if (LDR_room2 < 2500)
{
	DIO_voidSetPinValue(DIO_PORTD ,DIO_PIN7 , DIO_HIGH);
}
else
{
	DIO_voidSetPinValue(DIO_PORTD ,DIO_PIN7 , DIO_LOW);
}
//___________________________ROOM_3____________________________
/*take value of LDR of room3 , converting them into m_volt*/
LDR_room3 = ADC_u16GetDigitalValue(ADC_Channel_4);
LDR_room3 = ((u32)LDR_room3*5000)/(u16)1023  ; //m-volt

/*condition for led to turn it ON or OFF depending on readings of LDR of room3*/
if (LDR_room3 < 2500)
{
	DIO_voidSetPinValue(DIO_PORTD ,DIO_PIN6 , DIO_HIGH);
}
else
{
	DIO_voidSetPinValue(DIO_PORTD ,DIO_PIN6 , DIO_LOW);
}
}
