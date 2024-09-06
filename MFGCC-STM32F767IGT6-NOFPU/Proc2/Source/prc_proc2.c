/******************************************************************************
Filename    : prc_proc2.c
Author      : The RVM project generator.
Date        : 28/08/2024 11:01:18
License     : Unlicense; see COPYING for details.
Description : The main user stub file.
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

/* Public Variable ***********************************************************/
RVM_EXTERN const rvm_ptr_t RVM_Desc[6];
/* End Public Variable *******************************************************/

/* Private Function **********************************************************/
RVM_EXTERN rvm_ret_t Thd_Thd1(rvm_ret_t Param);
RVM_EXTERN rvm_ret_t Thd_Thd2(rvm_ret_t Param);
RVM_EXTERN rvm_ret_t Inv_Inv1(rvm_ret_t Param);
RVM_EXTERN void _RVM_Stub(void);
/* End Private Function ******************************************************/

/* Begin Function:main ********************************************************
Description : The function body for thread.
Input       : None.
Output      : None.
Return      : rvm_ret_t - Should never return.
******************************************************************************/
rvm_ret_t main(void)
{
    /* Check header validity */
    RVM_ASSERT(RVM_Desc[0]==RVM_MAGIC_NATIVE);
    RVM_ASSERT(RVM_Desc[1]==4U);

    /* Call the first (highest-priority) thread */
    Thd_Thd1(1234U);
}
/* End Function:main *********************************************************/

/* Begin Function:RVM_Putchar *************************************************
Description : The character printing function for debugging.
Input       : char Char - The character to print to console.
Output      : None.
Return      : None.
******************************************************************************/
#if(RVM_DBGLOG_ENABLE!=0U)
void RVM_Putchar(char Char)
{
#define RVM_TEST_PROCESS_PUTCHAR
#include "rvm_test.h"
#undef RVM_TEST_PROCESS_PUTCHAR
}
#endif
/* End Function:RVM_Putchar **************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/

