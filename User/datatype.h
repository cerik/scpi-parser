//=============================================================================
// File Description:
//
//=============================================================================
// Log:
//=============================================================================

#ifndef _DATATYPES_H_
#define _DATATYPES_H_

#ifndef __FUNCTION__
#define __FUNCTION__  __FILE__
#endif

#ifdef	__cplusplus
extern "C" {
#endif

typedef         unsigned char  UINT8;
typedef           signed char  INT8;
typedef        unsigned short  UINT16;
typedef          signed short  INT16;
typedef          unsigned int  UINT32;
typedef            signed int  INT32;
typedef                 float  FLOAT32;
typedef                double  FLOAT64;
typedef         unsigned long  UINT64;
typedef           signed long  INT64;

typedef volatile   signed int  VINT32;
typedef volatile unsigned int  VUINT32;

typedef enum{ FALSE = 0, TRUE=1} boolean;

#define NULLCHAR  '\0'

#define MAXUINT8  0xFF
#define MAXUINT16 0xFFFF
#define MAXUINT32 0xFFFFFFFF

typedef enum{GPIO_IN_MODE=0,GPIO_OUT_MODE=1} GPIOMODE;
typedef struct{
    INT32 ms;
    UINT32 t0,t1;
}tagCounter;

#ifdef  DEBUG
/*******************************************************************************
* Macro Name     : assert_param
* Description    : The assert_param macro is used for function's parameters check.
*                  It is used only if the library is compiled in DEBUG mode. 
* Input          : - expr: If expr is FALSE, it calls assert_failed function
*                    which reports the name of the source file and the source
*                    line number of the call that failed. 
*                    If expr is TRUE, it returns no value.
* Return         : None
*******************************************************************************/ 
#define assert_param(expr) ((expr) ? (void)0 : assert_failed((UINT8 *)__FILE__, __LINE__))
__inline  void assert_failed(UINT8* file, UINT32 line);
#else
  #define assert_param(expr) ((void)0)
#endif


#ifdef	__cplusplus
}
#endif

#endif
