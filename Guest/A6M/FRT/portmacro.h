/******************************************************************************
Filename    : portmacro.h
Author      : hrs
Date        : 09/08/2024
Licence     : The Unlicense; see LICENSE for details.
Description : The ARMv7-M FreeRTOS guest OS support header. This supports all
              compilers that the RVM supports.
              This file is NOT a part of the FreeRTOS distribution!
******************************************************************************/
#ifndef PORTMACRO_H
#define PORTMACRO_H

/* Include *******************************************************************/
#include "rvm_guest.h"
/* End Include ***************************************************************/

/* Define ********************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/* Type definitions. */
#define portCHAR                                char
#define portFLOAT                               float
#define portDOUBLE                              double
#define portLONG                                long
#define portSHORT                               short
#define portSTACK_TYPE                          uint32_t
#define portBASE_TYPE                           long

typedef portSTACK_TYPE                          StackType_t;
typedef long                                    BaseType_t;
typedef unsigned long                           UBaseType_t;

#if( configUSE_16_BIT_TICKS == 1 )
typedef uint16_t                                TickType_t;
#define portMAX_DELAY ( TickType_t )            (0xFFFFU)
#else
typedef uint32_t                                TickType_t;
#define portMAX_DELAY ( TickType_t )            (0xFFFFFFFFUL)
#define portTICK_TYPE_IS_ATOMIC                 1
#endif

/* Architecture specifics. */
#define portSTACK_GROWTH                        (-1)
#define portTICK_PERIOD_MS                      ((TickType_t)1000/configTICK_RATE_HZ)
#define portBYTE_ALIGNMENT                      8

/* Scheduler utilities. */
extern void vPortYield(void);
RVM_EXTERN void _FreeRTOS_A6M_RVM_Yield(void);
#define portYIELD()                             _FreeRTOS_A6M_RVM_Yield()
#define portEND_SWITCHING_ISR(xSwitchRequired) \
do \
{ \
    if(xSwitchRequired!=pdFALSE ) \
        RVM_Virt_Yield(); \
} \
while(0)
#define portYIELD_FROM_ISR(x)                   portEND_SWITCHING_ISR(x)

/* Critical section management. */
extern void vPortEnterCritical( void );
extern void vPortExitCritical( void );

#define portSET_INTERRUPT_MASK_FROM_ISR()       ulPortRaiseBASEPRI()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR(x)
#define portDISABLE_INTERRUPTS()                RVM_Virt_Int_Mask()
#define portENABLE_INTERRUPTS()                 RVM_Virt_Int_Unmask()
#define portENTER_CRITICAL()                    vPortEnterCritical()
#define portEXIT_CRITICAL()                     vPortExitCritical()

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO(vFunction,pvParameters) \
                                                void vFunction(void *pvParameters)
#define portTASK_FUNCTION(vFunction,pvParameters) \
                                                void vFunction(void *pvParameters)

#define portNOP()

static uint32_t ulPortRaiseBASEPRI(void)
{
    return 0U;
}


#ifdef __cplusplus
}
#endif
/* End Define ****************************************************************/

/* End Of File ***************************************************************/
#endif /* PORTMACRO_H */
/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/
