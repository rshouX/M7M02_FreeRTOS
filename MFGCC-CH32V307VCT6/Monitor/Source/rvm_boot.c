/******************************************************************************
Filename    : rvm_boot.c
Author      : The RVM project generator.
Date        : 30/07/2024 23:59:31
License     : Unlicense; see COPYING for details.
Description : The boot-time initialization file.
******************************************************************************/

/* Include *******************************************************************/
#include "rvm.h"
#include "rvm_boot.h"

#define __HDR_DEF__
#include "Platform/RV32P/rvm_platform_rv32p.h"
#include "Monitor/rvm_monitor.h"
#undef __HDR_DEF__

#define __HDR_STRUCT__
#include "Platform/RV32P/rvm_platform_rv32p.h"
#include "Monitor/rvm_monitor.h"
#undef __HDR_STRUCT__

#define __HDR_PUBLIC__
#include "Platform/RV32P/rvm_platform_rv32p.h"
#include "Monitor/rvm_monitor.h"
#undef __HDR_PUBLIC__
/* End Include ***************************************************************/

/* Public Variable ***********************************************************/
/* Virtual machine management metadata */
struct RVM_Virt_Struct RVM_Virt[RVM_VIRT_NUM];
const struct RVM_Vmap_Struct RVM_Vmap[RVM_VIRT_NUM]=
{
{(rvm_s8_t*)"Virt1", 5U, 10U, 100U, 0U, 100U, 
 (struct RVM_Thd_Reg*)0x2000F640U, (struct RVM_State*)0x2000F760U,
 0xA0U, 0x20000U, RVM_CID(RVM_MAIN_VEP_0, 0U),
 RVM_THD_VCT_PRC_VIRT1, 0x2000FC00U, 0x400U,
 RVM_THD_USR_PRC_VIRT1, 0x2000F800U, 0x400U},
};

/* Virtual endpoint metadata */
const struct RVM_Meta_Main_Struct RVM_Meta_Vep_Main[RVM_BOOT_VEP_MAIN_NUM]=
{
{RVM_MAIN_VEP_0, 1U},
};
const struct RVM_Meta_Rcv_Crt_Struct RVM_Meta_Vep_Crt[RVM_BOOT_VEP_CRT_NUM]=
{
{RVM_MAIN_VEP_0, 0U},
};
const struct RVM_Meta_Vcap_Init_Struct RVM_Meta_Vcap_Init[RVM_BOOT_VCAP_INIT_NUM]=
{
{RVM_CPT_VIRT1, RVM_MAIN_VEP_0, 0U},
};

/* Capability table metadata */
const struct RVM_Meta_Main_Struct RVM_Meta_Cpt_Main[RVM_BOOT_INIT_CPT_MAIN_NUM]=
{
{RVM_MAIN_CPT_0, 3U},
};
const struct RVM_Meta_Cpt_Crt_Struct RVM_Meta_Cpt_Crt[RVM_BOOT_INIT_CPT_CRT_NUM]=
{
{RVM_MAIN_CPT_0, 0, 13U},
{RVM_MAIN_CPT_0, 1, 4U},
{RVM_MAIN_CPT_0, 2, 5U},
};
const struct RVM_Meta_Cpt_Init_Struct RVM_Meta_Cpt_Init[RVM_BOOT_INIT_CPT_INIT_NUM]=
{
{RVM_CPT_PROC1, 1U, RVM_MAIN_INV_0, 1U, RVM_INV_FLAG_ACT},
{RVM_CPT_PROC1, 2U, RVM_MAIN_RCV_0, 0U, RVM_SIG_FLAG_SND|RVM_SIG_FLAG_RCV},
{RVM_CPT_PROC1, 3U, RVM_MAIN_RCV_0, 1U, RVM_SIG_FLAG_SND},
{RVM_CPT_PROC2, 1U, RVM_MAIN_INV_0, 0U, RVM_INV_FLAG_ACT},
{RVM_CPT_PROC2, 2U, RVM_MAIN_RCV_0, 1U, RVM_SIG_FLAG_SND|RVM_SIG_FLAG_RCV},
{RVM_CPT_PROC2, 3U, RVM_MAIN_RCV_0, 0U, RVM_SIG_FLAG_SND},
{RVM_CPT_VIRT1, 2U, RVM_MAIN_RCV_0, 0U, RVM_SIG_FLAG_SND},
{RVM_CPT_VIRT1, 3U, RVM_MAIN_RCV_0, 1U, RVM_SIG_FLAG_SND},
};
const struct RVM_Meta_Cpt_Kfn_Struct RVM_Meta_Cpt_Kfn[RVM_BOOT_INIT_CPT_KFN_NUM]=
{
{RVM_CPT_PROC1, 0U, RVM_KFN_EVT_LOCAL_TRIG, RVM_KFN_EVT_LOCAL_TRIG},
{RVM_CPT_PROC2, 0U, RVM_KFN_EVT_LOCAL_TRIG, RVM_KFN_EVT_LOCAL_TRIG},
{RVM_CPT_VIRT1, 4U, 0xF100U, 0xF100U},
};

