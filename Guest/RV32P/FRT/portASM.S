/******************************************************************************
Filename    : portASM.s
Author      : hrs
Date        : 05/09/2024
Description : The assembly part of the RVM/FreeRTOS. This is for RV32 with
              physical memory access, hence RV32P.
******************************************************************************/

/* Define ********************************************************************/
#define portCONTEXT_SIZE                (35*4)
/* End Define ****************************************************************/

/* Import ********************************************************************/
    /* Linker-provided global data address */
    .extern             _RVM_Global
    /* Linker-provided kernel stack address */
    .extern             _RVM_Stack
    /* The real task switch handling function */
    .extern             vTaskSwitchContext
    /* The stack address of current thread */
    .extern             pxCurrentTCB
    /* Hypercall parameter space */
    .extern             RVM_Usr_Param
    /* Mask/unmask interrupts */
    .extern             RVM_Virt_Int_Mask
    .extern             RVM_Virt_Int_Unmask
    /* The stack top of ISR of FreeRTOS */
    .extern             xISRStackTop
    /* Enable VM interrupts */
    .extern             RVM_Hyp_Int_Ena
/* End Import ****************************************************************/

/* Export ********************************************************************/
    /* Start the first thread */
    .global             xPortStartFirstTask
    /* Initialize thread stack */
    .global             pxPortInitialiseStack
    /* Fast-path context switching without invoking the RVM and FPU */
    .global             FRT_Ctx_Handler
/* End Export ****************************************************************/

/* Header ********************************************************************/
    .section            ".text.arch"
    .align              3
/* End Header ****************************************************************/

/* Function:FRT_Ctx_Handler ***************************************************
Description : Yield from one thread to another without an interrupt.
              This function only has 1 versions:
              1. no coprocessor;
              The difference with the bare-metal version is that we run the
              scheduler directly on user stack. It is imperative that the hook
              RMP_Ctx_Save and RMP_Ctx_Load does not save extra coprocessor
              context on thread stack, but in extra structures coallocated with
              the thread structure.
              The mstatus needs to be treated very carefully here: it does not
              contain any flags, but contains FPU state, and is not accessible
              from user mode. We're reading the mstatus on the stack when we
              return to decide whether the stack contains FPU state, and are
              trashing register tp (x4; which GCC/LLVM does not allocate anyway)
              to hold the return address (because we're unable to use mepc).
              The RISC-V calling convention requires that the stack be 16-byte
              aligned at all times. However, this is only relevant when we pass
              doubleword parameters, thus we are safe to ignore that convention
              when calling RVM_Virt_Int_Mask and RVM_Virt_Int_Unmask whose call
              chain never does that.
Input       : None.
Output      : None.
Return      : None.
******************************************************************************/
/* Save all GP regs **********************************************************/
    .macro              FRT_RV32P_RVM_SAVE LABEL
    ADDI                sp,sp,-31*4         /* Save registers */
    SW                  x31,30*4(sp)
    SW                  x30,29*4(sp)
    SW                  x29,28*4(sp)
    SW                  x28,27*4(sp)
    SW                  x27,26*4(sp)
    SW                  x26,25*4(sp)
    SW                  x25,24*4(sp)
    SW                  x24,23*4(sp)
    SW                  x23,22*4(sp)
    SW                  x22,21*4(sp)
    SW                  x21,20*4(sp)
    SW                  x20,19*4(sp)
    SW                  x19,18*4(sp)
    SW                  x18,17*4(sp)
    SW                  x17,16*4(sp)
    SW                  x16,15*4(sp)
    SW                  x15,14*4(sp)
    SW                  x14,13*4(sp)
    SW                  x13,12*4(sp)
    SW                  x12,11*4(sp)
    SW                  x11,10*4(sp)
    SW                  x10,9*4(sp)
    SW                  x9,8*4(sp)
    SW                  x8,7*4(sp)
    SW                  x7,6*4(sp)
    SW                  x6,5*4(sp)
    SW                  x5,4*4(sp)
    SW                  x4,3*4(sp)
    SW                  x3,2*4(sp)
    SW                  x1,1*4(sp)
    LA                  a0,\LABEL           /* Save pc - use exit address */
    SW                  a0,0*4(sp)
    CALL                RVM_Virt_Int_Mask   /* Disable interrupts */
    .endm

    /* Actual context switch */
    .macro              FRT_RV32P_RVM_SWITCH
    ADDI                sp,sp,-4            /* Save mstatus */
    SW                  a0,0*4(sp)
    ADDI                sp,sp,-5*4          /* Push hypercall parameters */
    LA                  a0,RVM_Usr_Param
    LW                  a0,(a0)
    LW                  a1,4*4(a0)
    SW                  a1,4*4(sp)
    LW                  a1,3*4(a0)
    SW                  a1,3*4(sp)
    LW                  a1,2*4(a0)
    SW                  a1,2*4(sp)
    LW                  a1,1*4(a0)
    SW                  a1,1*4(sp)
    LW                  a1,0*4(a0)
    SW                  a1,0*4(sp)
    .option             push
    .option             norelax
    LA                  gp,_RVM_Global      /* Load gp for kernel - defined by linker script */
    .option             pop
    
    LW                  t0,pxCurrentTCB     /* Load pxCurrentTCB. */
    SW                  sp,0(t0)            /* Write sp to first TCB member. */
    LA                  sp,_RVM_Stack       /* Load sp for kernel - defined by linker script */
    CALL                vTaskSwitchContext  /* Get the highest ready task */
    LW                  t1,pxCurrentTCB     /* Load pxCurrentTCB. */
    LW                  sp,0(t1)            /* Read sp from first TCB member. */

    LA                  a0,RVM_Usr_Param
    LW                  a0,(a0)             /* Pop hypercall parameters */
    LW                  a1,0*4(sp)
    SW                  a1,0*4(a0)
    LW                  a1,1*4(sp)
    SW                  a1,1*4(a0)
    LW                  a1,2*4(sp)
    SW                  a1,2*4(a0)
    LW                  a1,3*4(sp)
    SW                  a1,3*4(a0)
    LW                  a1,4*4(sp)
    SW                  a1,4*4(a0)
    ADDI                sp,sp,5*4
    LW                  a0,0*4(sp)          /* Read mstatus to decide FPU status, but don't load yet */
    ADDI                sp,sp,4
    .endm

