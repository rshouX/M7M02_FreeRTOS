/******************************************************************************
Filename    : portASM.s
Author      : hrs
Date        : 05/09/2024
Description : The assembly part of the RVM/FreeRTOS. This is for RV32 with
              physical memory access, hence RV32P.
******************************************************************************/

/* Define ********************************************************************/
#define store_x                         SW
#define load_x                          LW
#define portWORD_SIZE                   (4U)

/* Only the standard core registers are stored by default.  Any additional
registers must be saved by the portasmSAVE_ADDITIONAL_REGISTERS and
portasmRESTORE_ADDITIONAL_REGISTERS macros - which can be defined in a chip
specific version of freertos_risc_v_chip_specific_extensions.h.  See the notes
at the top of this file. */
#define portCONTEXT_SIZE                (30*portWORD_SIZE)
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
    LW                  x1,0(sp)            /* Note for starting the scheduler the exception return address is used as the function return address. */

    LW                  x6,3*portWORD_SIZE(sp)      /* t1 */
    LW                  x7,4*portWORD_SIZE(sp)      /* t2 */
    LW                  x8,5*portWORD_SIZE(sp)      /* s0/fp */
    LW                  x9,6*portWORD_SIZE(sp)      /* s1 */
    LW                  x10,7*portWORD_SIZE(sp)     /* a0 */
    LW                  x11,8*portWORD_SIZE(sp)     /* a1 */
    LW                  x12,9*portWORD_SIZE(sp)     /* a2 */
    LW                  x13,10*portWORD_SIZE(sp)    /* a3 */
    LW                  x14,11*portWORD_SIZE(sp)    /* a4 */
    LW                  x15,12*portWORD_SIZE(sp)    /* a5 */
    LW                  x16,13*portWORD_SIZE(sp)    /* a6 */
    LW                  x17,14*portWORD_SIZE(sp)    /* a7 */
    LW                  x18,15*portWORD_SIZE(sp)    /* s2 */
    LW                  x19,16*portWORD_SIZE(sp)    /* s3 */
    LW                  x20,17*portWORD_SIZE(sp)    /* s4 */
    LW                  x21,18*portWORD_SIZE(sp)    /* s5 */
    LW                  x22,19*portWORD_SIZE(sp)    /* s6 */
    LW                  x23,20*portWORD_SIZE(sp)    /* s7 */
    LW                  x24,21*portWORD_SIZE(sp)    /* s8 */
    LW                  x25,22*portWORD_SIZE(sp)    /* s9 */
    LW                  x26,23*portWORD_SIZE(sp)    /* s10 */
    LW                  x27,24*portWORD_SIZE(sp)    /* s11 */
    LW                  x28,25*portWORD_SIZE(sp)    /* t3 */
    LW                  x29,26*portWORD_SIZE(sp)    /* t4 */
    LW                  x30,27*portWORD_SIZE(sp)    /* t5 */
    LW                  x31,28*portWORD_SIZE(sp)    /* t6 */

    LW                  x5,29*portWORD_SIZE(sp)     /* Initial mstatus into x5 (t0) */
    ADDI                x5,x5, 0x08                 /* Set MIE bit so the first task starts with interrupts enabled - required as returns with ret not eret. */
    CALL                RVM_Hyp_Int_Ena
    LW                  x5,2*portWORD_SIZE(sp)      /* Initial x5 (t0) value. */

    ADDI                sp,sp,portCONTEXT_SIZE
    RET
    .endfunc
/* End Function:_RMP_Start ***************************************************/

/*
 * Unlike other ports pxPortInitialiseStack() is written in assembly code as it
 * needs access to the portasmADDITIONAL_CONTEXT_SIZE constant.  The prototype
 * for the function is as per the other ports:
 * StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters );
 *
 * As per the standard RISC-V ABI pxTopcOfStack is passed in in a0, pxCode in
 * a1, and pvParameters in a2.  The new top of stack is passed out in a0.
 *
 * RISC-V maps registers to ABI names as follows (X1 to X31 integer registers
 * for the 'I' profile, X1 to X15 for the 'E' profile, currently I assumed).
 *
 * Register        ABI Name    Description                        Saver
 * x0              zero        Hard-wired zero                    -
 * x1              ra          Return address                     Caller
 * x2              sp          Stack pointer                      Callee
 * x3              gp          Global pointer                     -
 * x4              tp          Thread pointer                     -
 * x5-7            t0-2        Temporaries                        Caller
 * x8              s0/fp       Saved register/Frame pointer       Callee
 * x9              s1          Saved register                     Callee
 * x10-11          a0-1        Function Arguments/return values   Caller
 * x12-17          a2-7        Function arguments                 Caller
 * x18-27          s2-11       Saved registers                    Callee
 * x28-31          t3-6        Temporaries                        Caller
 *
 * The RISC-V context is saved t FreeRTOS tasks in the following stack frame,
 * where the global and thread pointers are currently assumed to be constant so
 * are not saved:
 *
 * mstatus
 * x31
 * x30
 * x29
 * x28
 * x27
 * x26
 * x25
 * x24
 * x23
 * x22
 * x21
 * x20
 * x19
 * x18
 * x17
 * x16
 * x15
 * x14
 * x13
 * x12
 * x11
 * pvParameters
 * x9
 * x8
 * x7
 * x6
 * x5
 * portTASK_RETURN_ADDRESS
 * [chip specific registers go here]
 * pxCode
 */
.align 8
.func
pxPortInitialiseStack:
    ADDI                a0,a0,-portWORD_SIZE
    SW                  t0,0(a0)                    /* mstatus onto the stack. */
    ADDI                a0,a0,-(22*portWORD_SIZE)   /* Space for registers x11-x31. */
    SW                  a2,0(a0)                    /* Task parameters (pvParameters parameter) goes into register X10/a0 on the stack. */
    ADDI                a0,a0,-(6*portWORD_SIZE)    /* Space for registers x5-x9. */
    SW                  x0,0(a0)                    /* Return address onto the stack, could be portTASK_RETURN_ADDRESS */
    ADDI                a0,a0,-portWORD_SIZE
    SW                  a1,0(a0)                    /* mret value (pxCode parameter) onto the stack. */
    RET
    .endfunc
/* End Function:pxPortInitialiseStack ****************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/
