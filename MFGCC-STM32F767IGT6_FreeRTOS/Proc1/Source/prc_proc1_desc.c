/******************************************************************************
Filename    : prc_proc1_desc.c
Author      : The RVM project generator.
Date        : 08/08/2024 16:25:32
License     : Unlicense; see COPYING for details.
Description : The process descriptor header file - do not edit!
              When using LTO, make sure this file is exempt from the LTO option,
              so that it be firmly linked to the head of the image!
******************************************************************************/

/* Include *******************************************************************/
#include "rvm.h"
#include "rvm_guest.h"
/* End Include ***************************************************************/

/* Public Function ***********************************************************/
RVM_EXTERN rvm_ret_t Inv_Inv1(rvm_ret_t Param);
/* End Public Function *******************************************************/

/* Public Variable ***********************************************************/
const rvm_ptr_t RVM_Desc[5]=
{
    0x49535953U,
    0x3U,
    (rvm_ptr_t)_RVM_Entry,
    (rvm_ptr_t)Inv_Inv1,
    (rvm_ptr_t)_RVM_Stub,
};
/* End Public Variable *******************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/

