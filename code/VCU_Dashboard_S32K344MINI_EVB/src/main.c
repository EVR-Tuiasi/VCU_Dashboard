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
#include "Can_43_FlexCan.h"
#include "CanIf.h"

#include "Display/display.h"
#include "Segments/SevenSegments.h"
#include "helper_functions.h"
#include "Messaging.h"
#include "CanMessaging.h"
/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

#define BATTERY_HIGH_VOLTAGE 1008U
#define BATTERY_LOW_VOLTAGE 800U
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
bool reverseToggle = false;

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
    Can_43_FLEXCAN_Init(NULL_PTR);
    CanIf_Init(NULL_PTR);

    Segments_Init();
    //Segments_TimeoutTest();
    //Segments_Test();

    ActivationLogicButton_Init();
    //ActivationLogicButton_Test();
    CanMessaging_Init();
    //CanMessaging_Test();
	Display_Init();
	//Display_Test(&reverseToggle);
	//Display_Touch_Test();
	//Display_Sound_Test();
	//StatusLed_Test();
	uint8_t acceleration, braking, batteryPercentage, speed, witnesses;
	uint16_t cellVoltage, cellTemperature, totalCurrent, totalVoltage, maxTemperature;
	uint32_t limitedVoltage;
	int motorTemperature, inverterTemperature;
	volatile bool battery_error, pedals_error, inverters_error, /*dashboard_error,*/ acceleration_error, brake_error;
	while(1){
		acceleration = MonitoredValues.PedalsMonitoredValues.AcceleratorSensor1TravelPercentage.valueCan;
		if(acceleration < MonitoredValues.PedalsMonitoredValues.AcceleratorSensor2TravelPercentage.valueCan)
			acceleration = MonitoredValues.PedalsMonitoredValues.AcceleratorSensor2TravelPercentage.valueCan;

		braking = MonitoredValues.PedalsMonitoredValues.BrakeSensor1TravelPercentage.valueCan;
		if(braking < MonitoredValues.PedalsMonitoredValues.BrakeSensor2TravelPercentage.valueCan)
			braking = MonitoredValues.PedalsMonitoredValues.BrakeSensor2TravelPercentage.valueCan;

		motorTemperature = (int)MonitoredValues.InvertersMonitoredValues.LeftMotorTemperature.valueCan;
		if(motorTemperature < (int)MonitoredValues.InvertersMonitoredValues.RightMotorTemperature.valueCan)
			motorTemperature = (int)MonitoredValues.InvertersMonitoredValues.RightMotorTemperature.valueCan;
		motorTemperature -= 30;
		if(motorTemperature < 0)
			motorTemperature = 0;

		inverterTemperature = (int)MonitoredValues.InvertersMonitoredValues.LeftInverterTemperature.valueCan;
		if(inverterTemperature < (int)MonitoredValues.InvertersMonitoredValues.RightInverterTemperature.valueCan)
			inverterTemperature = (int)MonitoredValues.InvertersMonitoredValues.RightInverterTemperature.valueCan;
		inverterTemperature -= 40;
		if(inverterTemperature < 0)
			inverterTemperature = 0;

		speed = MonitoredValues.InvertersMonitoredValues.LeftMotorSpeedKmh.valueCan;
		if(speed < MonitoredValues.InvertersMonitoredValues.RightMotorSpeedKmh.valueCan)
			speed = MonitoredValues.InvertersMonitoredValues.RightMotorSpeedKmh.valueCan;

		cellVoltage = MonitoredValues.TsacMonitoredValues.HighestCellVoltage.valueCan;
		cellTemperature = MonitoredValues.TsacMonitoredValues.HighestCellTemperature.valueCan;
		totalCurrent = MonitoredValues.TsacMonitoredValues.OverallCurrent.valueCan / 10U;
		totalVoltage = MonitoredValues.TsacMonitoredValues.OverallVoltage.valueCan / 10U;

		if(MonitoredValues.TsacMonitoredValues.OverallVoltage.valueCan < BATTERY_LOW_VOLTAGE){
			limitedVoltage = BATTERY_LOW_VOLTAGE;
		}
		else if(MonitoredValues.TsacMonitoredValues.OverallVoltage.valueCan > BATTERY_HIGH_VOLTAGE){
			limitedVoltage = BATTERY_HIGH_VOLTAGE;
		}
		else{
			limitedVoltage = MonitoredValues.TsacMonitoredValues.OverallVoltage.valueCan;
		}
		batteryPercentage = (limitedVoltage - BATTERY_LOW_VOLTAGE) * 100U / (BATTERY_HIGH_VOLTAGE - BATTERY_LOW_VOLTAGE);

		Segments_Set(SPEED_KMH, speed * 10U);
		Segments_Set(BATTERY_PERCENTAGE, batteryPercentage * 10U);
		maxTemperature = motorTemperature*10U;
		if(maxTemperature < inverterTemperature*10U)
			maxTemperature = inverterTemperature*10U;
		if(maxTemperature < cellTemperature)
			maxTemperature = cellTemperature;
		Segments_Set(TEMPERATURE, maxTemperature);

		battery_error = CanMessaging_GetBatteryReceiveTimeout() | MonitoredValues.TsacMonitoredValues.AmsError.valueCan | MonitoredValues.TsacMonitoredValues.Bms0Error.valueCan | MonitoredValues.TsacMonitoredValues.Bms1Error.valueCan | MonitoredValues.TsacMonitoredValues.ThermistorsError.valueCan | MonitoredValues.TsacMonitoredValues.TransceiverError.valueCan | MonitoredValues.TsacMonitoredValues.ShuntError.valueCan;
		acceleration_error = CanMessaging_GetPedalsReceiveTimeout() | MonitoredValues.PedalsMonitoredValues.Accel_Implausibility.valueCan | MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_OutOfRangeOutput.valueCan | MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToGnd.valueCan | MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToVcc.valueCan | MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_OutOfRangeOutput.valueCan | MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToGnd.valueCan | MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToVcc.valueCan;
		brake_error = CanMessaging_GetPedalsReceiveTimeout() | MonitoredValues.PedalsMonitoredValues.Brake_Implausibility.valueCan | MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_OutOfRangeOutput.valueCan | MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToGnd.valueCan | MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToVcc.valueCan | MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_OutOfRangeOutput.valueCan | MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToGnd.valueCan | MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToVcc.valueCan;
		pedals_error = CanMessaging_GetPedalsReceiveTimeout() | acceleration_error | brake_error;
		inverters_error = CanMessaging_GetInvertersReceiveTimeout() | MonitoredValues.InvertersMonitoredValues.InvertersError.valueCan;
		//dashboard_error = MonitoredValues.DashboardMonitoredValues.IsDisplayWorking.valueCan | MonitoredValues.DashboardMonitoredValues.IsSegmentsDriverWorking.valueCan;

		witnesses = 0;
		if(brake_error){
			witnesses |= BRAKE_WARNING;
		}
		if(acceleration_error){
			witnesses |= ACCEL_WARNING;
		}
		if(battery_error){
			witnesses |= BATTERY_WARNING;
		}
		if(inverters_error){
			witnesses |= INVERTER_WARNING;
		}

		StatusLed_Set(BATTERY_LED, battery_error);
		StatusLed_Set(PEDALS_LED, pedals_error);
		StatusLed_Set(INVERTERS_LED, inverters_error);
		StatusLed_Set(DASHBOARD_LED, !ActivationLogicButton_GetState());
		touchScreen_Update(&reverseToggle);		//commented if not used, reverseToggle will always be FALSE
		Display_Update(acceleration, braking, batteryPercentage, motorTemperature, inverterTemperature, speed, cellVoltage, cellTemperature, totalCurrent, totalVoltage, 0, 0, 0, witnesses, &reverseToggle);
		Segments_Update();
		ActivationLogicButton_Update();

		WriteCanDataAtAddress(ActivationLogicButton_GetState(), &MonitoredValues.DashboardMonitoredValues.ActivationButtonPressed);
		WriteCanDataAtAddress(reverseToggle, &MonitoredValues.DashboardMonitoredValues.CarReverseCommandPressed);
		CanMessaging_Update();
	}
}


#ifdef __cplusplus
}
#endif
