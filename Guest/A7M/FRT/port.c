/******************************************************************************
Filename    : port.c
Author      : hrs
Date        : 14/07/2024
Licence     : The Unlicense; see LICENSE for details.
Description : The ARMv7-M FreeRTOS guest OS support source. This supports all
              compilers that the RVM supports.
              This file is NOT a part of the FreeRTOS distribution!
******************************************************************************/

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "rvm_guest.h"

#ifndef __VFP_FP__
    #error This port can only be used when the project options are configured to enable hardware floating point support.
#endif

#ifndef configSYSTICK_CLOCK_HZ
    #define configSYSTICK_CLOCK_HZ configCPU_CLOCK_HZ
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #define portNVIC_SYSTICK_CLK_BIT        (1UL<<2UL)
#else
    /* The way the SysTick is clocked is not modified in case it is not the same
    as the core. */
    #define portNVIC_SYSTICK_CLK_BIT        (0U)
#endif

/* FPU registers */
#define FRT_FPU                             ((volatile struct RVM_A7M_Cop_Struct*)(RVM_REG->Cop))

/* Constants required to set up the initial stack. */
#define portINITIAL_XPSR                    (0x01000000)
#define portINITIAL_EXEC_RETURN             (0xFFFFFFFD)

/* A fiddle factor to estimate the number of SysTick counts that would have
occurred while the SysTick counter is stopped during tickless idle
calculations. */
#define portMISSED_COUNTS_FACTOR            (45UL)

/* For strict compliance with the Cortex-M spec the task start address should
have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#define portSTART_ADDRESS_MASK              ((StackType_t)0xFFFFFFFEUL)

/* Let the user override the pre-loading of the initial LR with the address of
prvTaskExitError() in case it messes up unwinding of the stack in the
debugger. */
#ifdef configTASK_RETURN_ADDRESS
    #define portTASK_RETURN_ADDRESS         configTASK_RETURN_ADDRESS
#else
    #define portTASK_RETURN_ADDRESS         prvTaskExitError
#endif

/* Each task maintains its own interrupt status in the critical nesting
variable. */
static UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
void vPortSetupTimerInterrupt( void );

/*
 * Exception handlers.
 */
void xPortPendSVHandler( void );
void xPortSysTickHandler( void );
void vPortSVCHandler( void );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
static void prvPortStartFirstTask( void );

/*
 * Function to enable the VFP.
 */
 static void vPortEnableVFP( void ) __attribute__ (( naked ));

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
static void prvTaskExitError( void );

/*-----------------------------------------------------------*/

/*
 * The number of SysTick increments that make up one tick period.
 */
#if configUSE_TICKLESS_IDLE == 1
    static uint32_t ulTimerCountsForOneTick = 0;
#endif /* configUSE_TICKLESS_IDLE */

/*
 * The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer.
 */
#if configUSE_TICKLESS_IDLE == 1
    static uint32_t xMaximumPossibleSuppressedTicks = 0;
#endif /* configUSE_TICKLESS_IDLE */

/*
 * Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only.
 */
#if configUSE_TICKLESS_IDLE == 1
    static uint32_t ulStoppedTimerCompensation = 0;
#endif /* configUSE_TICKLESS_IDLE */

/*
 * Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#if ( configASSERT_DEFINED == 1 )
     static uint8_t ucMaxSysCallPriority = 0;
     static uint32_t ulMaxPRIGROUPValue = 0;
     static const volatile uint8_t * const pcInterruptPriorityRegisters = ( const volatile uint8_t * const ) portNVIC_IP_REGISTERS_OFFSET_16;
#endif /* configASSERT_DEFINED */

/*-----------------------------------------------------------*/

uint32_t SystemCoreClock=216000000U;

/*
 * See header file for description.
 */
StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
    interrupt. */

    /* Offset added to account for the way the MCU uses the stack on entry/exit
    of interrupts, and to ensure alignment. */
    pxTopOfStack--;

    *pxTopOfStack = portINITIAL_XPSR;    /* xPSR */
    pxTopOfStack--;
    *pxTopOfStack = ( ( StackType_t ) pxCode ) & portSTART_ADDRESS_MASK;    /* PC */
    pxTopOfStack--;
    *pxTopOfStack = ( StackType_t ) portTASK_RETURN_ADDRESS;    /* LR */

    /* Save code space by skipping register initialisation. */
    pxTopOfStack -= 5;    /* R12, R3, R2 and R1. */
    *pxTopOfStack = ( StackType_t ) pvParameters;    /* R0 */

    /* A save method is being used that requires each task to maintain its
    own exec return value. */
    pxTopOfStack--;
    *pxTopOfStack = portINITIAL_EXEC_RETURN;
    
    /* R11, R10, R9, R8, R7, R6, R5 and R4. */
    pxTopOfStack--;
    *pxTopOfStack = 0x11111111U;
    pxTopOfStack--;
    *pxTopOfStack = 0x10101010U;
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

extern PRIVILEGED_DATA struct tskTaskControlBlock * volatile pxCurrentTCB;
static void prvPortStartFirstTask( void )
{
    /* Lockdown - not changing this in the future */
    // RVM_Hyp_Vct_Lck();
    /* Enable virtual interrupts */
    RVM_Hyp_Int_Ena();
    
    /* Switch to first stack's entry & PC; startup stack is abandoned */
    __asm volatile("LDR     R1,TCB      \n"
                   "LDR     R0,[R1]     \n"
                   "LDR     SP,[R0]     \n"
                   "POP     {R0-R4}     \n"     /* Abandon hypercall parameters */
                   "POP     {R4-R11}    \n"     /* Restore R4-R11 */
                   "POP     {R12}       \n"     /* Abandon "EXEC_RETURN" */
                   "POP     {R0-R3,R12} \n"     /* Restore R0-R3,R12 */
                   "POP     {LR}        \n"     /* Restore PC in LR */
                   "POP     {LR}        \n"
                   "SUB     SP,4        \n"     /* Fix up SP/LR */
                   "ORR     LR,#0x01    \n"
                   "BX      LR          \n"     /* Branch to entry */
                   ".align  4           \n"
                   "TCB:                \n"
                   ".word pxCurrentTCB  \n");
}

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( void )
{
    /* configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to 0.
    See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
    here already. */
    vPortSetupTimerInterrupt();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    /* Start the first task. */
    prvPortStartFirstTask();

    /* Should never get here as the tasks will now be executing!  Call the task
    exit error function to prevent compiler warnings about a static function
    not being called in the case that the application writer overrides this
    functionality by defining configTASK_RETURN_ADDRESS. */
    prvTaskExitError();

    /* Should not get here! */
    return 0;
}
/*-----------------------------------------------------------*/

void vPortEndScheduler( void )
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

void vPortEnterCritical( void )
{
    portDISABLE_INTERRUPTS();
    uxCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
    assert() if it is being called from an interrupt context.  Only API
    functions that end in "FromISR" can be used in an interrupt.  Only assert if
    the critical nesting count is 1 to protect against recursive calls if the
    assert function also uses a critical section. */
    if( uxCriticalNesting == 1 )
    {
        //configASSERT( ( portNVIC_INT_CTRL_REG & portVECTACTIVE_MASK ) == 0 );
    }
}

void vPortExitCritical( void )
{
    configASSERT(uxCriticalNesting);
    uxCriticalNesting--;
    if( uxCriticalNesting == 0 )
    {
        portENABLE_INTERRUPTS();
    }
}

