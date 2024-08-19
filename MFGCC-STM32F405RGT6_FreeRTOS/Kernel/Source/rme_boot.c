/******************************************************************************
Filename    : rme_boot.c
Author      : The RVM project generator.
Date        : 16/08/2024 22:18:15
License     : Unlicense; see COPYING for details.
Description : The boot-time initialization file.
******************************************************************************/

/* Include *******************************************************************/
#define __HDR_DEF__
#include "Platform/A7M/rme_platform_a7m.h"
#include "Kernel/rme_kernel.h"
#undef __HDR_DEF__

#define __HDR_STRUCT__
#include "Platform/A7M/rme_platform_a7m.h"
#include "Kernel/rme_kernel.h"
#undef __HDR_STRUCT__

#define __HDR_PUBLIC__
#include "Platform/A7M/rme_platform_a7m.h"
#include "Kernel/rme_kernel.h"
#undef __HDR_PUBLIC__

#include "rme_boot.h"
/* End Include ***************************************************************/

/* Private Variable **********************************************************/
/* End Private Variable ******************************************************/

/* Private Function **********************************************************/
RME_EXTERN rme_ptr_t RME_Spurious_Handler(rme_ptr_t Vct_Num);
/* End Private Function ******************************************************/

/* Public Function ***********************************************************/
rme_ptr_t RME_Boot_Vct_Init(struct RME_Cap_Cpt* Cpt, rme_ptr_t Cap_Front, rme_ptr_t Kom_Front);
rme_ptr_t RME_Boot_Vct_Handler(rme_ptr_t Vct_Num);
/* End Public Function *******************************************************/

/* Begin Function:RME_Boot_Vct_Init *******************************************
Description : Initialize all the vector endpoints at boot-time.
Input       : rme_ptr_t Cap_Front - The current capability table frontier.
            : rme_ptr_t Kom_Front - The current kernel absolute memory frontier.
Output      : None.
Return      : rme_ptr_t - The kernel memory frontier after booting is all done.
******************************************************************************/
rme_ptr_t RME_Boot_Vct_Init(struct RME_Cap_Cpt* Cpt, rme_ptr_t Cap_Front, rme_ptr_t Kom_Front)
{
    rme_ptr_t Cur_Addr;

    /* The address here shall match what is in the generator */
    RME_ASSERT(Cap_Front==7U);
    RME_ASSERT(Kom_Front==0x10001A50U);

    Cur_Addr=Kom_Front;
    /* Create all the vector capability tables first */

    /* Then all the vectors */

    return Cur_Addr;
}
/* End Function:RME_Boot_Vct_Init ********************************************/

/* Begin Function:RME_Boot_Vct_Handler ****************************************
Description : The interrupt handler entry for all the vectors.
Input       : rme_ptr_t Vct_Num - The vector number.
Output      : None.
Return      : rme_ptr_t - Whether to send to the generic vector endpoint.
******************************************************************************/
rme_ptr_t RME_Boot_Vct_Handler(rme_ptr_t Vct_Num)
{
    rme_ptr_t Send;
    struct RME_Cap_Sig* Endp;

    Send=0U;

    switch(Vct_Num)
    {
        /* Spurious */
        default: 
        {
            Send=RME_Spurious_Handler(Vct_Num);
            Endp=RME_NULL;
            break;
        }
    }

    if(Endp==RME_NULL)
    {
        if(Send==RME_RVM_VCT_SIG_NONE)
	         return 0U;
        else
	         return 1U;
    }

    switch(Send)
    {
        case RME_RVM_VCT_SIG_ALL: _RME_Kern_Snd(Endp); return 1U;
        case RME_RVM_VCT_SIG_SELF: _RME_Kern_Snd(Endp); return 0U;
        case RME_RVM_VCT_SIG_INIT: return 1U;
        default: break;
    }

    return 0U;
}
/* End Function:RME_Boot_Vct_Handler *****************************************/

/* End Of File ***************************************************************/

/* Copyright (C) Evo-Devo Instrum. All rights reserved ***********************/

