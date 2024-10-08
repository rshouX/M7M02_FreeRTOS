/*
 * FreeRTOS Kernel V10.4.6
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the RISC-V RV32 port.
 *----------------------------------------------------------*/

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"

/* Standard includes. */
#include "string.h"

#ifdef configCLINT_BASE_ADDRESS
	#warning The configCLINT_BASE_ADDRESS constant has been deprecated.  configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS are currently being derived from the (possibly 0) configCLINT_BASE_ADDRESS setting.  Please update to define configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS dirctly in place of configCLINT_BASE_ADDRESS.  See https://www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html
#endif

#ifndef configMTIME_BASE_ADDRESS
	#warning configMTIME_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  If the target chip includes a memory-mapped mtime register then set configMTIME_BASE_ADDRESS to the mapped address.  Otherwise set configMTIME_BASE_ADDRESS to 0.  See https://www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html
#endif

#ifndef configMTIMECMP_BASE_ADDRESS
	#warning configMTIMECMP_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  If the target chip includes a memory-mapped mtimecmp register then set configMTIMECMP_BASE_ADDRESS to the mapped address.  Otherwise set configMTIMECMP_BASE_ADDRESS to 0.  See https://www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html
#endif

/* Let the user override the pre-loading of the initial LR with the address of
prvTaskExitError() in case it messes up unwinding of the stack in the
debugger. */
#ifdef configTASK_RETURN_ADDRESS
	#define portTASK_RETURN_ADDRESS	configTASK_RETURN_ADDRESS
#else
	#define portTASK_RETURN_ADDRESS	prvTaskExitError
#endif

/* The stack used by interrupt service routines.  Set configISR_STACK_SIZE_WORDS
to use a statically allocated array as the interrupt stack.  Alternative leave
configISR_STACK_SIZE_WORDS undefined and update the linker script so that a
linker variable names __freertos_irq_stack_top has the same value as the top
of the stack used by main.  Using the linker script method will repurpose the
stack that was used by main before the scheduler was started for use as the
interrupt stack after the scheduler has started. */
#ifdef configISR_STACK_SIZE_WORDS
	static __attribute__ ((aligned(16))) StackType_t xISRStack[ configISR_STACK_SIZE_WORDS ] = { 0 };
	const StackType_t xISRStackTop = ( StackType_t ) &( xISRStack[ configISR_STACK_SIZE_WORDS & ~portBYTE_ALIGNMENT_MASK ] );

	/* Don't use 0xa5 as the stack fill bytes as that is used by the kernerl for
	the task stacks, and so will legitimately appear in many positions within
	the ISR stack. */
	#define portISR_STACK_FILL_BYTE	0xee
#else
	/* __freertos_irq_stack_top define by .ld file */
	extern const uint32_t __freertos_irq_stack_top[];
	const StackType_t xISRStackTop = ( StackType_t ) __freertos_irq_stack_top;
#endif

static UBaseType_t uxCriticalNesting = 0xaaaaaaaa;
/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
void vPortSetupTimerInterrupt( void ) __attribute__(( weak ));
void FRT_Tim_Handler(void);
extern void FRT_Ctx_Handler(void);

/*-----------------------------------------------------------*/
#if( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 )
/* Used to program the machine timer compare register. */
uint64_t ullNextTime = 0ULL;
const uint64_t *pullNextTime = &ullNextTime;
const uint64_t uxTimerIncrementsForOneTick = ( uint64_t) ( ( configCPU_CLOCK_HZ )/( configTICK_RATE_HZ ) ); /* Assumes increment won't go over 32-bits. */
uint64_t const ullMachineTimerCompareRegisterBase = configMTIMECMP_BASE_ADDRESS;
volatile uint64_t * pullMachineTimerCompareRegister = NULL;
#endif

/* Set configCHECK_FOR_STACK_OVERFLOW to 3 to add ISR stack checking to task
stack checking.  A problem in the ISR stack will trigger an assert, not call the
stack overflow hook function (because the stack overflow hook is specific to a
task stack, not the ISR stack). */
#if defined( configISR_STACK_SIZE_WORDS ) && ( configCHECK_FOR_STACK_OVERFLOW > 2 )
	#warning This path not tested, or even compiled yet.

	static const uint8_t ucExpectedStackBytes[] = {
									portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE,		\
									portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE,		\
									portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE,		\
									portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE,		\
									portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE };	\

	#define portCHECK_ISR_STACK() configASSERT( ( memcmp( ( void * ) xISRStack, ( void * ) ucExpectedStackBytes, sizeof( ucExpectedStackBytes ) ) == 0 ) )
