/******************************************************************************
Filename    : rvm_boot.h
Author      : The RVM project generator.
Date        : 08/08/2024 16:25:32
License     : Unlicense; see COPYING for details.
Description : The boot-time initialization file header.
******************************************************************************/

/* Define ********************************************************************/
/* Vector endpoint capability tables */

/* Vector endpoints */

/* 2 threads and 1 endpoint for RVM */

/* Virtual machine endpoint capability tables */
#define RVM_MAIN_VEP_0                                  (10U)

/* Process capability table capability tables */
#define RVM_MAIN_CPT_0                                  (11U)

/* Process capability tables */
#define RVM_CPT_PROC1                                   (RVM_CID(RVM_MAIN_CPT_0, 0U))
#define RVM_CPT_PROC2                                   (RVM_CID(RVM_MAIN_CPT_0, 1U))
#define RVM_CPT_VIRT1                                   (RVM_CID(RVM_MAIN_CPT_0, 2U))

/* Process page table capability tables */
#define RVM_MAIN_PGT_0                                  (12U)

/* Process page tables */
#define RVM_PGT_PROC1_0                                 (RVM_CID(RVM_MAIN_PGT_0, 0U))
#define RVM_PGT_PROC1_1                                 (RVM_CID(RVM_MAIN_PGT_0, 1U))
#define RVM_PGT_PROC1_2                                 (RVM_CID(RVM_MAIN_PGT_0, 2U))
#define RVM_PGT_PROC1_3                                 (RVM_CID(RVM_MAIN_PGT_0, 3U))
#define RVM_PGT_PROC2_0                                 (RVM_CID(RVM_MAIN_PGT_0, 4U))
#define RVM_PGT_PROC2_1                                 (RVM_CID(RVM_MAIN_PGT_0, 5U))
#define RVM_PGT_PROC2_2                                 (RVM_CID(RVM_MAIN_PGT_0, 6U))
#define RVM_PGT_PROC2_3                                 (RVM_CID(RVM_MAIN_PGT_0, 7U))
#define RVM_PGT_VIRT1_0                                 (RVM_CID(RVM_MAIN_PGT_0, 8U))
#define RVM_PGT_VIRT1_1                                 (RVM_CID(RVM_MAIN_PGT_0, 9U))
#define RVM_PGT_VIRT1_2                                 (RVM_CID(RVM_MAIN_PGT_0, 10U))
#define RVM_PGT_VIRT1_3                                 (RVM_CID(RVM_MAIN_PGT_0, 11U))

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
#define RVM_THD_THD1_PRC_PROC2                          (RVM_CID(RVM_MAIN_THD_0, 1U))
#define RVM_THD_VCT_PRC_VIRT1                           (RVM_CID(RVM_MAIN_THD_0, 2U))
#define RVM_THD_USR_PRC_VIRT1                           (RVM_CID(RVM_MAIN_THD_0, 3U))

/* Invocation capability tables */
#define RVM_MAIN_INV_0                                  (15U)

/* Invocations */
#define RVM_INV_INV1_PRC_PROC1                          (RVM_CID(RVM_MAIN_INV_0, 0U))
#define RVM_INV_INV1_PRC_PROC2                          (RVM_CID(RVM_MAIN_INV_0, 1U))

/* Receive endpoint capability tables */
#define RVM_MAIN_RCV_0                                  (16U)

/* Receive endpoints */
#define RVM_RCV_RECV1_PRC_PROC1                         (RVM_CID(RVM_MAIN_RCV_0, 0U))
#define RVM_RCV_RECV1_PRC_PROC2                         (RVM_CID(RVM_MAIN_RCV_0, 1U))

/* VM number */
#define RVM_VIRT_NUM                                    (1U)

/* Virtual endpoint frontiers & number */
#define RVM_BOOT_VEP_BEFORE                             (0x830U)
#define RVM_BOOT_VEP_AFTER                              (0x850U)
#define RVM_BOOT_VEP_MAIN_NUM                           (1U)
#define RVM_BOOT_VEP_CRT_NUM                            (1U)
#define RVM_BOOT_VCAP_INIT_NUM                          (1U)

/* Cpt frontiers & number */
#define RVM_BOOT_INIT_CPT_BEFORE                        (0x850U)
#define RVM_BOOT_INIT_CPT_AFTER                         (0xB70U)
#define RVM_BOOT_INIT_CPT_MAIN_NUM                      (1U)
#define RVM_BOOT_INIT_CPT_CRT_NUM                       (3U)
#define RVM_BOOT_INIT_CPT_INIT_NUM                      (8U)
#define RVM_BOOT_INIT_CPT_KFN_NUM                       (3U)

/* Pgt frontiers & number */
#define RVM_BOOT_INIT_PGT_BEFORE                        (0xB70U)
#define RVM_BOOT_INIT_PGT_AFTER                         (0xFC0U)
#define RVM_BOOT_INIT_PGT_MAIN_NUM                      (1U)
#define RVM_BOOT_INIT_PGT_CRT_NUM                       (12U)
#define RVM_BOOT_INIT_PGT_CON_NUM                       (9U)
#define RVM_BOOT_INIT_PGT_ADD_NUM                       (14U)

/* Process frontiers & number */
#define RVM_BOOT_PRC_BEFORE                             (0xFC0U)
#define RVM_BOOT_PRC_AFTER                              (0x1020U)
#define RVM_BOOT_PRC_MAIN_NUM                           (1U)
#define RVM_BOOT_PRC_CRT_NUM                            (3U)

/* Thread frontiers & number */
#define RVM_BOOT_THD_BEFORE                             (0x1020U)
#define RVM_BOOT_THD_AFTER                              (0x1370U)
#define RVM_BOOT_THD_MAIN_NUM                           (1U)
#define RVM_BOOT_THD_CRT_NUM                            (4U)
#define RVM_BOOT_THD_INIT_NUM                           (4U)

/* Invocation frontiers & number */
#define RVM_BOOT_INV_BEFORE                             (0x1370U)
#define RVM_BOOT_INV_AFTER                              (0x1410U)
#define RVM_BOOT_INV_MAIN_NUM                           (1U)
#define RVM_BOOT_INV_CRT_NUM                            (2U)
#define RVM_BOOT_INV_INIT_NUM                           (2U)

/* Receive endpoint frontiers & number */
#define RVM_BOOT_RCV_BEFORE                             (0x1410U)
#define RVM_BOOT_RCV_AFTER                              (0x1450U)
#define RVM_BOOT_RCV_MAIN_NUM                           (1U)
#define RVM_BOOT_RCV_CRT_NUM                            (2U)

/* End Define ****************************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/

