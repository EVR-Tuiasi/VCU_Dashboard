/*
 *   Copyright 2020 NXP
 *
 *   NXP Confidential. This software is owned or controlled by NXP and may only be used strictly
 *   in accordance with the applicable license terms.  By expressly accepting
 *   such terms or by downloading, installing, activating and/or otherwise using
 *   the software, you are agreeing that you have read, and that you agree to
 *   comply with and are bound by, such license terms.  If you do not agree to
 *   be bound by the applicable license terms, then you may not retain,
 *   install, activate or otherwise use the software.
 *
 *   This file contains sample code only. It is not part of the production code deliverables.
 */

#ifdef __cplusplus
extern "C" {
#endif


/*==================================================================================================
 *                                        INCLUDE FILES
 * 1) system and project includes
 * 2) needed interfaces from external units
 * 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Spi.h"
#include "Gpt.h"
#include "Platform.h"
#include "display.h"
#include "FT81_misc.h"
#include "FT81_display.h"
#include "FT81_sound.h"
#include "FT81_touch.h"

#include "check_example.h"

/*==================================================================================================
 *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
 *                                       LOCAL MACROS
==================================================================================================*/

#define TIMEOUT_VALUE	48000					//for 10ms

/*==================================================================================================
 *                                      LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
 *                                      LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
 *                                      GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
 *                                      GLOBAL VARIABLES
==================================================================================================*/

uint8 testValues[] = {15, 42, 15, 22, 53, 21, 99, 19, 82, 111, 5, 29, 15, 83, 0, 7, 33, 26};
volatile uint32_t milis = 0U;

/*==================================================================================================
 *                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
 *                                       LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================
 *                                       GLOBAL FUNCTIONS
==================================================================================================*/

void Gpt_FtmNotification(void){
	milis++;
}

uint8_t Get_Seconds(void){
	return ((milis / 1000U) % 60);
}

uint8_t Get_Minutes(void){
	return ((milis / 60000U));
}

/**
 * @brief        Main function of the example
 * @details      Initializez the used drivers and uses the Icu
 *               and Dio drivers to toggle a LED on a push button
 */
int main(void)
{
	uint8_t channel = 0U;
	int i;
	int j;
	/* Initialize the Mcu driver */
#if (MCU_PRECOMPILE_SUPPORT == STD_ON)
	Mcu_Init(NULL_PTR);
#elif (MCU_PRECOMPILE_SUPPORT == STD_OFF)

	Mcu_Init(&Mcu_Config_VS_0);
#endif /* (MCU_PRECOMPILE_SUPPORT == STD_ON) */

	/* Initialize the clock tree and apply PLL as system clock */
	Mcu_InitClock(McuClockSettingConfig_0);
#if (MCU_NO_PLL == STD_OFF)
	while ( MCU_PLL_LOCKED != Mcu_GetPllStatus() )
	{
		/* Busy wait until the System PLL is locked */
	}

	Mcu_DistributePllClock();
#endif
	Mcu_SetMode(McuModeSettingConf_0);

	/* Initialize all pins using the Port driver */
	Port_Init(NULL_PTR);
	Spi_Init(NULL_PTR);
	Platform_Init(NULL_PTR);
	Gpt_Init(NULL_PTR);

	Gpt_StartTimer(channel, TIMEOUT_VALUE);
	Gpt_EnableNotification(channel);

	trailingArray();
	Display_Init();
	while(1){
		for(i = 0; i < 18; i++)
		{
			for(j = 0; j < 70; j++)
			{
			Display_Test(testValues[i], Get_Minutes(), Get_Seconds(), milis);
			Get_Seconds();
			Get_Minutes();
			}
		}

	}
}

#ifdef __cplusplus
}
#endif

/** @} */
