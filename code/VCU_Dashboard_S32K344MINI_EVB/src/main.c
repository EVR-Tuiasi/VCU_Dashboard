#ifdef __cplusplus
extern "C" {
#endif


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Port.h"
#include "Det.h"
#include "Spi.h"
#include "Platform.h"
#include "Mcu.h"
#include "Dio.h"
#include "Mcl.h"
#include "Gpt.h"
#include "CDD_I2c.h"

#include "Display/display.h"
#include "Segments/SevenSegments.h"
#include "helper_functions.h"
#include "Messaging.h"
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

int main(void)
{
    Mcu_Init(NULL_PTR);
    Mcu_InitClock(McuClockSettingConfig_0);
    while(MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
    	;
    }
    Mcu_DistributePllClock();
    Mcu_SetMode(McuModeSettingConf_0);
    Mcl_Init(NULL_PTR);
    Platform_Init(NULL_PTR);
    Port_Init(NULL_PTR);
    Gpt_Init(NULL_PTR);
    Spi_Init(NULL_PTR);
    I2c_Init(NULL_PTR);

    //Segments_Init();
    //Segments_TimeoutTest();
    //Segments_Test();

    //ActivationLogicButton_Init();
    //ActivationLogicButton_Test();
	Display_Init();
	//TouchTest();
	//SoundTest();
	while(1){
		Display_Update(MonitoredValues.PedalsMonitoredValues.AcceleratorSensor1TravelPercentage.valueCan, MonitoredValues.PedalsMonitoredValues.BrakeSensor1TravelPercentage.valueCan, 100, MonitoredValues.InvertersMonitoredValues.LeftMotorTemperature.valueCan, MonitoredValues.InvertersMonitoredValues.LeftInverterTemperature.valueCan, MonitoredValues.InvertersMonitoredValues.LeftMotorSpeedKmh.valueCan, 0, 0, 0, 0, 0, 0, 0);
	}
	TouchTest();
	//StatusLed_Test();
}


#ifdef __cplusplus
}
#endif
