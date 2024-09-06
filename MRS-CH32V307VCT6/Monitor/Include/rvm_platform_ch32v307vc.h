/******************************************************************************
Filename   : rvm_platform_ch32v307vc.h
Author     : pry
Date       : 26/06/2017
Licence    : The Unlicense; see LICENSE for details.
Description: The configuration file for CH32V307VC. The values listed here should
             be in accordance with that in the kernel.
******************************************************************************/

/* Define ********************************************************************/
/* Debugging *****************************************************************/
#define RVM_ASSERT_ENABLE                               (1U)
#define RVM_DBGLOG_ENABLE                               (1U)
/* Kernel configurations - align with the kernel *****************************/
/* Are we using raw memory mappings? */
#define RVM_PGT_RAW_ENABLE                              (1U)
/* Kernel object virtual memory base */
#define RVM_KOM_VA_BASE                                 (0x20001500U)
/* Kernel object virtual memory size */
#define RVM_KOM_VA_SIZE                                 (0x1280U)
/* Kernel memory allocation granularity order */
#define RVM_KOM_SLOT_ORDER                              (4U)
/* The maximum number of preemption priorities */
#define RVM_PREEMPT_PRIO_NUM                            (32U)
/* The maximum number of VM preemption priorities */
#define RVM_PREEMPT_VPRIO_NUM                           (32U)

/* Physical vector number, flag area base and size */
#define RVM_PHYS_VCT_NUM                                (110U)
#define RVM_PHYS_VCTF_BASE                              (0x20002FC0U)
#define RVM_PHYS_VCTF_SIZE                              (0x40U)
/* Virtual event number, flag area base and size */
#define RVM_VIRT_EVT_NUM                                (32U)
#define RVM_VIRT_EVTF_BASE                              (0x20002FA0U)
#define RVM_VIRT_EVTF_SIZE                              (0x20U)
/* Maximum number of mappings allowed */
#define RVM_VIRT_MAP_NUM                                (32U)

/* Size of initial capability table */
#define RVM_INIT_CPT_SIZE                               (52U)
/* Initial kernel object frontier limit */
#define RVM_CPT_BOOT_FRONT                              (7U)
#define RVM_KOM_BOOT_FRONT                              (0x6F0U)
/* Post-boot kernel object frontier limit */
#define RVM_CPT_DONE_FRONT                              (16U)
#define RVM_KOM_DONE_FRONT                              (0x1280U)

/* Init process's first thread's entry point address */
#define RVM_RV32P_INIT_ENTRY                            (0x8000U)
/* Init process's first thread's stack address */
#define RVM_RV32P_INIT_STACK                            (0x20006FF0U)
/* Number of MPU regions available */
#define RVM_RV32P_REGION_NUM                            (3U)
/* What is the FPU type? */
#define RVM_COP_NUM                                     (1U)
#define RVM_RV32P_COP_RVF                               (1U)
#define RVM_RV32P_COP_RVD                               (0U)

/* Syslib configurations *****************************************************/
/* Stack redundancy */
#define RVM_STACK_SAFE_RDCY                             (16U)
/* Daemon process stack address and size, in bytes */
#define RVM_SFTD_STACK_BASE                             (0x20006400U)
#define RVM_SFTD_STACK_SIZE                             (0x400U)
#define RVM_VMMD_STACK_BASE                             (0x20005C00U)
#define RVM_VMMD_STACK_SIZE                             (0x800U)

#define RVM_RV32P_USART1_STATR                          RVM_RV32P_REG(0x40013800U)
#define RVM_RV32P_USART1_STATR_TC                       (0x00000040U)
#define RVM_RV32P_USART1_DATAR                          RVM_RV32P_REG(0x40013804U)

#if(RVM_DBGLOG_ENABLE==1U)
/* Print characters to console */
#define RVM_RV32P_PUTCHAR(CHAR) \
do \
{ \
    while((RVM_RV32P_USART1_STATR&RVM_RV32P_USART1_STATR_TC)==0U); \
    RVM_RV32P_USART1_DATAR=(rvm_ptr_t)(CHAR); \
} \
while(0)
#endif
/* End Define ****************************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/

