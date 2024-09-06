/******************************************************************************
Filename    : rvm_boot.h
Author      : The RVM project generator.
Date        : 05/09/2024 21:42:52
License     : Unlicense; see COPYING for details.
Description : The boot-time initialization file header.
******************************************************************************/

/* Define ********************************************************************/
/* Vector endpoint capability tables */
#define RVM_MAIN_VCT_0                                  (7U)

/* Vector endpoints */
#define RVM_VCT_TIM4                                    (RVM_CID(RVM_MAIN_VCT_0, 0U))

/* 2 threads and 1 endpoint for RVM */

/* Virtual machine endpoint capability tables */
#define RVM_MAIN_VEP_0                                  (11U)

/* Process capability table capability tables */
#define RVM_MAIN_CPT_0                                  (12U)

/* Process capability tables */
#define RVM_CPT_PROC1                                   (RVM_CID(RVM_MAIN_CPT_0, 0U))
#define RVM_CPT_PROC2                                   (RVM_CID(RVM_MAIN_CPT_0, 1U))
#define RVM_CPT_VIRT1                                   (RVM_CID(RVM_MAIN_CPT_0, 2U))

/* Process capability tables */
#define RVM_MAIN_PRC_0                                  (13U)

/* Processes */
#define RVM_PRC_PROC1                                   (RVM_CID(RVM_MAIN_PRC_0, 0U))
#define RVM_PRC_PROC2                                   (RVM_CID(RVM_MAIN_PRC_0, 1U))
#define RVM_PRC_VIRT1                                   (RVM_CID(RVM_MAIN_PRC_0, 2U))

/* Thread capability tables */
#define RVM_MAIN_THD_0                                  (14U)

/* Threads */
#define RVM_THD_THD1_PRC_PROC1                          (RVM_CID(RVM_MAIN_THD_0, 0U))
#define RVM_THD_THD2_PRC_PROC1                          (RVM_CID(RVM_MAIN_THD_0, 1U))
#define RVM_THD_THD1_PRC_PROC2                          (RVM_CID(RVM_MAIN_THD_0, 2U))
#define RVM_THD_THD2_PRC_PROC2                          (RVM_CID(RVM_MAIN_THD_0, 3U))
#define RVM_THD_VCT_PRC_VIRT1                           (RVM_CID(RVM_MAIN_THD_0, 4U))
#define RVM_THD_USR_PRC_VIRT1                           (RVM_CID(RVM_MAIN_THD_0, 5U))

/* Invocation capability tables */
#define RVM_MAIN_INV_0                                  (15U)

/* Invocations */
#define RVM_INV_INV1_PRC_PROC2                          (RVM_CID(RVM_MAIN_INV_0, 0U))

/* Receive endpoint capability tables */
#define RVM_MAIN_RCV_0                                  (16U)

/* Receive endpoints */
#define RVM_RCV_RECV1_PRC_PROC1                         (RVM_CID(RVM_MAIN_RCV_0, 0U))
#define RVM_RCV_RECV2_PRC_PROC1                         (RVM_CID(RVM_MAIN_RCV_0, 1U))
#define RVM_RCV_RECV1_PRC_PROC2                         (RVM_CID(RVM_MAIN_RCV_0, 2U))
#define RVM_RCV_RECV2_PRC_PROC2                         (RVM_CID(RVM_MAIN_RCV_0, 3U))

/* VM number */
#define RVM_VIRT_NUM                                    (1U)

/* Virtual endpoint frontiers & number */
#define RVM_BOOT_VEP_BEFORE                             (0x510U)
#define RVM_BOOT_VEP_AFTER                              (0x530U)
#define RVM_BOOT_VEP_MAIN_NUM                           (1U)
#define RVM_BOOT_VEP_CRT_NUM                            (1U)
#define RVM_BOOT_VCAP_INIT_NUM                          (1U)

/* Cpt frontiers & number */
#define RVM_BOOT_INIT_CPT_BEFORE                        (0x530U)
#define RVM_BOOT_INIT_CPT_AFTER                         (0x850U)
#define RVM_BOOT_INIT_CPT_MAIN_NUM                      (1U)
#define RVM_BOOT_INIT_CPT_CRT_NUM                       (3U)
#define RVM_BOOT_INIT_CPT_INIT_NUM                      (16U)
#define RVM_BOOT_INIT_CPT_KFN_NUM                       (4U)

/* Pgt frontiers & number */
/* Process frontiers & number */
#define RVM_BOOT_PRC_BEFORE                             (0x850U)
#define RVM_BOOT_PRC_AFTER                              (0x8B0U)
#define RVM_BOOT_PRC_MAIN_NUM                           (1U)
#define RVM_BOOT_PRC_CRT_NUM                            (3U)

/* Thread frontiers & number */
#define RVM_BOOT_THD_BEFORE                             (0x8B0U)
#define RVM_BOOT_THD_AFTER                              (0xE80U)
#define RVM_BOOT_THD_MAIN_NUM                           (1U)
#define RVM_BOOT_THD_CRT_NUM                            (6U)
#define RVM_BOOT_THD_INIT_NUM                           (6U)

/* Invocation frontiers & number */
#define RVM_BOOT_INV_BEFORE                             (0xE80U)
#define RVM_BOOT_INV_AFTER                              (0xED0U)
#define RVM_BOOT_INV_MAIN_NUM                           (1U)
#define RVM_BOOT_INV_CRT_NUM                            (1U)
#define RVM_BOOT_INV_INIT_NUM                           (1U)

/* Receive endpoint frontiers & number */
#define RVM_BOOT_RCV_BEFORE                             (0xED0U)
#define RVM_BOOT_RCV_AFTER                              (0xF50U)
#define RVM_BOOT_RCV_MAIN_NUM                           (1U)
#define RVM_BOOT_RCV_CRT_NUM                            (4U)

/* Code memory blocks */
#define RVM_PROC1_CODE_CODE1_BASE                       (0x20000U)
#define RVM_PROC1_CODE_CODE1_SIZE                       (0x4000U)
#define RVM_PROC2_CODE_CODE1_BASE                       (0x24000U)
#define RVM_PROC2_CODE_CODE1_SIZE                       (0x4000U)
#define RVM_VIRT1_CODE_CODE1_BASE                       (0x10000U)
#define RVM_VIRT1_CODE_CODE1_SIZE                       (0x10000U)

/* Data memory blocks */
#define RVM_PROC1_DATA_DATA1_BASE                       (0x20007000U)
#define RVM_PROC1_DATA_DATA1_SIZE                       (0x1000U)
#define RVM_PROC2_DATA_DATA1_BASE                       (0x20010000U)
#define RVM_PROC2_DATA_DATA1_SIZE                       (0x1000U)
#define RVM_VIRT1_DATA_DATA1_BASE                       (0x20008000U)
#define RVM_VIRT1_DATA_DATA1_SIZE                       (0x8000U)

/* Device memory blocks */
#define RVM_DEVICE_SHARED_DEVICE1_BASE                  (0x40000000U)
#define RVM_DEVICE_SHARED_DEVICE1_SIZE                  (0x20000000U)
/* End Define ****************************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/