#else
	/* Define the function away. */
	#define portCHECK_ISR_STACK()
#endif /* configCHECK_FOR_STACK_OVERFLOW > 2 */

/*-----------------------------------------------------------*/

#if( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 )

	void vPortSetupTimerInterrupt( void )
	{
	uint32_t ulCurrentTimeHigh, ulCurrentTimeLow;
	volatile uint32_t * const pulTimeHigh = ( volatile uint32_t * const ) ( ( configMTIME_BASE_ADDRESS ) + 4UL ); /* 8-byte typer so high 32-bit word is 4 bytes up. */
	volatile uint32_t * const pulTimeLow = ( volatile uint32_t * const ) ( configMTIME_BASE_ADDRESS );
	volatile uint32_t ulHartId;

		__asm volatile( "csrr %0, mhartid" : "=r"( ulHartId ) );
		pullMachineTimerCompareRegister  = ( volatile uint64_t * ) ( ullMachineTimerCompareRegisterBase + ( ulHartId * sizeof( uint64_t ) ) );

		do
		{
			ulCurrentTimeHigh = *pulTimeHigh;
			ulCurrentTimeLow = *pulTimeLow;
		} while( ulCurrentTimeHigh != *pulTimeHigh );

		ullNextTime = ( uint64_t ) ulCurrentTimeHigh;
		ullNextTime <<= 32ULL; /* High 4-byte word is 32-bits up. */
		ullNextTime |= ( uint64_t ) ulCurrentTimeLow;
		ullNextTime += ( uint64_t ) uxTimerIncrementsForOneTick;
		*pullMachineTimerCompareRegister = ullNextTime;

		/* Prepare the time to use after the next tick interrupt. */
		ullNextTime += ( uint64_t ) uxTimerIncrementsForOneTick;
	}

#else
void Ctx_Handler( void );
/* just for wch's systick,don't have mtime */
void vPortSetupTimerInterrupt( void )
{
    /* Hook Systick & PendSV */
    RVM_Virt_Tim_Reg(FRT_Tim_Handler);
    RVM_Virt_Ctx_Reg(Ctx_Handler);
}

#endif /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIME_BASE_ADDRESS != 0 ) */
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( void )
{
extern void xPortStartFirstTask( void );

	/* If there is a CLINT then it is ok to use the default implementation
	in this file, otherwise vPortSetupTimerInterrupt() must be implemented to
	configure whichever clock is to be used to generate the tick interrupt. */
	vPortSetupTimerInterrupt();
    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;
	xPortStartFirstTask();

	/* Should not get here as after calling xPortStartFirstTask() only tasks
	should be executing. */
	return pdFAIL;
}
/*-----------------------------------------------------------*/

void vPortEndScheduler( void )
{
	/* Not implemented. */
	for( ;; );
}
// /*-----------------------------------------------------------*/
// void SysTick_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void FRT_Tim_Handler( void )
{
    portDISABLE_INTERRUPTS();
    if( xTaskIncrementTick() != pdFALSE )
    {
		/* Trigger yield. */
    }
    portENABLE_INTERRUPTS();
}

