/******************************************************************************
Filename    : rme_platform_stm32l071cb.ld
Author      : The RVM project generator.
Date        : 29/08/2024 19:59:28
Licence     : Unlicense; see COPYING for details.
Description : The GCC linker script. This file is intended
              to be used with STM32L071CB, and the GNU toolchain.
******************************************************************************/

/* Memory ********************************************************************/
MEMORY
{
    /* Statically allocated kernel data segment */
    KDATA (rw) : ORIGIN = 0x20000000 , LENGTH = 0x240
    /* Dynamically allocated kernel data segment */
    KMEM (rw) : ORIGIN = 0x20000240 , LENGTH = 0x1180
    /* Kernel stack segment */
    KSTK (rw) : ORIGIN = 0x200013C0 , LENGTH = 0x400

    /* Kernel code segment */
    KCODE (rx) : ORIGIN = 0x8000000 , LENGTH = 0xE000
    /* Monitor code segment */
    MCODE (rx) : ORIGIN = 0x800E000 , LENGTH = 0xE000
    /* Proc1 code segment */
    PROC1_CODE (rx) : ORIGIN = 0x801E000 , LENGTH = 0x800
    /* Proc2 code segment */
    PROC2_CODE (rx) : ORIGIN = 0x801E800 , LENGTH = 0x800
    /* Virt1 code segment */
    VIRT1_CODE (rx) : ORIGIN = 0x8016000 , LENGTH = 0x8000
}
/* End Memory ****************************************************************/

/* Stack *********************************************************************/
__RME_Stack = ORIGIN(KSTK) + LENGTH(KSTK);
/* End Stack Definitions *****************************************************/

/* Entry *********************************************************************/
ENTRY(__RME_Entry);
/* End Entry *****************************************************************/

/* Process *******************************************************************/
SECTIONS
{
/* Monitor image */
.MONITOR_CODE : ALIGN(4)
{
    KEEP(*monitor_image.o(.text .text.*))
    KEEP(*monitor_image.o(.rodata .rodata.* .constdata .constdata.*))
} > MCODE

/* Process image */
.PROC1_CODE : ALIGN(4)
{
    KEEP(*proc1_image.o(.text .text.*))
    KEEP(*proc1_image.o(.rodata .rodata.* .constdata .constdata.*))
} > PROC1_CODE

/* Process image */
.PROC2_CODE : ALIGN(4)
{
    KEEP(*proc2_image.o(.text .text.*))
    KEEP(*proc2_image.o(.rodata .rodata.* .constdata .constdata.*))
} > PROC2_CODE

/* Process image */
.VIRT1_CODE : ALIGN(4)
{
    KEEP(*virt1_image.o(.text .text.*))
    KEEP(*virt1_image.o(.rodata .rodata.* .constdata .constdata.*))
} > VIRT1_CODE
/* End Process ***************************************************************/

/* Kernel ********************************************************************/
/* Kernel code segment */
.KERNEL_CODE : ALIGN(4)
{
    __RME_Code_Start = .;
    KEEP(*_gcc.o(.text.rme_vector))
    *(.text .text.*)
    *(.srodata .srodata.* .sconstdata .sconstdata.*)
    *(.rodata .rodata.* .constdata .constdata.*)
    __RME_Code_End = .;
} > KCODE

/* Statically allocated kernel data segment */
__RME_Data_Load = LOADADDR(.KERNEL_DATA);
.KERNEL_DATA : ALIGN(4)
{
    FILL(0xFF)
    __RME_Data_Start = .;
    __RME_Global = . + 0x800;
    *(.sdata_begin .sdata_begin.*)
    *(.sdata .sdata.*)
    *(.sdata2.*)
    *(.sdata_end .sdata_end.*)
    *(.data_begin .data_begin.*)
    *(.data .data.*)
    *(.data_end .data_end.*)
    . = ALIGN(4);
    __RME_Data_End = .;
} > KDATA AT > KCODE

/* Statically allocated kernel bss segment */
.KERNEL_ZERO (NOLOAD) : ALIGN(4)
{
    __RME_Zero_Start = .;
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
    __RME_Zero_End = .;
} > KDATA

/* Statically allocated kernel noinit segment */
.KERNEL_NOINIT (NOLOAD) : ALIGN(4)
{
    __RME_Noinit_Start = .;
    *(.snoinit .snoinit.*)
    *(.noinit .noinit.*)
    . = ALIGN(4);
    __RME_Noinit_End = .;
} > KDATA

/* Compatibility symbols for various architectures */
PROVIDE(__stack = __RME_Stack);
PROVIDE(__initial_sp = __RME_Stack);
PROVIDE(__initial_sp$ = __RME_Stack);
PROVIDE(__global_pointer = __RME_Global);
PROVIDE(__global_pointer$ = __RME_Global);
PROVIDE(__start = __RME_Entry);
PROVIDE(_stext = __RME_Code_Start);
PROVIDE(_etext = __RME_Code_End);
PROVIDE(_sidata = __RME_Data_Load);
PROVIDE(_sdata = __RME_Data_Start);
PROVIDE(_edata = __RME_Data_End);
PROVIDE(_sbss = __RME_Zero_Start);
PROVIDE(_ebss = __RME_Zero_End);
PROVIDE(_snoinit = __RME_Noinit_Start);
PROVIDE(_enoinit = __RME_Noinit_End);
PROVIDE(__text_start__ = __RME_Code_Start);
PROVIDE(__text_end__ = __RME_Code_End);
PROVIDE(__data_load__ = __RME_Data_Load);
PROVIDE(__data_start__ = __RME_Data_Start);
PROVIDE(__data_end__ = __RME_Data_End);
PROVIDE(__bss_start__ = __RME_Zero_Start);
PROVIDE(__bss_end__ = __RME_Zero_End);
PROVIDE(__noinit_start__ = __RME_Noinit_Start);
PROVIDE(__noinit_end__ = __RME_Noinit_End);
PROVIDE(end = __RME_Noinit_End);
PROVIDE(_end = __RME_Noinit_End);
PROVIDE(__end = __RME_Noinit_End);
PROVIDE(__end__ = __RME_Noinit_End);
/* End Section:.noinit *******************************************************/
}
/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/

