/******************************************************************************
Filename    : prc_proc2.h
Author      : The RVM project generator.
Date        : 26/09/2024 10:23:17
License     : Unlicense; see COPYING for details.
Description : The user kernel object header.
******************************************************************************/

/* Define ********************************************************************/
#ifndef __PRC_PROC2__
#define __PRC_PROC2__

/* Process capability table frontier & size */
#define CPT_SIZE                                        (7U)
#define CPT_FRONT                                       (7U)

/* Ports */

/* Receive endpoints */
#define RCV_RECV1                                       (1U)
#define RCV_RECV2                                       (2U)

/* Send endpoints */
#define SND_RECV1_PRC_PROC1                             (3U)
#define SND_RECV2_PRC_PROC1                             (4U)
#define SND_RECV1_PRC_PROC2                             (5U)
#define SND_RECV2_PRC_PROC2                             (6U)

/* Vector endpoints */

/* Kernel functions */

/* Code memory blocks */
#define CODE_CODE1_BASE                                 (0x8040000U)
#define CODE_CODE1_SIZE                                 (0x10000U)

/* Data memory blocks */
#define DATA_DATA1_BASE                                 (0x20030000U)
#define DATA_DATA1_SIZE                                 (0x10000U)
#define DATA_SHARED_SHARED1_BASE                        (0x20050000U)
#define DATA_SHARED_SHARED1_SIZE                        (0x400U)

/* Device memory blocks */
#define DEVICE_SHARED_DEVICE1_BASE                      (0x40000000U)
#define DEVICE_SHARED_DEVICE1_SIZE                      (0x20000000U)

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
#define RVM_COP_NUM                                     (0U)
#define RVM_A7M_COP_FPV4_SP                             (0U)
#define RVM_A7M_COP_FPV5_SP                             (0U)
#define RVM_A7M_COP_FPV5_DP                             (0U)
#endif /* __PRC_PROC2__ */
/* End Define ****************************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/