extern PRIVILEGED_DATA struct tskTaskControlBlock * volatile pxCurrentTCB;
void Ctx_Handler( void )
{
	uint32_t* SP;
    uint32_t MSTATUS;
    
    /* ADDI     sp,sp,-31*4         Save registers
     * SW       x31,30*4(sp)
     * SW       x30,29*4(sp)
     * SW       x29,28*4(sp)
     * SW       x28,27*4(sp)
     * SW       x27,26*4(sp)
     * SW       x26,25*4(sp)
     * SW       x25,24*4(sp)
     * SW       x24,23*4(sp)
     * SW       x23,22*4(sp)
     * SW       x22,21*4(sp)
     * SW       x21,20*4(sp)
     * SW       x20,19*4(sp)
     * SW       x19,18*4(sp)
     * SW       x18,17*4(sp)
     * SW       x17,16*4(sp)
     * SW       x16,15*4(sp)
     * SW       x15,14*4(sp)
     * SW       x14,13*4(sp)
     * SW       x13,12*4(sp)
     * SW       x12,11*4(sp)
     * SW       x11,10*4(sp)
     * SW       x10,9*4(sp)
     * SW       x9,8*4(sp)
     * SW       x8,7*4(sp)
     * SW       x7,6*4(sp)
     * SW       x6,5*4(sp)
     * SW       x5,4*4(sp)
     * SW       x4,3*4(sp)
     * SW       x3,2*4(sp)
     * SW       x1,1*4(sp)
     * CSRR     a0,mepc
     * SW       a0,1*4(sp)
     * CSRR     a0,mstatus */
    SP=((uint32_t*)(RVM_REG->Reg.X2_SP))-31U;
    SP[30U]=RVM_REG->Reg.X31_T6;
    SP[29U]=RVM_REG->Reg.X30_T5;
    SP[28U]=RVM_REG->Reg.X29_T4;
    SP[27U]=RVM_REG->Reg.X28_T3;
    SP[26U]=RVM_REG->Reg.X27_S11;
    SP[25U]=RVM_REG->Reg.X26_S10;
    SP[24U]=RVM_REG->Reg.X25_S9;
    SP[23U]=RVM_REG->Reg.X24_S8;
    SP[22U]=RVM_REG->Reg.X23_S7;
    SP[21U]=RVM_REG->Reg.X22_S6;
    SP[20U]=RVM_REG->Reg.X21_S5;
    SP[19U]=RVM_REG->Reg.X20_S4;
    SP[18U]=RVM_REG->Reg.X19_S3;
    SP[17U]=RVM_REG->Reg.X18_S2;
    SP[16U]=RVM_REG->Reg.X17_A7;
    SP[15U]=RVM_REG->Reg.X16_A6;
    SP[14U]=RVM_REG->Reg.X15_A5;
    SP[13U]=RVM_REG->Reg.X14_A4;
    SP[12U]=RVM_REG->Reg.X13_A3;
    SP[11U]=RVM_REG->Reg.X12_A2;
    SP[10U]=RVM_REG->Reg.X11_A1;
    SP[9U]=RVM_REG->Reg.X10_A0;
    SP[8U]=RVM_REG->Reg.X9_S1;
    SP[7U]=RVM_REG->Reg.X8_S0_FP;
    SP[6U]=RVM_REG->Reg.X7_T2;
    SP[5U]=RVM_REG->Reg.X6_T1;
    SP[4U]=RVM_REG->Reg.X5_T0;
    SP[3U]=RVM_REG->Reg.X4_TP;
    SP[2U]=RVM_REG->Reg.X3_GP;
    SP[1U]=RVM_REG->Reg.X1_RA;
    SP[0U]=RVM_REG->Reg.PC;
    MSTATUS=RVM_REG->Reg.MSTATUS;   /* Read mstatus to decide FPU status, but don't save yet */

    /* ADDI     sp,sp,-4            Save mstatus
     * SW       a0,0*4(sp) */
    SP--;
    SP[0U]=MSTATUS;

    /* Store all the user-accessible hypercall structure to stack */
    SP-=5U;
    SP[4U]=RVM_STATE->Usr.Param[3];
    SP[3U]=RVM_STATE->Usr.Param[2];
    SP[2U]=RVM_STATE->Usr.Param[1];
    SP[1U]=RVM_STATE->Usr.Param[0];
    SP[0U]=RVM_STATE->Usr.Number;

    /* STR      R0,[R2] */
    *((uint32_t*)pxCurrentTCB)=(uint32_t)SP;
    
    vTaskSwitchContext();
    
    /* LDR      R1,[R3] */
    /* LDR      R0,[R1] */
    SP=(uint32_t*)(*((uint32_t*)pxCurrentTCB));

    /* Load the user-accessible hypercall structure to stack */
    RVM_STATE->Usr.Number=SP[0U];
    RVM_STATE->Usr.Param[0]=SP[1U];
    RVM_STATE->Usr.Param[1]=SP[2U];
    RVM_STATE->Usr.Param[2]=SP[3U];
    RVM_STATE->Usr.Param[3]=SP[4U];
    SP+=5U;

    /* LW       a0,0*4(sp)          Read mstatus to decide FPU status, but don't load yet
     * ADDI     sp,sp,4 */
    MSTATUS=SP[0U];
    SP++;

    /* LI       a1,0x1880           Load mstatus - force M mode with enabled interrupt
     * OR       a0,a0,a1
     * CSRW     mstatus,a0
     * The RVM port is actually forcing U mode; we keep the original for reference */
    RVM_REG->Reg.MSTATUS=MSTATUS;

    /* LW       a0,0*4(sp)          Load pc
     * CSRW     mepc,a0
     * LW       x1,1*4(sp)          Load registers
     * LW       x3,2*4(sp)
     * LW       x4,3*4(sp)
     * LW       x5,4*4(sp)
     * LW       x6,5*4(sp)
     * LW       x7,6*4(sp)
     * LW       x8,7*4(sp)
     * LW       x9,8*4(sp)
     * LW       x10,9*4(sp)
     * LW       x11,10*4(sp)
     * LW       x12,11*4(sp)
     * LW       x13,12*4(sp)
     * LW       x14,13*4(sp)
     * LW       x15,14*4(sp)
     * LW       x16,15*4(sp)
     * LW       x17,16*4(sp)
     * LW       x18,17*4(sp)
     * LW       x19,18*4(sp)
     * LW       x20,19*4(sp)
     * LW       x21,20*4(sp)
     * LW       x22,21*4(sp)
     * LW       x23,22*4(sp)
     * LW       x24,23*4(sp)
     * LW       x25,24*4(sp)
     * LW       x26,25*4(sp)
     * LW       x27,26*4(sp)
     * LW       x28,27*4(sp)
     * LW       x29,28*4(sp)
     * LW       x30,29*4(sp)
     * LW       x31,30*4(sp)
     * ADDI     sp,sp,31*4 */
    RVM_REG->Reg.PC=SP[0U];
    RVM_REG->Reg.X1_RA=SP[1U];
    RVM_REG->Reg.X3_GP=SP[2U];
    RVM_REG->Reg.X4_TP=SP[3U];
    RVM_REG->Reg.X5_T0=SP[4U];
    RVM_REG->Reg.X6_T1=SP[5U];
    RVM_REG->Reg.X7_T2=SP[6U];
    RVM_REG->Reg.X8_S0_FP=SP[7U];
    RVM_REG->Reg.X9_S1=SP[8U];
    RVM_REG->Reg.X10_A0=SP[9U];
    RVM_REG->Reg.X11_A1=SP[10U];
    RVM_REG->Reg.X12_A2=SP[11U];
    RVM_REG->Reg.X13_A3=SP[12U];
    RVM_REG->Reg.X14_A4=SP[13U];
    RVM_REG->Reg.X15_A5=SP[14U];
    RVM_REG->Reg.X16_A6=SP[15U];
    RVM_REG->Reg.X17_A7=SP[16U];
    RVM_REG->Reg.X18_S2=SP[17U];
    RVM_REG->Reg.X19_S3=SP[18U];
    RVM_REG->Reg.X20_S4=SP[19U];
    RVM_REG->Reg.X21_S5=SP[20U];
    RVM_REG->Reg.X22_S6=SP[21U];
    RVM_REG->Reg.X23_S7=SP[22U];
    RVM_REG->Reg.X24_S8=SP[23U];
    RVM_REG->Reg.X25_S9=SP[24U];
    RVM_REG->Reg.X26_S10=SP[25U];
    RVM_REG->Reg.X27_S11=SP[26U];
    RVM_REG->Reg.X28_T3=SP[27U];
    RVM_REG->Reg.X29_T4=SP[28U];
    RVM_REG->Reg.X30_T5=SP[29U];
    RVM_REG->Reg.X31_T6=SP[30U];
    RVM_REG->Reg.X2_SP=(uint32_t)(SP+31U);

    /* MRET */
    return;
}

