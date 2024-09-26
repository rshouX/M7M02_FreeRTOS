/******************************************************************************
Filename    : prc_virt1.c
Author      : The RVM project generator.
Date        : 26/09/2024 10:23:15
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
rvm_ret_t Thd_Vct(rvm_ret_t Param);
RVM_EXTERN void _RVM_Stub(void);
/* End Private Function ******************************************************/

/* Begin Function:Thd_Vct *****************************************************
Description : The function body for vector handler.
Input       : rvm_ret_t Param - The parameter supplied by the OS.
Output      : None.
Return      : rvm_ret_t - Should never return.
******************************************************************************/
rvm_ret_t Thd_Vct(rvm_ret_t Param)
{
    /* Check header validity on boot */
    RVM_ASSERT(RVM_Desc[0]==RVM_MAGIC_VIRTUAL);
    RVM_ASSERT(RVM_Desc[1]==3U);

    /* DO NOT MODIFY - THIS HIGH PRIORITY THREAD CAN RUN ON UNINITIALIZED RAM */
    RVM_Virt_Init();
    RVM_Vct_Loop();

    return 0;
}
/* End Function:Thd_Vct ******************************************************/

/* Begin Function:RVM_Putchar *************************************************
Description : The character printing function for debugging.
Input       : char Char - The character to print to console.
Output      : None.
Return      : None.
******************************************************************************/
#if(RVM_DBGLOG_ENABLE!=0U)
void RVM_Putchar(char Char)
{
    RVM_Hyp_Putchar(Char);
}
#endif
/* End Function:RVM_Putchar **************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/