/* Restore all GP regs and simulate a MRET ***********************************/
    .macro              FRT_RV32P_RVM_LOAD
    CALL                RVM_Virt_Int_Unmask /* Enable interrupts */
    LW                  tp,0*4(sp)          /* Load pc - have to trash x4 (tp) for this purpose */
    LW                  x1,1*4(sp)          /* Load registers, but skip x4 (tp) */
    LW                  x3,2*4(sp)
    /* x4 (tp) intentionally skipped */
    LW                  x5,4*4(sp)
    LW                  x6,5*4(sp)
    LW                  x7,6*4(sp)
    LW                  x8,7*4(sp)
    LW                  x9,8*4(sp)
    LW                  x10,9*4(sp)
    LW                  x11,10*4(sp)
    LW                  x12,11*4(sp)
    LW                  x13,12*4(sp)
    LW                  x14,13*4(sp)
    LW                  x15,14*4(sp)
    LW                  x16,15*4(sp)
    LW                  x17,16*4(sp)
    LW                  x18,17*4(sp)
    LW                  x19,18*4(sp)
    LW                  x20,19*4(sp)
    LW                  x21,20*4(sp)
    LW                  x22,21*4(sp)
    LW                  x23,22*4(sp)
    LW                  x24,23*4(sp)
    LW                  x25,24*4(sp)
    LW                  x26,25*4(sp)
    LW                  x27,26*4(sp)
    LW                  x28,27*4(sp)
    LW                  x29,28*4(sp)
    LW                  x30,29*4(sp)
    LW                  x31,30*4(sp)
    ADDI                sp,sp,31*4
    JALR                zero,tp
    .endm

/* No coprocessor ************************************************************/
    .section            .text.FRT_Ctx_Handler
    .align              3

FRT_Ctx_Handler:                            /* Disable interrupts and save registers */
    FRT_RV32P_RVM_SAVE  Yield_Exit
    LI                  a0,0x0088           /* mstatus for no FPU, back to U-mode */
    FRT_RV32P_RVM_SWITCH                    /* Do context switch */
    FRT_RV32P_RVM_LOAD                      /* Enable interrupts and restore registers */
Yield_Exit:
    RET
/* End Function:FRT_Ctx_Handler **********************************************/

/* Function:xPortStartFirstTask ***********************************************
Description : Jump to the user function and will never return from it.
Input       : None.
Output      : None.
Return      : None.
******************************************************************************/
    .section            .text.xPortStartFirstTask
    .align              3
    .func
xPortStartFirstTask:
    LW                  sp,pxCurrentTCB     /* Load pxCurrentTCB. */
    LW                  sp,0(sp)            /* Read sp from first TCB member. */

    LW                  x5,7*4(sp)          /* t0 */
    LW                  x6,8*4(sp)          /* t1 */
    LW                  x7,9*4(sp)          /* t2 */
    LW                  x8,10*4(sp)         /* s0/fp */
    LW                  x9,11*4(sp)         /* s1 */
    LW                  x10,12*4(sp)        /* a0 */
    LW                  x11,13*4(sp)        /* a1 */
    LW                  x12,14*4(sp)        /* a2 */
    LW                  x13,15*4(sp)        /* a3 */
    LW                  x14,16*4(sp)        /* a4 */
    LW                  x15,17*4(sp)        /* a5 */
    LW                  x16,18*4(sp)        /* a6 */
    LW                  x17,19*4(sp)        /* a7 */
    LW                  x18,20*4(sp)        /* s2 */
    LW                  x19,21*4(sp)        /* s3 */
    LW                  x20,22*4(sp)        /* s4 */
    LW                  x21,23*4(sp)        /* s5 */
    LW                  x22,24*4(sp)        /* s6 */
    LW                  x23,25*4(sp)        /* s7 */
    LW                  x24,26*4(sp)        /* s8 */
    LW                  x25,27*4(sp)        /* s9 */
    LW                  x26,28*4(sp)        /* s10 */
    LW                  x27,29*4(sp)        /* s11 */
    LW                  x28,30*4(sp)        /* t3 */
    LW                  x29,31*4(sp)        /* t4 */
    LW                  x30,32*4(sp)        /* t5 */
    LW                  x31,33*4(sp)        /* t6 */

    CALL                RVM_Hyp_Int_Ena
    LW                  x1,5*4(sp)          /* Note for starting the scheduler the exception return address is used as the function return address. */
    ADDI                sp,sp,portCONTEXT_SIZE

    RET
    .endfunc
/* End Function:xPortStartFirstTask ******************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/
