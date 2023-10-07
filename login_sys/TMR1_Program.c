#include "STD_TYPES.h"
#include "BIT_Math.h"
#include "DIO.h"
#include "TMR1_Interface.h"

void (*TMR1_GlobalPtr)(void) = '\0';

void TMR1_SetCallBack(void (*Ptr)(void))
{
	TMR1_GlobalPtr = Ptr;
}

void TMR1_voidInit(void)
{
	/**********************************TMR1 Prescaler******************************/
#if TMR1_Prescaler == TMR1_NO_Prescaler
	SET_BIT(TCCR1B , CS10);
	CLR_BIT(TCCR1B , CS11);
	CLR_BIT(TCCR1B , CS12);
#elif TMR1_Prescaler == TMR1_Prescaler_8
	CLR_BIT(TCCR1B , CS10);
	SET_BIT(TCCR1B , CS11);
	CLR_BIT(TCCR1B , CS12);
#elif TMR1_Prescaler == TMR1_Prescaler_64
	SET_BIT(TCCR1B , CS10);
	SET_BIT(TCCR1B , CS11);
	CLR_BIT(TCCR1B , CS12);
#elif TMR1_Prescaler == TMR1_Prescaler_256
	CLR_BIT(TCCR1B , CS10);
	CLR_BIT(TCCR1B , CS11);
	SET_BIT(TCCR1B , CS12);
#elif TMR1_Prescaler == TMR1_Prescaler_1024
	SET_BIT(TCCR1B , CS10);
	CLR_BIT(TCCR1B , CS11);
	SET_BIT(TCCR1B , CS12);
#endif

/************************************compare match******************************/
#if TMR1_CompareOutputMode == OC1A_OC1B_disconnected
	CLR_BIT(TCCR1A , COM1B0);
	CLR_BIT(TCCR1A , COM1A0);
	CLR_BIT(TCCR1A , COM1B1);
	CLR_BIT(TCCR1A , COM1A1);
#elif TMR1_CompareOutputMode == Toggle_OC1A_OC1B
	SET_BIT(TCCR1A , COM1B0);
    SET_BIT(TCCR1A , COM1A0);
	CLR_BIT(TCCR1A , COM1B1);
	CLR_BIT(TCCR1A , COM1A1);
#elif TMR1_CompareOutputMode == Clear_OC1A_OC1B
	CLR_BIT(TCCR1A , COM1B0);
    CLR_BIT(TCCR1A , COM1A0);
	SET_BIT(TCCR1A , COM1B1);
	SET_BIT(TCCR1A , COM1A1);
#elif TMR1_CompareOutputMode == Set_OC1A_OC1B
	SET_BIT(TCCR1A , COM1B0);
    SET_BIT(TCCR1A , COM1A0);
	SET_BIT(TCCR1A , COM1B1);
	SET_BIT(TCCR1A , COM1A1);
#endif
/******************************************TMR1 Modes*********************************/
#if TMR1_Mode == Normal
	CLR_BIT(TCCR1A , WGM10);
	CLR_BIT(TCCR1A , WGM11);
	CLR_BIT(TCCR1B , WGM12);
	CLR_BIT(TCCR1B , WGM13);
	/*overflow interrupt enable*/
	//SET_BIT(TIMSK , TOIE1);
	/*capture event*/
	SET_BIT(TIMSK , TICIE1);
#elif TMR1_Mode == PhaseCorrectPWM
	CLR_BIT(TCCR1A , WGM10);
	SET_BIT(TCCR1A , WGM11);
	CLR_BIT(TCCR1B , WGM12);
	SET_BIT(TCCR1B , WGM13);
	ICR1 = 20000;   //for servo
#elif TMR1_Mode == CTC
	CLR_BIT(TCCR1A , WGM10);
	CLR_BIT(TCCR1A , WGM11);
	SET_BIT(TCCR1B , WGM12);
	SET_BIT(TCCR1B , WGM13);
	/*Output Compare Match Interrupt Enable*/
	SET_BIT(TIMSK , OCIE1A);
	//SET_BIT(TIMSK , OCIE1B);
#elif TMR1_Mode == FastPWM
	CLR_BIT(TCCR1A , WGM10);
	SET_BIT(TCCR1A , WGM11);
	SET_BIT(TCCR1B , WGM12);
	SET_BIT(TCCR1B , WGM13);
	ICR1 = 20000;     //for servo
#endif

}

void TMR1_voidOCR1A(u16 Copy_u16OCR1AValue)
{
	OCR1A = Copy_u16OCR1AValue;
}

void TMR1_voidPreload(u16 Copy_u16Value)
{
	TCNT1 = Copy_u16Value;
}

u16 TMR1_u16ICR1(void)
{
	return ICR1;
}

void TMR1_voidLoadCounterTop(u16 copy_u8CounterTop)
{
	ICR1 = copy_u8CounterTop;
}

void TMR1_voidICU_EdgeSelect(u16 Copy_u16EdgeSelect)
{
	switch(Copy_u16EdgeSelect)
	{
	case RisingEdge :
		SET_BIT(TCCR1B , ICES1);
		break;
	case FallingEdge :
		CLR_BIT(TCCR1B , ICES1);
	}
}
void __vector_9()__attribute__((signal));     //overflow
void __vector_9()
{
	if(TMR1_GlobalPtr != '\0')
	{
		TMR1_GlobalPtr();
	}
}

void __vector_7()__attribute__((signal));      //compare
void __vector_7()
{
	if(TMR1_GlobalPtr != '\0')
	{
		TMR1_GlobalPtr();
	}
}

void __vector_6()__attribute__((signal));     //capture event
void __vector_6()
{
	if(TMR1_GlobalPtr != '\0')
	{
		TMR1_GlobalPtr();
	}
}


