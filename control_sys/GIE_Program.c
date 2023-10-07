#include "STD_TYPES.h"
#include "BIT_Math.h"
#include "DIO.h"
#include "GIE_Interface.h"

void EXT_voidGIE_Enable(void)
{
	SET_BIT(SREG , DIO_PIN7);
}

void EXT_voidGIE_Disable(void)
{
	CLR_BIT(SREG , DIO_PIN7);
}
