#ifdef __cplusplus
extern "C" {
#endif


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "helper_functions.h"
#include "Dio.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/


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


/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void StatusLed_Set(StatusLed_t ledInstance, bool state){
	Dio_WriteChannel((Dio_ChannelType)ledInstance, (Dio_LevelType)state);
}

void StatusLed_Test(void){
	volatile uint64_t delei;
	uint8_t valori_leduri = 0;
	while(1){
		delei=1000000;
		while(delei--);
		valori_leduri++;
		valori_leduri = valori_leduri % 16;
		StatusLed_Set(BATTERY_LED, (bool)(valori_leduri % 2));
		StatusLed_Set(INVERTERS_LED, (bool)((valori_leduri >> 1) % 2));
		StatusLed_Set(DASHBOARD_LED, (bool)((valori_leduri >> 2) % 2));
		StatusLed_Set(PEDALS_LED, (bool)((valori_leduri  >> 3) % 2));
	}
}

void ActivationLogicButton_Init(void){
	Dio_WriteChannel(ACTIVATION_LOGIC_BUTTON_POWER_PIN_PCR, 1);
}

bool ActivationLogicButton_GetState(void){
	return Dio_ReadChannel(ACTIVATION_LOGIC_BUTTON_READ_PIN_PCR);
}

void ActivationLogicButton_Test(void){
	bool stare_buton;
	while(1){
		if(ActivationLogicButton_GetState()){
			stare_buton = 1;
		}
		else{
			stare_buton = 0;
		}
		StatusLed_Set(BATTERY_LED, stare_buton);
		StatusLed_Set(INVERTERS_LED, stare_buton);
		StatusLed_Set(DASHBOARD_LED, stare_buton);
		StatusLed_Set(PEDALS_LED, stare_buton);
	}
}

#ifdef __cplusplus
}
#endif