void xPortPendSVHandler(void)
{
    uint32_t* SP;
    
    /* MRS      R0,PSP
     * ISB */
    SP=(uint32_t*)(RVM_REG->Reg.SP);
    
    /* LDR      R3,pxCurrentTCB
     * LDR      R2,[R3] */
    
    /* TST      LR,#0x10
     * IT       EQ
     * VSTMDBEQ R0!,{S16-S31} */
    if((RVM_REG->Reg.LR&0x10U)==0U)
    {
        *(--SP)=FRT_FPU->S31;
        *(--SP)=FRT_FPU->S30;
        *(--SP)=FRT_FPU->S29;
        *(--SP)=FRT_FPU->S28;
        *(--SP)=FRT_FPU->S27;
        *(--SP)=FRT_FPU->S26;
        *(--SP)=FRT_FPU->S25;
        *(--SP)=FRT_FPU->S24;
        *(--SP)=FRT_FPU->S23;
        *(--SP)=FRT_FPU->S22;
        *(--SP)=FRT_FPU->S21;
        *(--SP)=FRT_FPU->S20;
        *(--SP)=FRT_FPU->S19;
        *(--SP)=FRT_FPU->S18;
        *(--SP)=FRT_FPU->S17;
        *(--SP)=FRT_FPU->S16;
    }
    
    /* STMDB    R0!,{R4-R11,LR} */
    *(--SP)=RVM_REG->Reg.LR;
    *(--SP)=RVM_REG->Reg.R11;
    *(--SP)=RVM_REG->Reg.R10;
    *(--SP)=RVM_REG->Reg.R9;
    *(--SP)=RVM_REG->Reg.R8;
    *(--SP)=RVM_REG->Reg.R7;
    *(--SP)=RVM_REG->Reg.R6;
    *(--SP)=RVM_REG->Reg.R5;
    *(--SP)=RVM_REG->Reg.R4;
    
    /* Save hypercall parameter to stack */
    *(--SP)=RVM_STATE->Usr.Param[3];
    *(--SP)=RVM_STATE->Usr.Param[2];
    *(--SP)=RVM_STATE->Usr.Param[1];
    *(--SP)=RVM_STATE->Usr.Param[0];
    *(--SP)=RVM_STATE->Usr.Number;
    
    /* STR      R0,[R2] */
    *((uint32_t*)pxCurrentTCB)=(uint32_t)SP;
    
    vTaskSwitchContext();
    
    /* LDR      R1,[R3] */
    /* LDR      R0,[R1] */
    SP=(uint32_t*)(*((uint32_t*)pxCurrentTCB));
    
    /* Restore hypercall parameter from stack */
    RVM_STATE->Usr.Number=*(SP++);
    RVM_STATE->Usr.Param[0]=*(SP++);
    RVM_STATE->Usr.Param[1]=*(SP++);
    RVM_STATE->Usr.Param[2]=*(SP++);
    RVM_STATE->Usr.Param[3]=*(SP++);
    
    /* LDMIA    R0!,{R4-R11,LR} */
    RVM_REG->Reg.R4=*(SP++);
    RVM_REG->Reg.R5=*(SP++);
    RVM_REG->Reg.R6=*(SP++);
    RVM_REG->Reg.R7=*(SP++);
    RVM_REG->Reg.R8=*(SP++);
    RVM_REG->Reg.R9=*(SP++);
    RVM_REG->Reg.R10=*(SP++);
    RVM_REG->Reg.R11=*(SP++);
    RVM_REG->Reg.LR=*(SP++);
    
    /* TST      LR,#0x10
     * IT       EQ
     * VLDMIAEQ R0!,{S16-S31} */
    if((RVM_REG->Reg.LR&0x10U)==0U)
    {
        FRT_FPU->S16=*(SP++);
        FRT_FPU->S17=*(SP++);
        FRT_FPU->S18=*(SP++);
        FRT_FPU->S19=*(SP++);
        FRT_FPU->S20=*(SP++);
        FRT_FPU->S21=*(SP++);
        FRT_FPU->S22=*(SP++);
        FRT_FPU->S23=*(SP++);
        FRT_FPU->S24=*(SP++);
        FRT_FPU->S25=*(SP++);
        FRT_FPU->S26=*(SP++);
        FRT_FPU->S27=*(SP++);
        FRT_FPU->S28=*(SP++);
        FRT_FPU->S29=*(SP++);
        FRT_FPU->S30=*(SP++);
        FRT_FPU->S31=*(SP++);
    }
    
    /* MSR      PSP,R0 */
    RVM_REG->Reg.SP=(uint32_t)SP;
    /* BX       LR */
    return;
}

void xPortSysTickHandler( void )
{
    portDISABLE_INTERRUPTS();
    
    if(xTaskIncrementTick()!=pdFALSE)
    {
        /* Trigger PendSV */
    }
    
    portENABLE_INTERRUPTS();
}

#if(configUSE_TICKLESS_IDLE==1)
#error RVM: FRT: Tickless idle is not supported in virtualized environment
#endif

void vPortSetupTimerInterrupt( void )
{
    /* Hook Systick & PendSV */
    RVM_Virt_Tim_Reg(xPortSysTickHandler);
    RVM_Virt_Ctx_Reg(xPortPendSVHandler);
}
/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/