/* Process page table raw data */
const rvm_ptr_t RVM_Meta_Raw_Proc1[5U]=
{
    0x181B1F1DU,
    0x47FFU,
    0x8001DFFU,
    0x800447FU,
    0xFFFFFFFFU,
};
const rvm_ptr_t RVM_Meta_Raw_Proc2[5U]=
{
    0x181B1F1DU,
    0x57FFU,
    0x80041FFU,
    0x800447FU,
    0xFFFFFFFFU,
};
const rvm_ptr_t RVM_Meta_Raw_Virt1[5U]=
{
    0x181B1F1DU,
    0x9FFFU,
    0x8002FFFU,
    0x13FFFFFFU,
    0xFFFFFFFFU,
};

/* Process metadata */
const struct RVM_Meta_Main_Struct RVM_Meta_Prc_Main[RVM_BOOT_PRC_MAIN_NUM]=
{
{RVM_MAIN_PRC_0, 3U},
};
const struct RVM_Meta_Prc_Crt_Struct RVM_Meta_Prc_Crt[RVM_BOOT_PRC_CRT_NUM]=
{
{RVM_MAIN_PRC_0, 0, RVM_CPT_PROC1, (rvm_ptr_t)RVM_Meta_Raw_Proc1},
{RVM_MAIN_PRC_0, 1, RVM_CPT_PROC2, (rvm_ptr_t)RVM_Meta_Raw_Proc2},
{RVM_MAIN_PRC_0, 2, RVM_CPT_VIRT1, (rvm_ptr_t)RVM_Meta_Raw_Virt1},
};

/* Thread metadata */
const struct RVM_Meta_Main_Struct RVM_Meta_Thd_Main[RVM_BOOT_THD_MAIN_NUM]=
{
{RVM_MAIN_THD_0, 4U},
};
const struct RVM_Meta_Thd_Crt_Struct RVM_Meta_Thd_Crt[RVM_BOOT_THD_CRT_NUM]=
{
{RVM_MAIN_THD_0, 0, RVM_PRC_PROC1, 17U, RVM_RV32P_ATTR_RVF, 0U},
{RVM_MAIN_THD_0, 1, RVM_PRC_PROC2, 16U, RVM_RV32P_ATTR_RVF, 0U},
{RVM_MAIN_THD_0, 2, RVM_PRC_VIRT1, 3U, RVM_RV32P_ATTR_RVF, 0U},
{RVM_MAIN_THD_0, 3, RVM_PRC_VIRT1, 2U, RVM_RV32P_ATTR_RVF, 1U},
};
const struct RVM_Meta_Thd_Init_Struct RVM_Meta_Thd_Init[RVM_BOOT_THD_INIT_NUM]=
{
{RVM_THD_THD1_PRC_PROC1, 0U, 0x10000U, 0U, 0x20007E00U, 0x200U, 0x1234U, 17U, 0U},
{RVM_THD_THD1_PRC_PROC2, 0U, 0x14000U, 0U, 0x20010E00U, 0x200U, 0x1234U, 16U, 0U},
{RVM_THD_VCT_PRC_VIRT1, RVM_VIRT_TID_FLAG, 0x20000U, 0U, 0x2000FC00U, 0x400U, 0x0U, 3U, 0U},
{RVM_THD_USR_PRC_VIRT1, RVM_VIRT_TID_FLAG, 0x20000U, 1U, 0x2000F800U, 0x400U, 0x0U, 2U, 0x2000F640U},
};

/* Invocation metadata */
const struct RVM_Meta_Main_Struct RVM_Meta_Inv_Main[RVM_BOOT_INV_MAIN_NUM]=
{
{RVM_MAIN_INV_0, 2U},
};
const struct RVM_Meta_Inv_Crt_Struct RVM_Meta_Inv_Crt[RVM_BOOT_INV_CRT_NUM]=
{
{RVM_MAIN_INV_0, 0, RVM_PRC_PROC1},
{RVM_MAIN_INV_0, 1, RVM_PRC_PROC2},
};
const struct RVM_Meta_Inv_Init_Struct RVM_Meta_Inv_Init[RVM_BOOT_INV_INIT_NUM]=
{
{RVM_INV_INV1_PRC_PROC1, 0x10000U, 1U, 0x20007C00U, 0x200U},
{RVM_INV_INV1_PRC_PROC2, 0x14000U, 1U, 0x20010C00U, 0x200U},
};

/* Receive endpoint metadata */
const struct RVM_Meta_Main_Struct RVM_Meta_Rcv_Main[RVM_BOOT_RCV_MAIN_NUM]=
{
{RVM_MAIN_RCV_0, 2U},
};
const struct RVM_Meta_Rcv_Crt_Struct RVM_Meta_Rcv_Crt[RVM_BOOT_RCV_CRT_NUM]=
{
{RVM_MAIN_RCV_0, 0},
{RVM_MAIN_RCV_0, 1},
};

/* End Public Variable *******************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/

