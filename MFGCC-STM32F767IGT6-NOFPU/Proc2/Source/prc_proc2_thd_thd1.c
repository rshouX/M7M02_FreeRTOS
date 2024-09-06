/******************************************************************************
Filename    : prc_proc2_thd_thd1.c
Author      : The RVM project generator.
Date        : 28/08/2024 11:01:18
License     : Unlicense; see COPYING for details.
Description : The user stub file for thread 'Thd1'.
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
void Thd_Thd1(rvm_ret_t Param);
/* End Private Function ******************************************************/

/* Begin Function:Thd_Thd1 ****************************************************
Description : The function body for thread.
Input       : rvm_ret_t Param - The parameter supplied by the OS.
Output      : None.
Return      : None.
******************************************************************************/
void Thd_Thd1(rvm_ret_t Param)
{
#define RVM_BENCHMARK_PRC_PROC2_THD_THD1
#include "Test/rvm_benchmark.h"
#undef RVM_BENCHMARK_PRC_PROC2_THD_THD1
}
/* End Function:Thd_Thd1 *****************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/


