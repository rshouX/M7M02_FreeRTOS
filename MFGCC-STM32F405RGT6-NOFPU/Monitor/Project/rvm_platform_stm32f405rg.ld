/******************************************************************************
Filename    : rvm_platform_stm32f405rg.ld
Author      : The RVM project generator.
Date        : 26/09/2024 10:23:16
Licence     : Unlicense; see COPYING for details.
Description : The GCC linker script. This file is intended
              to be used with STM32F405RG, and the GNU toolchain.
******************************************************************************/

/* Memory ********************************************************************/
MEMORY
{
    /* Monitor RAM BASE and SIZE*/
    DATA (rw) : ORIGIN = 0x10003000 , LENGTH = 0x2E00
    /* Monitor Stack BASE and SIZE*/
    STK (rw) : ORIGIN = 0x10006E00 , LENGTH = 0x200
    /* Monitor flash segment */
    CODE (rx) : ORIGIN = 0x8010000 , LENGTH = 0x10000
}
/* End Memory ****************************************************************/

/* Stack *********************************************************************/
__RVM_Stack = ORIGIN(STK) + LENGTH(STK);
/* End Entry Point Definitions ***********************************************/

/* Entry *********************************************************************/
ENTRY(__RVM_Entry)
/* End Entry *****************************************************************/

/* Section *******************************************************************/
SECTIONS
{
/* Monitor code segment */
.MONITOR_CODE : ALIGN(4)
{
    __RVM_Code_Start = .;
    KEEP(*_gcc.o(.text.rvm_entry))
    *(.text .text.*)
    *(.srodata .srodata.* .sconstdata .sconstdata.*)
    *(.rodata .rodata.* .constdata .constdata.*)
    . = ALIGN(4);
    __RVM_Code_End = .;
} > CODE

/* Monitor data segment */
__RVM_Data_Load = LOADADDR(.MONITOR_DATA);
.MONITOR_DATA : ALIGN(4)
{
    FILL(0xFF)
    __RVM_Data_Start = .;
    __RVM_Global = . + 0x800;
    *(.sdata_begin .sdata_begin.*)
    *(.sdata .sdata.*)
    *(.sdata2.*)
    *(.sdata_end .sdata_end.*)
    *(.data_begin .data_begin.*)
    *(.data .data.*)
    *(.data_end .data_end.*)
    . = ALIGN(4);
    __RVM_Data_End = .;
  } > DATA AT > CODE

/* Monitor bss segment */
.MONITOR_ZERO : ALIGN(4)
{
    __RVM_Zero_Start = .;
    *(.sbss_begin .sbss_begin.*)
    *(.sbss .sbss.*)
    *(.sbss2.*)
    *(SCOMMON)
    *(.sbss_end .sbss_end.*)
    *(.bss_begin .bss_begin.*)
    *(.bss .bss.*)
    *(COMMON)
    *(.bss_end .bss_end.*)
    . = ALIGN(4);
    __RVM_Zero_End = .;
} > DATA

/* Monitor noinit segment */
.MONITOR_NOINIT (NOLOAD) : ALIGN(4)
{
    __RVM_Noinit_Start = .;
    *(.snoinit .snoinit.*)
    *(.noinit .noinit.*)
    . = ALIGN(4);
    __RVM_Noinit_End = .;
} > DATA
}

/* Compatibility symbols for various architectures */
PROVIDE(__stack = __RVM_Stack);
PROVIDE(__initial_sp = __RVM_Stack);
PROVIDE(__initial_sp$ = __RVM_Stack);
PROVIDE(__global_pointer = __RVM_Global);
PROVIDE(__global_pointer$ = __RVM_Global);
PROVIDE(__start = __RVM_Entry);
PROVIDE(_stext = __RVM_Code_Start);
PROVIDE(_etext = __RVM_Code_End);
PROVIDE(_sidata = __RVM_Data_Load);
PROVIDE(_sdata = __RVM_Data_Start);
PROVIDE(_edata = __RVM_Data_End);
PROVIDE(_sbss = __RVM_Zero_Start);
PROVIDE(_ebss = __RVM_Zero_End);
PROVIDE(_snoinit = __RVM_Noinit_Start);
PROVIDE(_enoinit = __RVM_Noinit_End);
PROVIDE(__text_start__ = __RVM_Code_Start);
PROVIDE(__text_end__ = __RVM_Code_End);
PROVIDE(__data_load__ = __RVM_Data_Load);
PROVIDE(__data_start__ = __RVM_Data_Start);
PROVIDE(__data_end__ = __RVM_Data_End);
PROVIDE(__bss_start__ = __RVM_Zero_Start);
PROVIDE(__bss_end__ = __RVM_Zero_End);
PROVIDE(__noinit_start__ = __RVM_Noinit_Start);
PROVIDE(__noinit_end__ = __RVM_Noinit_End);
PROVIDE(end = __RVM_Noinit_End);
PROVIDE(_end = __RVM_Noinit_End);
PROVIDE(__end = __RVM_Noinit_End);
PROVIDE(__end__ = __RVM_Noinit_End);
/* End Section ***************************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/