/*-----------------------------------------------------------*/
void vPortEnterCritical( void )
{
    portDISABLE_INTERRUPTS();
    uxCriticalNesting++;
}

/*-----------------------------------------------------------*/
void vPortExitCritical( void )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;

    if( uxCriticalNesting == 0 )
    {
        portENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/
portUBASE_TYPE xPortSetInterruptMask(void)
{
    return 0;
}

/*-----------------------------------------------------------*/
extern uint32_t _RVM_Global;
StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters )
{
	/* x31...x11 */
	pxTopOfStack--;
	*pxTopOfStack = 0x31313131U;
	pxTopOfStack--;
	*pxTopOfStack = 0x30303030U;
	pxTopOfStack--;
	*pxTopOfStack = 0x29292929U;
	pxTopOfStack--;
	*pxTopOfStack = 0x28282828U;
	pxTopOfStack--;
	*pxTopOfStack = 0x27272727U;
	pxTopOfStack--;
	*pxTopOfStack = 0x26262626U;
	pxTopOfStack--;
	*pxTopOfStack = 0x25252525U;
	pxTopOfStack--;
	*pxTopOfStack = 0x24242424U;
	pxTopOfStack--;
	*pxTopOfStack = 0x23232323U;
	pxTopOfStack--;
	*pxTopOfStack = 0x22222222U;
	pxTopOfStack--;
	*pxTopOfStack = 0x21212121U;
	pxTopOfStack--;
	*pxTopOfStack = 0x20202020U;
	pxTopOfStack--;
	*pxTopOfStack = 0x19191919U;
	pxTopOfStack--;
	*pxTopOfStack = 0x18181818U;
	pxTopOfStack--;
	*pxTopOfStack = 0x17171717U;
	pxTopOfStack--;
	*pxTopOfStack = 0x16161616U;
	pxTopOfStack--;
	*pxTopOfStack = 0x15151515U;
	pxTopOfStack--;
	*pxTopOfStack = 0x14141414U;
	pxTopOfStack--;
	*pxTopOfStack = 0x13131313U;
	pxTopOfStack--;
	*pxTopOfStack = 0x12121212U;
	pxTopOfStack--;
	*pxTopOfStack = 0x11111111U;
	/* push pvParameters */
	pxTopOfStack--;
	*pxTopOfStack = (uint32_t)pvParameters;
	/* x9...x3 */
	pxTopOfStack--;
	*pxTopOfStack = 0x09090909U;
	pxTopOfStack--;
	*pxTopOfStack = 0x08080808U;
	pxTopOfStack--;
	*pxTopOfStack = 0x07070707U;
	pxTopOfStack--;
	*pxTopOfStack = 0x06060606U;
	pxTopOfStack--;
	*pxTopOfStack = 0x05050505U;
	pxTopOfStack--;
	*pxTopOfStack = 0x04040404U;
	pxTopOfStack--;
	*pxTopOfStack = (uint32_t)(&_RVM_Global);

	/* x1 - return address */
	pxTopOfStack--;
	*pxTopOfStack = 0x0U;

	/* push pxCode */
	pxTopOfStack--;
	*pxTopOfStack = (uint32_t)pxCode;

	/* mstatus */
	pxTopOfStack--;
	*pxTopOfStack = 0x0088U;

	/* Clean up hypercall registers */
	pxTopOfStack--;
	*pxTopOfStack = 0U;
	pxTopOfStack--;
	*pxTopOfStack = 0U;
	pxTopOfStack--;
	*pxTopOfStack = 0U;
	pxTopOfStack--;
	*pxTopOfStack = 0U;
	pxTopOfStack--;
	*pxTopOfStack = 0U;

	return pxTopOfStack;
}
/*-----------------------------------------------------------*/

static void prvTaskExitError( void )
{
    /* A function that implements a task must not exit or attempt to return to
    its caller as there is nothing to return to.  If a task wants to exit it
    should instead call vTaskDelete( NULL ).

    Artificially force an assert() to be triggered if configASSERT() is
    defined, then stop here so application writers can catch the error. */
    configASSERT( uxCriticalNesting == ~0UL );
    portDISABLE_INTERRUPTS();
    for( ;; );
}
/*-----------------------------------------------------------*/