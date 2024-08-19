/******************************************************************************
Filename    : prc_virt1.h
Author      : The RVM project generator.
Date        : 30/07/2024 23:59:31
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
#define CODE_MAIN_CODE_BASE                             (0x20000U)
#define CODE_MAIN_CODE_SIZE                             (0x10000U)

/* Data memory blocks */
#define DATA_MAIN_DATA_BASE                             (0x20008000U)
#define DATA_MAIN_DATA_SIZE                             (0x8000U)

/* Device memory blocks */
#define DEVICE_MAIN_DEVICE_BASE                         (0x40000000U)
#define DEVICE_MAIN_DEVICE_SIZE                         (0x20000000U)

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
#define RVM_VIRT_STATE_BASE                             (0x2000F760U)
#define RVM_VIRT_STATE_SIZE                             (0xA0U)
/* Virtual register base address & size */
#define RVM_VIRT_REG_BASE                               (0x2000F640U)
#define RVM_VIRT_REG_SIZE                               (0x120U)

/* Debugging settings */
#define RVM_ASSERT_ENABLE                               (1U)
#define RVM_DBGLOG_ENABLE                               (1U)

/* Coprocessor options */
#define RVM_COP_NUM                                     (1U)
#define RVM_RV32P_COP_RVF                               (1U)
#define RVM_RV32P_COP_RVD                               (0U)
#endif /* __PRC_VIRT1__ */
/* End Define ****************************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/


