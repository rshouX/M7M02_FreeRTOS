/******************************************************************************
Filename    : prc_virt1.h
Author      : The RVM project generator.
Date        : 08/08/2024 16:25:25
License     : Unlicense; see COPYING for details.
Description : The user kernel object header.
******************************************************************************/

/* Define ********************************************************************/
#ifndef __PRC_VIRT1__
#define __PRC_VIRT1__

/* Process capability table frontier & size */
#define CPT_SIZE                                        (5U)
#define CPT_FRONT                                       (5U)

/* Ports */

/* Receive endpoints */

/* Send endpoints */
#define SND_RECV1_PRC_PROC1                             (2U)
#define SND_RECV1_PRC_PROC2                             (3U)

/* Vector endpoints */

/* Kernel functions */
#define KFN_INT_LOCAL_MOD                               (4U)

/* Code memory blocks */
#define CODE_V_CODE_BASE                                (0x8028000U)
#define CODE_V_CODE_SIZE                                (0x10000U)

/* Data memory blocks */
#define DATA_V_DATA_BASE                                (0x2000A000U)
#define DATA_V_DATA_SIZE                                (0x10000U)
#define DATA_SHARED_S_DATA_BASE                         (0x10007000U)
#define DATA_SHARED_S_DATA_SIZE                         (0x400U)

/* Device memory blocks */
#define DEVICE_V_DEVICE_BASE                            (0x40000000U)
#define DEVICE_V_DEVICE_SIZE                            (0x20000000U)

/* Total priority number */
#define RVM_PREEMPT_PRIO_NUM                            (32U)
/* Total VM priority number */
#define RVM_PREEMPT_VPRIO_NUM                           (32U)
/* The kernel memory allocation granularity order */
#define RVM_KOM_SLOT_ORDER                              (4U)

/* Virtual machine library enable */
#define RVM_VIRT_LIB_ENABLE                             (1U)
/* Virtual vector total number */
#define RVM_VIRT_VCT_NUM                                (100U)
/* State block base address & size */
#define RVM_VIRT_STATE_BASE                             (0x20019760U)
#define RVM_VIRT_STATE_SIZE                             (0xA0U)
/* Virtual register base address & size */
#define RVM_VIRT_REG_BASE                               (0x200196F0U)
#define RVM_VIRT_REG_SIZE                               (0x70U)

/* Debugging settings */
#define RVM_ASSERT_ENABLE                               (1U)
#define RVM_DBGLOG_ENABLE                               (1U)

/* Coprocessor options */
#define RVM_COP_NUM                                     (1U)
#define RVM_A7M_COP_FPV4_SP                             (1U)
#define RVM_A7M_COP_FPV5_SP                             (0U)
#define RVM_A7M_COP_FPV5_DP                             (0U)
#endif /* __PRC_VIRT1__ */
/* End Define ****************************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/


