/******************************************************************************
Filename    : test.h
Author      : hrs 
Date        : 14/07/2024
Licence     : The Unlicense; see LICENSE for details.
Description : FreeRTOS init functions.
******************************************************************************/

/* Include *******************************************************************/
#include "rvm_guest.h"
/* End Include ***************************************************************/

/* Define ********************************************************************/
/* Counter read wrapper */
#define TEST_CNT_READ()         (TIM1_CNT)
/* Memory pool test switch */
#define TEST_MEM_POOL           (4096U)
/* Minimal build switch */
/* #define MINIMAL_SIZE */

/* Hardware definitions so we don't rely on WCH HAL */
#define TIM1_BASE               (0x40012C00U)
#define TIM4_BASE               (0x40000800U)
#define RCC_BASE                (0x40021000U)

#define RCC_APB2PCENR           *((volatile rvm_u32_t*)(RCC_BASE+0x18U))
#define RCC_APB2PCENR_TIM1      (1U<<11)

#define RCC_APB1PCENR           *((volatile rvm_u32_t*)(RCC_BASE+0x1CU))
#define RCC_APB1PCENR_TIM4      (1U<<2)

#define TIM1_CTLR1              *((volatile rvm_u16_t*)(TIM1_BASE+0x00U))
#define TIM1_SMCFGR             *((volatile rvm_u16_t*)(TIM1_BASE+0x08U))
#define TIM1_CNT                *((volatile rvm_u16_t*)(TIM1_BASE+0x24U))

#define TIM4_CTLR1              *((volatile rvm_u16_t*)(TIM4_BASE+0x00U))
#define TIM4_ATRLR              *((volatile rvm_u16_t*)(TIM4_BASE+0x2CU))
#define TIM4_PSC                *((volatile rvm_u16_t*)(TIM4_BASE+0x28U))
#define TIM4_DMAINTENR          *((volatile rvm_u16_t*)(TIM4_BASE+0x0CU))
#define TIM4_INTFR              *((volatile rvm_u16_t*)(TIM4_BASE+0x10U))
    
#define TIM_CTLR1_CEN           (1U<<0)
#define TIM_COUNTERMODE_UP      (0U)
#define TIM_COUNTERMODE_DOWN    (1U<<4)
#define TIM_CKD_DIV1            (0U)
#define TIM_IT_UPDATE           (1U<<0)
/* End Define ****************************************************************/

/* Global ********************************************************************/
void Timer_Init(void);
void Int_Init(void);
void Int_Handler(void);
void Int_Disable(void);
/* End Global ****************************************************************/

/* Function:Timer_Init ********************************************************
Description : Initialize the timer for timing measurements. This function needs
              to be adapted to your specific hardware.
Input       : None.
Output      : None.
Return      : None.
******************************************************************************/
void Timer_Init(void)
{
    /* TIM1 clock = CPU clock */
    RCC_APB2PCENR|=RCC_APB2PCENR_TIM1;
    TIM1_CTLR1=TIM_COUNTERMODE_UP;
    TIM1_SMCFGR=0U;
    TIM1_CTLR1|=TIM_CTLR1_CEN;
}
/* End Function:Timer_Init ***************************************************/

/* Function:Int_Init **********************************************************
Description : Initialize an periodic interrupt source. This function needs
              to be adapted to your specific hardware.
Input       : None.
Output      : None.
Return      : None.
******************************************************************************/
void Int_Init(void)
{
    /* Connect the physical interrupt to our machine */
    RVM_ASSERT(RVM_Hyp_Vct_Phys(46U,2U)==0U);
    /* Set the priority of the physical interrupt and enable it */
    RVM_ASSERT(RVM_RV32P_Int_Local_Mod(KFN_INT_LOCAL_MOD,46U,
                                       RVM_RV32P_KFN_INT_LOCAL_MOD_STATE_SET,1U)==0);
    RVM_ASSERT(RVM_RV32P_Int_Local_Mod(KFN_INT_LOCAL_MOD,46U,
                                       RVM_RV32P_KFN_INT_LOCAL_MOD_PRIO_SET,0xFFU)==0);
    /* Interrupt generation is initialized too, here we only register our handler */
    RVM_Virt_Vct_Reg(2U,Int_Handler);
    
    /* TIM4 clock = CPU clock */
    RCC_APB1PCENR|=RCC_APB1PCENR_TIM4;
    
    TIM4_PSC=0U;
    TIM4_ATRLR=14400U*4U;
    TIM4_CTLR1=TIM_COUNTERMODE_DOWN|TIM_CKD_DIV1;
    TIM4_INTFR=0U;
    TIM4_DMAINTENR=TIM_IT_UPDATE;
    TIM4_CTLR1|=TIM_CTLR1_CEN;
}
/* End Function:Int_Init *****************************************************/

/* Function:Int_Disable *******************************************************
Description : Disable the periodic interrupt source. This function needs
              to be adapted to your specific hardware.
Input       : None.
Output      : None.
Return      : None.
******************************************************************************/
void Int_Disable(void)
{
    /* Disable interrupt */
    RVM_ASSERT(RVM_RV32P_Int_Local_Mod(KFN_INT_LOCAL_MOD,46U,
                                       RVM_RV32P_KFN_INT_LOCAL_MOD_STATE_SET,0U)==0);
    /* Reverse registration */
    RVM_Virt_Vct_Reg(2U,RVM_NULL);
}
/* End Function:Int_Disable **************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/
