#ifndef _EXT_INTERFACE_H
#define _EXT_INTERFACE_H
#define  SREG    *((volatile u8*)0x5F)
void EXT_voidGIE_Enable(void);
void EXT_voidGIE_Disable(void);

#endif
