/******************************************************************************
Filename    : prc_proc1.h
Author      : The RVM project generator.
Date        : 08/08/2024 16:25:29
License     : Unlicense; see COPYING for details.
Description : The user kernel object header.
******************************************************************************/

/* Define ********************************************************************/
#ifndef __PRC_PROC1__
#define __PRC_PROC1__

/* Process capability table frontier & size */
#define CPT_SIZE                                        (13U)
#define CPT_FRONT                                       (4U)

/* Ports */
#define PRT_INV1_PRC_PROC2                              (1U)

/* Receive endpoints */
#define RCV_RECV1                                       (2U)

/* Send endpoints */
#define SND_RECV1_PRC_PROC2                             (3U)

/* Vector endpoints */

/* Kernel functions */

/* Code memory blocks */
#define CODE_P1_CODE_BASE                               (0x8020000U)
#define CODE_P1_CODE_SIZE                               (0x8000U)

/* Data memory blocks */
#define DATA_P1_DATA_BASE                               (0x20000000U)
#define DATA_P1_DATA_SIZE                               (0x9000U)
#define DATA_SHARED_S_DATA_BASE                         (0x10007000U)
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
#define RVM_A7M_COP_FPV4_SP                             (1U)
#define RVM_A7M_COP_FPV5_SP                             (0U)
#define RVM_A7M_COP_FPV5_DP                             (0U)
#endif /* __PRC_PROC1__ */
/* End Define ****************************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/


