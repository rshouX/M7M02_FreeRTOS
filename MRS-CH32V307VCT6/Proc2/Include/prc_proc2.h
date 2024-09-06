/******************************************************************************
Filename    : prc_proc2.h
Author      : The RVM project generator.
Date        : 30/07/2024 23:59:31
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
#define CODE_MAIN_CODE_BASE                             (0x14000U)
#define CODE_MAIN_CODE_SIZE                             (0x4000U)

/* Data memory blocks */
#define DATA_MAIN_DATA_BASE                             (0x20010000U)
#define DATA_MAIN_DATA_SIZE                             (0x1000U)
#define DATA_SHARED_SHARED1_BASE                        (0x20011000U)
#define DATA_SHARED_SHARED1_SIZE                        (0x400U)

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
#define RVM_RV32P_COP_RVF                               (1U)
#define RVM_RV32P_COP_RVD                               (0U)
#endif /* __PRC_PROC2__ */
/* End Define ****************************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/


