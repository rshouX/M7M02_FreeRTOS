/******************************************************************************
Filename    : proc_proc1_stm32f405rg.ld
Author      : The RVM project generator.
Date        : 08/08/2024 16:25:29
Licence     : Unlicense; see COPYING for details.
Description : The GCC linker script. This file is intended
              to be used with STM32F405RG, and the GNU toolchain.
******************************************************************************/

/* Memory ********************************************************************/
MEMORY
{
    /* Process data segment */
    DATA (rw) : ORIGIN = 0x20000000 , LENGTH = 0x7E00
    /* Process stack segment */
    STK (rw) : ORIGIN = 0x20008E00 , LENGTH = 0x200
    /* Process descriptor */
    DESC (r) : ORIGIN = 0x8020000 , LENGTH = 0x20
    /* Process code segment */
    CODE (rx) : ORIGIN = 0x8020020 , LENGTH = 0x7FE0
}
/* End Memory ****************************************************************/

/* Stack *********************************************************************/
_RVM_Stack = ORIGIN(STK) + LENGTH(STK);
/* End Entry Point Definitions ***********************************************/

/* Entry *********************************************************************/
ENTRY(_RVM_Entry)
/* End Entry *****************************************************************/

/* Section *******************************************************************/
SECTIONS
{
/* Process descriptor segment */
.PROCESS_DESC : ALIGN(4)
{
    KEEP(*prc_proc1_desc.o(.rodata .rodata.* .constdata .constdata.*))
} > DESC

/* Process code, srodata and rodata segment */
.PROCESS_CODE : ALIGN(4)
{
    _RVM_Code_Start = .;
    KEEP(*_gcc.o(.text.rvm_entry))
    *(.text .text.*)
    *(.srodata .srodata.* .sconstdata .sconstdata.*)
    *(.rodata .rodata.* .constdata .constdata.*)
    . = ALIGN(4);
    _RVM_Code_End = .;
} > CODE

/* Process sdata & data segment */
_RVM_Data_Load = LOADADDR(.PROCESS_DATA);
.PROCESS_DATA : ALIGN(4)
{
    FILL(0xFF)
    _RVM_Data_Start = .;
    _RVM_Global = . + 0x800;
    *(.sdata_begin .sdata_begin.*)
    *(.sdata .sdata.*)
    *(.sdata2.*)
    *(.sdata_end .sdata_end.*)
    *(.data_begin .data_begin.*)
    *(.data .data.*)
    *(.data_end .data_end.*)
    _RVM_Data_End = .;
    . = ALIGN(4);
  } > DATA AT > CODE

/* Process sbss & bss segment */
.PROCESS_ZERO : ALIGN(4)
{
    _RVM_Zero_Start = .;
    *(.sbss_begin .sbss_begin.*)
    *(.sbss .sbss.*)
    *(.sbss2.*)
    *(SCOMMON)
    *(.sbss_end .sbss_end.*)
    *(.bss_begin .bss_begin.*)
    *(.bss .bss.*)
    *(COMMON)
    *(.bss_end .bss_end.*)
    _RVM_Zero_End = .;
    . = ALIGN(4);
} > DATA

/* Process snoinit & noinit segment */
.PROCESS_NOINIT (NOLOAD) : ALIGN(4)
{
    _RVM_Noinit_Start = .;
    *(.snoinit .snoinit.*)
    *(.noinit .noinit.*)
    . = ALIGN(4);
    _RVM_Noinit_End = .;
} > DATA
}

/* Compatibility symbols for various architectures */
PROVIDE(__stack = _RVM_Stack);
PROVIDE(__initial_sp = _RVM_Stack);
PROVIDE(__initial_sp$ = _RVM_Stack);
PROVIDE(__global_pointer = _RVM_Global);
PROVIDE(__global_pointer$ = _RVM_Global);
PROVIDE(__start = _RVM_Entry);
PROVIDE(_stext = _RVM_Code_Start);
PROVIDE(_etext = _RVM_Code_End);
PROVIDE(_sidata = _RVM_Data_Load);
PROVIDE(_sdata = _RVM_Data_Start);
PROVIDE(_edata = _RVM_Data_End);
PROVIDE(_sbss = _RVM_Zero_Start);
PROVIDE(_ebss = _RVM_Zero_End);
PROVIDE(_snoinit = _RVM_Noinit_Start);
PROVIDE(_enoinit = _RVM_Noinit_End);
PROVIDE(__text_start__ = _RVM_Code_Start);
PROVIDE(__text_end__ = _RVM_Code_End);
PROVIDE(__data_load__ = _RVM_Data_Load);
PROVIDE(__data_start__ = _RVM_Data_Start);
PROVIDE(__data_end__ = _RVM_Data_End);
PROVIDE(__bss_start__ = _RVM_Zero_Start);
PROVIDE(__bss_end__ = _RVM_Zero_End);
PROVIDE(__noinit_start__ = _RVM_Noinit_Start);
PROVIDE(__noinit_end__ = _RVM_Noinit_End);
PROVIDE(end = _RVM_Noinit_End);
PROVIDE(_end = _RVM_Noinit_End);
PROVIDE(__end = _RVM_Noinit_End);
PROVIDE(__end__ = _RVM_Noinit_End);
/* End Section ***************************************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/

