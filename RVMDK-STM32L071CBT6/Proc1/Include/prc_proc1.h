/******************************************************************************
Filename    : prc_proc1.h
Author      : The RVM project generator.
Date        : 26/09/2024 10:23:18
License     : Unlicense; see COPYING for details.
Description : The user kernel object header.
******************************************************************************/

/* Define ********************************************************************/
#ifndef __PRC_PROC1__
#define __PRC_PROC1__

/* Process capability table frontier & size */
#define CPT_SIZE                                        (10U)
#define CPT_FRONT                                       (10U)

/* Ports */
#define PRT_INV1_PRC_PROC2                              (1U)

/* Receive endpoints */
#define RCV_RECV1                                       (2U)
#define RCV_RECV2                                       (3U)

/* Send endpoints */
#define SND_RECV1_PRC_PROC1                             (4U)
#define SND_RECV2_PRC_PROC1                             (5U)
#define SND_RECV1_PRC_PROC2                             (6U)
#define SND_RECV2_PRC_PROC2                             (7U)

/* Vector endpoints */
#define VCT_TIM21                                       (8U)

/* Kernel functions */
#define KFN_INT_LOCAL_MOD                               (9U)

/* Code memory blocks */
#define CODE_CODE1_BASE                                 (0x8016000U)
#define CODE_CODE1_SIZE                                 (0x1000U)

/* Data memory blocks */
#define DATA_DATA1_BASE                                 (0x20002800U)
#define DATA_DATA1_SIZE                                 (0x800U)
#define DATA_SHARED_SHARED1_BASE                        (0x20004800U)
#define DATA_SHARED_SHARED1_SIZE                        (0x100U)

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
#endif /* __PRC_PROC1__ */
/* End Define ****************************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/


