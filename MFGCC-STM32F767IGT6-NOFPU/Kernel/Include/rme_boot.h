/******************************************************************************
Filename    : rme_boot.h
Author      : The RVM project generator.
Date        : 05/09/2024 21:43:00
License     : Unlicense; see COPYING for details.
Description : The boot-time initialization file header.
******************************************************************************/

/* Define ********************************************************************/
/* Capability table maximum capacity */
#define RME_MAIN_CPT_SIZE                               (128U)
/* Boot-time capability table */
#define RME_BOOT_CPT_OBJ                                (RME_A7M_CPT)

/* Vector endpoint capability tables */
#define RME_MAIN_VCT_0                                  (7U)

/* Vector endpoints */
#define RVM_VCT_TIM4                                    (0U)

/* Receive endpoint capability tables - created by RVM later */
#define RME_BOOT_SIG_0                                  (17U)

/* Receive endpoints - created by RVM later */
#define RME_RCV_RECV1_PRC_PROC1                         (RME_CID(RME_BOOT_SIG_0,0U))
#define RME_RCV_RECV2_PRC_PROC1                         (RME_CID(RME_BOOT_SIG_0,1U))
#define RME_RCV_RECV1_PRC_PROC2                         (RME_CID(RME_BOOT_SIG_0,2U))
#define RME_RCV_RECV2_PRC_PROC2                         (RME_CID(RME_BOOT_SIG_0,3U))

/* Code memory blocks */
#define RME_PROC1_CODE_CODE1_BASE                       (0x8030000U)
#define RME_PROC1_CODE_CODE1_SIZE                       (0x10000U)
#define RME_PROC2_CODE_CODE1_BASE                       (0x8040000U)
#define RME_PROC2_CODE_CODE1_SIZE                       (0x10000U)
#define RME_VIRT1_CODE_CODE1_BASE                       (0x8050000U)
#define RME_VIRT1_CODE_CODE1_SIZE                       (0x10000U)

/* Data memory blocks */
#define RME_PROC1_DATA_DATA1_BASE                       (0x20020000U)
#define RME_PROC1_DATA_DATA1_SIZE                       (0x10000U)
#define RME_PROC2_DATA_DATA1_BASE                       (0x20030000U)
#define RME_PROC2_DATA_DATA1_SIZE                       (0x10000U)
#define RME_VIRT1_DATA_DATA1_BASE                       (0x20040000U)
#define RME_VIRT1_DATA_DATA1_SIZE                       (0x10000U)
#define RME_DATA_SHARED_SHARED1_BASE                    (0x20050000U)
#define RME_DATA_SHARED_SHARED1_SIZE                    (0x400U)

/* Device memory blocks */
#define RME_DEVICE_SHARED_DEVICE1_BASE                  (0x40000000U)
#define RME_DEVICE_SHARED_DEVICE1_SIZE                  (0x20000000U)
/* End Define ****************************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/

