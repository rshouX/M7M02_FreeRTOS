/******************************************************************************
Filename    : prc_proc2.c
Author      : The RVM project generator.
Date        : 16/08/2024 22:18:31
License     : Unlicense; see COPYING for details.
Description : The main user stub file.
******************************************************************************/

/* Include *******************************************************************/
#include "rvm.h"
#include "rvm_guest.h"
/* End Include ***************************************************************/

/* Public Variable ***********************************************************/
RVM_EXTERN const rvm_ptr_t RVM_Desc[5];
/* End Public Variable *******************************************************/

/* Private Function **********************************************************/
RVM_EXTERN rvm_ret_t Thd_Thd1(rvm_ret_t Param);
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
    RVM_ASSERT(RVM_Desc[1]==3U);

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
    /* Add your own code */
}
#endif
/* End Function:RVM_Putchar **************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/

