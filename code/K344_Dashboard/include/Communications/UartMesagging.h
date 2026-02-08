#ifndef UART_MESSAGING_H
#define UART_MESSAGING_H

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "stdint.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

typedef enum{
    /* TSAC */
    TSAC_MedianCellTemperature,
    TSAC_HighestCellTemperature,
    TSAC_LowestCellTemperature,
    TSAC_MedianCellVoltage,
    TSAC_HighestCellVoltage,
    TSAC_LowestCellVoltage,
    TSAC_OverallVoltage,
    TSAC_OverallCurrent,
    TSAC_IsAmsSafe,
    TSAC_IsImdSafe,
    TSAC_IsTransceiverWorking,
    TSAC_IsShuntWorking,
    TSAC_IsBms0Working,
    TSAC_IsBms1Working,
    /* PEDALS */
    PEDALS_AcceleratorSensor1Voltage,
    PEDALS_AcceleratorSensor2Voltage,
    PEDALS_AcceleratorSensor1TravelPercentage,
    PEDALS_AcceleratorSensor2TravelPercentage,
    PEDALS_BrakeSensor1Voltage,
    PEDALS_BrakeSensor2Voltage,
    PEDALS_BrakeSensor1TravelPercentage,
    PEDALS_BrakeSensor2TravelPercentage,
    PEDALS_PressureSensorVoltage,
    PEDALS_PressureSensorBars,
    PEDALS_Accel_Sensor1_ShortToGnd,
    PEDALS_Accel_Sensor1_ShortToVcc,
    PEDALS_Accel_Sensor1_OutOfRangeOutput,
    PEDALS_Accel_Sensor2_ShortToGnd,
    PEDALS_Accel_Sensor2_ShortToVcc,
    PEDALS_Accel_Sensor2_OutOfRangeOutput,
    PEDALS_Accel_Implausibility,
    PEDALS_Brake_Sensor1_ShortToGnd,
    PEDALS_Brake_Sensor1_ShortToVcc,
    PEDALS_Brake_Sensor1_OutOfRangeOutput,
    PEDALS_Brake_Sensor2_ShortToGnd,
    PEDALS_Brake_Sensor2_ShortToVcc,
    PEDALS_Brake_Sensor2_OutOfRangeOutput,
    PEDALS_Brake_Implausibility,
    /* INVERTERS */
    INVERTERS_LeftInverterTemperature,
    INVERTERS_LeftMotorTemperature,
    INVERTERS_LeftInverterInputVoltage,
    INVERTERS_LeftInverterCurrent,
    INVERTERS_LeftMotorRpm,
    INVERTERS_LeftMotorSpeedKmh,
    INVERTERS_LeftInverterThrottle,
    INVERTERS_LeftInverterThrottleFeedback,
    INVERTERS_RightInverterTemperature,
    INVERTERS_RightMotorTemperature,
    INVERTERS_RightInverterInputVoltage,
    INVERTERS_RightInverterCurrent,
    INVERTERS_RightMotorRpm,
    INVERTERS_RightMotorSpeedKmh,
    INVERTERS_RightInverterSentThrottle,
    INVERTERS_RightInverterThrottleFeedback,
    INVERTERS_IsCarInReverse,
    INVERTERS_IsCarRunning,
    /* DASHBOARD */
    DASHBOARD_ActivationButtonPressed,
    DASHBOARD_CarReverseCommandPressed,
    DASHBOARD_IsDisplayWorking,
    DASHBOARD_IsSegmentsDriverWorking
}UartMonitoredValue_t;

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

void UartMessaging_Init(void);
void UartMessaging_Test(void);
void UartMessaging_Update(void);
void UartMessaging_SendValue(UartMonitoredValue_t DesiredValueType, uint32_t Value);
uint32_t UartMessaging_ReadValue(UartMonitoredValue_t DesiredValueType);

#ifdef __cplusplus
}
#endif

#endif