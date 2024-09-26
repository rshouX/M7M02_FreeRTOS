/******************************************************************************
Filename    : prc_proc1_thd_thd2.c
Author      : The RVM project generator.
Date        : 26/09/2024 10:23:17
License     : Unlicense; see COPYING for details.
Description : The user stub file for thread 'Thd2'.
******************************************************************************/

/* Include *******************************************************************/
#include "rvm.h"
#include "rvm_guest.h"

#define RVM_TEST_NATIVE_INC
#include "rvm_test.h"
#undef RVM_TEST_NATIVE_INC

#define RVM_BENCHMARK_NATIVE_INC
#include "Test/rvm_benchmark.h"
#undef RVM_BENCHMARK_NATIVE_INC
/* End Include ***************************************************************/

/* Private Function **********************************************************/
void Thd_Thd2(rvm_ret_t Param);
/* End Private Function ******************************************************/

/* Begin Function:Thd_Thd2 ****************************************************
Description : The function body for thread.
Input       : rvm_ret_t Param - The parameter supplied by the OS.
Output      : None.
Return      : None.
******************************************************************************/
void Thd_Thd2(rvm_ret_t Param)
{
#define RVM_BENCHMARK_PRC_PROC1_THD_THD2
#include "Test/rvm_benchmark.h"
#undef RVM_BENCHMARK_PRC_PROC1_THD_THD2
}
/* End Function:Thd_Thd2 *****************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/


