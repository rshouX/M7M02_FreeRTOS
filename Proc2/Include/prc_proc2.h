/******************************************************************************
Filename    : prc_proc2.h
Author      : The RVM project generator.
Date        : 15/07/2024 19:11:05
License     : Unlicense; see COPYING for details.
Description : The user kernel object header.
******************************************************************************/

/* Define ********************************************************************/
#ifndef __PRC_PROC2__
#define __PRC_PROC2__

/* Process capability table frontier & size */
#define CPT_SIZE                                        (4U)
#define CPT_FRONT                                       (4U)

/* Ports */
#define PRT_INV1_PRC_PROC1                              (1U)

/* Receive endpoints */
#define RCV_RECV1                                       (2U)

/* Send endpoints */
#define SND_RECV1_PRC_PROC1                             (3U)

/* Vector endpoints */

/* Kernel functions */

/* Code memory blocks */
#define CODE_P2_CODE_BASE                               (0x8040000U)
#define CODE_P2_CODE_SIZE                               (0x10000U)

/* Data memory blocks */
#define DATA_P2_DATA_BASE                               (0x20030000U)
#define DATA_P2_DATA_SIZE                               (0x10000U)
#define DATA_SHARED_S_DATA_BASE                         (0x20050000U)
#define DATA_SHARED_S_DATA_SIZE                         (0x400U)

/* Device memory blocks */

/* Total priority number */
#define RVM_PREEMPT_PRIO_NUM                            (32U)
/* Total VM priority number */
#define RVM_PREEMPT_VPRIO_NUM                           (32U)
/* The kernel memory allocation granularity order */
#define RVM_KOM_SLOT_ORDER                              (4U)

/* Virtual machine library disable */
#define RVM_VIRT_LIB_ENABLE                             (0U)

/* Debugging settings */
#define RVM_ASSERT_ENABLE                               (1U)
#define RVM_DBGLOG_ENABLE                               (1U)

/* Coprocessor options */
#define RVM_COP_NUM                                     (1U)
#define RVM_A7M_COP_FPV4_SP                             (0U)
#define RVM_A7M_COP_FPV5_SP                             (0U)
#define RVM_A7M_COP_FPV5_DP                             (1U)
#endif /* __PRC_PROC2__ */
/* End Define ****************************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/


