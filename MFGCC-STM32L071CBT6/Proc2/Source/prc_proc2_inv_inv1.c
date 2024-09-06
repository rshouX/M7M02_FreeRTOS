/******************************************************************************
Filename    : prc_proc2_inv_inv1.c
Author      : The RVM project generator.
Date        : 05/09/2024 21:43:15
License     : Unlicense; see COPYING for details.
Description : The user stub file for thread 'Inv1'.
******************************************************************************/

/* Include *******************************************************************/
#include "rvm.h"
#include "rvm_guest.h"

#define RVM_TEST_PROCESS_INC
#include "rvm_test.h"
#undef RVM_TEST_PROCESS_INC

#define RVM_BENCHMARK_PROCESS_INC
#include "Test/rvm_benchmark.h"
#undef RVM_BENCHMARK_PROCESS_INC
/* End Include ***************************************************************/

/* Private Function **********************************************************/
void Inv_Inv1(rvm_ret_t Param);
/* End Private Function ******************************************************/

/* Begin Function:Inv_Inv1 ****************************************************
Description : The function body for invocation.
Input       : rvm_ret_t Param - The parameter supplied by the caller.
Output      : None.
Return      : None.
******************************************************************************/
void Inv_Inv1(rvm_ret_t Param)
{
#define RVM_BENCHMARK_PRC_PROC2_INV_INV1
#include "Test/rvm_benchmark.h"
#undef RVM_BENCHMARK_PRC_PROC2_INV_INV1
}
/* End Function:Inv_Inv1 *****************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/
