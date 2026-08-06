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
#include "Display/display.h"
#include "Messaging.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/
#define BRAKE_PERCENTAGE_THRESHOLD 10U

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

static ActivationButtonState_t activationButtonState = DEACTIVATED_PRESSED;
/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/
extern MonitoredValues_t MonitoredValues;

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
	switch(activationButtonState){
		case DEACTIVATED_PRESSED:
		case DEACTIVATED_NOT_PRESSED:
			return false;
		case ACTIVATED_PRESSED:
		case ACTIVATED_NOT_PRESSED:
			return true;
		default:
			return false;
	}
}

void ActivationLogicButton_Test(void){
	bool stare_buton;
	while(1){
		if(Dio_ReadChannel(ACTIVATION_LOGIC_BUTTON_READ_PIN_PCR)){
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

void ActivationLogicButton_Update(void){
	uint8_t brake_sensor1_travel_percentage, brake_sensor2_travel_percentage, brake_travel_percentage;
	brake_sensor1_travel_percentage = MonitoredValues.PedalsMonitoredValues.BrakeSensor1TravelPercentage.valueCan;
	brake_sensor2_travel_percentage = MonitoredValues.PedalsMonitoredValues.BrakeSensor2TravelPercentage.valueCan;
	brake_travel_percentage = brake_sensor1_travel_percentage;
	if(brake_travel_percentage > brake_sensor2_travel_percentage){
		brake_travel_percentage = brake_sensor2_travel_percentage;
	}
	switch(activationButtonState){
		case DEACTIVATED_PRESSED:
			if(Dio_ReadChannel(ACTIVATION_LOGIC_BUTTON_READ_PIN_PCR) == STD_OFF){
				activationButtonState = DEACTIVATED_NOT_PRESSED;
			}
			break;
		case DEACTIVATED_NOT_PRESSED:
			if((Dio_ReadChannel(ACTIVATION_LOGIC_BUTTON_READ_PIN_PCR) == STD_ON) && (brake_travel_percentage >= BRAKE_PERCENTAGE_THRESHOLD)){
				activationButtonState = ACTIVATED_PRESSED;
				Display_Sound_Play();
			}
			break;
		case ACTIVATED_PRESSED:
			if((Dio_ReadChannel(ACTIVATION_LOGIC_BUTTON_READ_PIN_PCR) == STD_OFF)  && (brake_travel_percentage >= BRAKE_PERCENTAGE_THRESHOLD)){
				activationButtonState = ACTIVATED_NOT_PRESSED;
			}
			break;
		case ACTIVATED_NOT_PRESSED:
			if(Dio_ReadChannel(ACTIVATION_LOGIC_BUTTON_READ_PIN_PCR) == STD_ON){
				activationButtonState = DEACTIVATED_PRESSED;;
			}
			break;
	}
}

#ifdef __cplusplus
}
#endif
