/********************************************/
/* Description : Standard lib for new types */
/* Author      : Salem Elfaidy             */
/* Date        : 18-7-2023                   */
/* Version     :  0.1 V                     */
/********************************************/

 #ifndef   STD_TYPES_H
 #define   STD_TYPES_H
 
 
typedef  unsigned char      u8    ;
typedef  unsigned short int u16   ;
typedef  unsigned long  int u32   ;
typedef  signed char        s8    ;
typedef  signed short  int  s16   ;
typedef  signed long   int  s32   ;
typedef  float              f32   ;
typedef  double             f64   ;
typedef  long double        f128  ;
typedef  unsigned long long  int u64 ;

/*user expected errors*/
typedef enum {
	FUN_OK,
	FUN_NOK,
	PARAM_OUT_OF_RANGE ,
	 
}enuErrorStatus;


#endif



