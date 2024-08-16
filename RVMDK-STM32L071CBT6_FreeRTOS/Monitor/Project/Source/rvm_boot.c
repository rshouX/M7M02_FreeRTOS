/******************************************************************************
Filename    : rvm_boot.c
Author      : The RVM project generator.
Date        : 08/08/2024 16:25:18
License     : Unlicense; see COPYING for details.
Description : The boot-time initialization file.
******************************************************************************/

/* Include *******************************************************************/
#include "rvm.h"
#include "rvm_boot.h"

#define __HDR_DEF__
#include "Platform/A6M/rvm_platform_a6m.h"
#include "Monitor/rvm_monitor.h"
#undef __HDR_DEF__

#define __HDR_STRUCT__
#include "Platform/A6M/rvm_platform_a6m.h"
#include "Monitor/rvm_monitor.h"
#undef __HDR_STRUCT__

#define __HDR_PUBLIC__
#include "Platform/A6M/rvm_platform_a6m.h"
#include "Monitor/rvm_monitor.h"
#undef __HDR_PUBLIC__
/* End Include ***************************************************************/

/* Public Variable ***********************************************************/
/* Virtual machine management metadata */
struct RVM_Virt_Struct RVM_Virt[RVM_VIRT_NUM];
const struct RVM_Vmap_Struct RVM_Vmap[RVM_VIRT_NUM]=
{
{(rvm_s8_t*)"Virt1", 5U, 10U, 100U, 0U, 4U, 
 (struct RVM_Thd_Reg*)0x20003390U, (struct RVM_State*)0x200033C0U,
 0x40U, 0x8016000U, RVM_CID(RVM_MAIN_VEP_0, 0U),
 RVM_THD_VCT_PRC_VIRT1, 0x20003600U, 0x200U,
 RVM_THD_USR_PRC_VIRT1, 0x20003400U, 0x200U},
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
{RVM_MAIN_CPT_0, 0, 4U},
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

/* Page table metadata */
const struct RVM_Meta_Main_Struct RVM_Meta_Pgt_Main[RVM_BOOT_INIT_PGT_MAIN_NUM]=
{
{RVM_MAIN_PGT_0, 11U},
};
const struct RVM_Meta_Pgt_Crt_Struct RVM_Meta_Pgt_Crt[RVM_BOOT_INIT_PGT_CRT_NUM]=
{
{RVM_MAIN_PGT_0, 0, 0x0U, 1U, 27U, 3U},
{RVM_MAIN_PGT_0, 1, 0x801E000U, 0U, 11U, 0U},
{RVM_MAIN_PGT_0, 2, 0x20003800U, 0U, 11U, 0U},
{RVM_MAIN_PGT_0, 3, 0x0U, 1U, 27U, 3U},
{RVM_MAIN_PGT_0, 4, 0x801E800U, 0U, 11U, 0U},
{RVM_MAIN_PGT_0, 5, 0x20000000U, 0U, 12U, 3U},
{RVM_MAIN_PGT_0, 6, 0x20003800U, 0U, 10U, 0U},
{RVM_MAIN_PGT_0, 7, 0x20004000U, 0U, 10U, 0U},
{RVM_MAIN_PGT_0, 8, 0x0U, 1U, 28U, 3U},
{RVM_MAIN_PGT_0, 9, 0x8010000U, 0U, 13U, 3U},
{RVM_MAIN_PGT_0, 10, 0x20002000U, 0U, 10U, 3U},
};
const struct RVM_Meta_Pgt_Con_Struct RVM_Meta_Pgt_Con[RVM_BOOT_INIT_PGT_CON_NUM]=
{
{RVM_PGT_PROC1_0, RVM_PGT_PROC1_1, 0x1U},
{RVM_PGT_PROC1_0, RVM_PGT_PROC1_2, 0x4U},
{RVM_PGT_PROC2_0, RVM_PGT_PROC2_1, 0x1U},
{RVM_PGT_PROC2_0, RVM_PGT_PROC2_2, 0x4U},
{RVM_PGT_PROC2_2, RVM_PGT_PROC2_3, 0x3U},
{RVM_PGT_PROC2_2, RVM_PGT_PROC2_4, 0x4U},
{RVM_PGT_VIRT1_0, RVM_PGT_VIRT1_1, 0x0U},
{RVM_PGT_VIRT1_0, RVM_PGT_VIRT1_2, 0x2U},
};
const struct RVM_Meta_Pgt_Add_Struct RVM_Meta_Pgt_Add[RVM_BOOT_INIT_PGT_ADD_NUM]=
{
{RVM_PGT_PROC1_1, 0x0U,
 RVM_PGT_READ|RVM_PGT_EXECUTE|RVM_PGT_CACHE|RVM_PGT_BUFFER|RVM_PGT_STATIC,
 0x0U, 0x1003CU},
{RVM_PGT_PROC1_2, 0x0U,
 RVM_PGT_READ|RVM_PGT_WRITE|RVM_PGT_CACHE|RVM_PGT_BUFFER|RVM_PGT_STATIC,
 0x0U, 0x40007U},
{RVM_PGT_PROC2_1, 0x0U,
 RVM_PGT_READ|RVM_PGT_EXECUTE|RVM_PGT_CACHE|RVM_PGT_BUFFER|RVM_PGT_STATIC,
 0x0U, 0x1003DU},
{RVM_PGT_PROC2_3, 0x0U,
 RVM_PGT_READ|RVM_PGT_WRITE|RVM_PGT_CACHE|RVM_PGT_BUFFER|RVM_PGT_STATIC,
 0x0U, 0x8000EU},
{RVM_PGT_PROC2_4, 0x0U,
 RVM_PGT_READ|RVM_PGT_WRITE|RVM_PGT_CACHE|RVM_PGT_BUFFER|RVM_PGT_STATIC,
 0x0U, 0x80010U},
{RVM_PGT_VIRT1_0, 0x4U,
 RVM_PGT_READ|RVM_PGT_WRITE|RVM_PGT_STATIC,
 0x0U, 0x4U},
{RVM_PGT_VIRT1_0, 0x5U,
 RVM_PGT_READ|RVM_PGT_WRITE|RVM_PGT_STATIC,
 0x0U, 0x5U},
{RVM_PGT_VIRT1_1, 0x3U,
 RVM_PGT_READ|RVM_PGT_EXECUTE|RVM_PGT_CACHE|RVM_PGT_BUFFER|RVM_PGT_STATIC,
 0x0U, 0x400BU},
{RVM_PGT_VIRT1_1, 0x4U,
 RVM_PGT_READ|RVM_PGT_EXECUTE|RVM_PGT_CACHE|RVM_PGT_BUFFER|RVM_PGT_STATIC,
 0x0U, 0x400CU},
{RVM_PGT_VIRT1_1, 0x5U,
 RVM_PGT_READ|RVM_PGT_EXECUTE|RVM_PGT_CACHE|RVM_PGT_BUFFER|RVM_PGT_STATIC,
 0x0U, 0x400DU},
{RVM_PGT_VIRT1_1, 0x6U,
 RVM_PGT_READ|RVM_PGT_EXECUTE|RVM_PGT_CACHE|RVM_PGT_BUFFER|RVM_PGT_STATIC,
 0x0U, 0x400EU},
{RVM_PGT_VIRT1_2, 0x2U,
 RVM_PGT_READ|RVM_PGT_WRITE|RVM_PGT_CACHE|RVM_PGT_BUFFER|RVM_PGT_STATIC,
 0x0U, 0x8000AU},
{RVM_PGT_VIRT1_2, 0x3U,
 RVM_PGT_READ|RVM_PGT_WRITE|RVM_PGT_CACHE|RVM_PGT_BUFFER|RVM_PGT_STATIC,
 0x0U, 0x8000BU},
{RVM_PGT_VIRT1_2, 0x4U,
 RVM_PGT_READ|RVM_PGT_WRITE|RVM_PGT_CACHE|RVM_PGT_BUFFER|RVM_PGT_STATIC,
 0x0U, 0x8000CU},
{RVM_PGT_VIRT1_2, 0x5U,
 RVM_PGT_READ|RVM_PGT_WRITE|RVM_PGT_CACHE|RVM_PGT_BUFFER|RVM_PGT_STATIC,
 0x0U, 0x8000DU},
{RVM_PGT_VIRT1_2, 0x6U,
 RVM_PGT_READ|RVM_PGT_WRITE|RVM_PGT_CACHE|RVM_PGT_BUFFER|RVM_PGT_STATIC,
 0x0U, 0x8000EU},
};

/* Process metadata */
const struct RVM_Meta_Main_Struct RVM_Meta_Prc_Main[RVM_BOOT_PRC_MAIN_NUM]=
{
{RVM_MAIN_PRC_0, 3U},
};
const struct RVM_Meta_Prc_Crt_Struct RVM_Meta_Prc_Crt[RVM_BOOT_PRC_CRT_NUM]=
{
{RVM_MAIN_PRC_0, 0, RVM_CPT_PROC1, RVM_PGT_PROC1_0},
{RVM_MAIN_PRC_0, 1, RVM_CPT_PROC2, RVM_PGT_PROC2_0},
{RVM_MAIN_PRC_0, 2, RVM_CPT_VIRT1, RVM_PGT_VIRT1_0},
};

/* Thread metadata */
const struct RVM_Meta_Main_Struct RVM_Meta_Thd_Main[RVM_BOOT_THD_MAIN_NUM]=
{
{RVM_MAIN_THD_0, 4U},
};
const struct RVM_Meta_Thd_Crt_Struct RVM_Meta_Thd_Crt[RVM_BOOT_THD_CRT_NUM]=
{
{RVM_MAIN_THD_0, 0, RVM_PRC_PROC1, 17U, RVM_A6M_ATTR_NONE, 0U},
{RVM_MAIN_THD_0, 1, RVM_PRC_PROC2, 16U, RVM_A6M_ATTR_NONE, 0U},
{RVM_MAIN_THD_0, 2, RVM_PRC_VIRT1, 3U, RVM_A6M_ATTR_NONE, 0U},
{RVM_MAIN_THD_0, 3, RVM_PRC_VIRT1, 2U, RVM_A6M_ATTR_NONE, 1U},
};
const struct RVM_Meta_Thd_Init_Struct RVM_Meta_Thd_Init[RVM_BOOT_THD_INIT_NUM]=
{
{RVM_THD_THD1_PRC_PROC1, 0U, 0x801E000U, 0U, 0x20003E00U, 0x200U, 0x1234U, 17U, 0U},
{RVM_THD_THD1_PRC_PROC2, 0U, 0x801E800U, 0U, 0x20004200U, 0x200U, 0x1234U, 16U, 0U},
{RVM_THD_VCT_PRC_VIRT1, RVM_VIRT_TID_FLAG, 0x8016000U, 0U, 0x20003600U, 0x200U, 0x0U, 3U, 0U},
{RVM_THD_USR_PRC_VIRT1, RVM_VIRT_TID_FLAG, 0x8016000U, 1U, 0x20003400U, 0x200U, 0x0U, 2U, 0x20003390U},
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
{RVM_INV_INV1_PRC_PROC1, 0x801E000U, 1U, 0x20003D00U, 0x100U},
{RVM_INV_INV1_PRC_PROC2, 0x801E800U, 1U, 0x20004100U, 0x100U},
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

