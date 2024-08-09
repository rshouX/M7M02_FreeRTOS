/******************************************************************************
Filename    : prc_proc1_thd_thd1.c
Author      : The RVM project generator.
Date        : 08/08/2024 16:25:20
License     : Unlicense; see COPYING for details.
Description : The user stub file for thread 'Thd1'.
******************************************************************************/

/* Include *******************************************************************/
#include "rvm.h"
#include "rvm_guest.h"
/* End Include ***************************************************************/

/* Private Function **********************************************************/
rvm_ret_t Thd_Thd1(rvm_ret_t Param);
/* End Private Function ******************************************************/

/* Begin Function:Thd_Thd1 ****************************************************
Description : The function body for thread.
Input       : rvm_ret_t Param - The parameter supplied by the OS.
Output      : None.
Return      : rvm_ret_t - Should never return.
******************************************************************************/
rvm_ret_t Thd_Thd1(rvm_ret_t Param)
{
    while(1) RVM_Sig_Rcv(RCV_RECV1,RVM_RCV_BM);
}
/* End Function:Thd_Thd1 *****************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/


