#ifndef _TMR1_INTERFACE_H
#define _TMR1_INTERFACE_H
/*****************************************************************/
#define  TCCR1A     *((volatile u8*)0x4F)
#define  TCCR1B     *((volatile u8*)0x4E)

#define  ICR1L     *((volatile u8*)0x46)
#define  ICR1H     *((volatile u8*)0x47)

#define  ICR1     *((volatile u16*)0x46)

#define  OCR1AL     *((volatile u8*)0x4A)
#define  OCR1AH     *((volatile u8*)0x4B)

#define  OCR1A     *((volatile u16*)0x4A)

#define  OCR1BL     *((volatile u8*)0x48)
#define  OCR1BH     *((volatile u8*)0x49)

#define  OCR1B     *((volatile u16*)0x48)

#define  TCNT1L     *((volatile u8*)0x4C)
#define  TCNT1H     *((volatile u8*)0x4D)

#define  TCNT1     *((volatile u16*)0x4C)

#define  TIMSK     *((volatile u8*)0x59)
/***********************************************************************/
/*TCCRA1*/
#define COM1B0    4
#define COM1B1    5
#define COM1A0    6
#define COM1A1    7

#define WGM10     0
#define WGM11     1

/*CompareOutputMode*/
#define OC1A_OC1B_disconnected       0         //Normal port operation
#define Toggle_OC1A_OC1B             1
#define Clear_OC1A_OC1B              2        //Set output to low level
#define Set_OC1A_OC1B                3        //Set output to high level

#define  TMR1_CompareOutputMode         Clear_OC1A_OC1B

/*TCCRB1*/
/*prescaler*/
#define TMR1_NO_Prescaler        1
#define TMR1_Prescaler_8         8
#define TMR1_Prescaler_64        64
#define TMR1_Prescaler_256       256
#define TMR1_Prescaler_1024      1024

#define CS10     0
#define CS11     1
#define CS12     2

#define TMR1_Prescaler     TMR1_Prescaler_8

#define WGM12    3
#define WGM13    4

#define ICES1    6      // Input Capture Edge Select
#define RisingEdge    0
#define FallingEdge   1


/*TIMSK*/
#define TOIE1   2
#define OCIE1B  3
#define OCIE1A  4
#define TICIE1  5


/*TMR1_MOde*/
#define Normal               0
#define PhaseCorrectPWM      1
#define CTC                  2
#define FastPWM              3

#define TMR1_Mode    FastPWM
/************************************************************************/

void TMR1_voidInit(void);
void TMR1_SetCallBack(void (*Ptr)(void));
void TMR1_voidOCR1A(u16 Copy_u16OCR1AValue);
void TMR1_voidPreload(u16 Copy_u16Value);
void TMR1_voidLoadCounterTop(u16 copy_u8CounterTop);
#endif



