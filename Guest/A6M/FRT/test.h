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
/* Timestamp data type - STM32L0 timers are mixed, we treat them as 16-bits */
#define TEST_CNT_READ()         ((rvm_u16_t)(TIM2_CNT))
/* Memory pool test switch */
/* #define TEST_MEM_POOL */
/* Minimal build switch */
/* #define MINIMAL_SIZE */

/* Hardware definitions so we don't rely on STM32 HAL */
#define TIM2_BASE               (0x40000000U)
#define TIM21_BASE              (0x40010800U)
#define RCC_BASE                (0x40021000U)

#define RCC_APB1ENR             *((volatile rvm_u32_t*)(RCC_BASE+0x38U))
#define RCC_APB2ENR             *((volatile rvm_u32_t*)(RCC_BASE+0x34U))
#define RCC_APB1ENR_TIM2        (1U<<0)
#define RCC_APB2ENR_TIM21       (1U<<2)

#define TIM2_CR1                *((volatile rvm_u32_t*)(TIM2_BASE+0x00U))
#define TIM2_ARR                *((volatile rvm_u32_t*)(TIM2_BASE+0x2CU))
#define TIM2_PSC                *((volatile rvm_u32_t*)(TIM2_BASE+0x28U))
#define TIM2_CNT                *((volatile rvm_u32_t*)(TIM2_BASE+0x24U))

#define TIM21_CR1               *((volatile rvm_u32_t*)(TIM21_BASE+0x00U))
#define TIM21_ARR               *((volatile rvm_u32_t*)(TIM21_BASE+0x2CU))
#define TIM21_PSC               *((volatile rvm_u32_t*)(TIM21_BASE+0x28U))
#define TIM21_DIER              *((volatile rvm_u32_t*)(TIM21_BASE+0x0CU))
#define TIM21_SR                *((volatile rvm_u32_t*)(TIM21_BASE+0x10U))
    
#define TIM_CR1_CEN             (1U<<0)
#define TIM_COUNTERMODE_UP      (0U)
#define TIM_COUNTERMODE_DOWN    (1U<<4)
#define TIM_CLOCKDIVISION_DIV1  (0U)
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
    /* TIM2 clock = CPU clock */
    TIM2_CR1=TIM_COUNTERMODE_UP|TIM_CLOCKDIVISION_DIV1;
    TIM2_ARR=(unsigned int)(-1);
    TIM2_PSC=0U;
    RCC_APB1ENR|=RCC_APB1ENR_TIM2;
    TIM2_CR1|=TIM_CR1_CEN;
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
    RVM_ASSERT(RVM_Hyp_Vct_Phys(20U,2U)==0U);
    /* Set the priority of the physical interrupt and enable it */
    RVM_ASSERT(RVM_A6M_Int_Local_Mod(KFN_INT_LOCAL_MOD,20U,
                                     RVM_A6M_KFN_INT_LOCAL_MOD_PRIO_SET,0xFFU)==0);
    RVM_ASSERT(RVM_A6M_Int_Local_Mod(KFN_INT_LOCAL_MOD,20U,
                                     RVM_A6M_KFN_INT_LOCAL_MOD_STATE_SET,1U)==0);
    /* Interrupt generation is initialized too, here we only register our handler */
    RVM_Virt_Vct_Reg(2U,Int_Handler);
    
    /* TIM21 clock = CPU clock */
    TIM21_CR1=TIM_COUNTERMODE_DOWN|TIM_CLOCKDIVISION_DIV1;
    TIM21_ARR=3600U*4U;
    TIM21_PSC=0U;
    RCC_APB2ENR|=RCC_APB2ENR_TIM21;
    TIM21_SR&=~0x01U;
    TIM21_DIER|=0x01U;
    TIM21_CR1|=TIM_CR1_CEN;
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
    RVM_ASSERT(RVM_A6M_Int_Local_Mod(KFN_INT_LOCAL_MOD,20U, 
                                     RVM_A6M_KFN_INT_LOCAL_MOD_STATE_SET,0U)==0);
    /* Reverse registration */
    RVM_Virt_Vct_Reg(2U,RVM_NULL);
}
/* End Function:Int_Disable **************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/
