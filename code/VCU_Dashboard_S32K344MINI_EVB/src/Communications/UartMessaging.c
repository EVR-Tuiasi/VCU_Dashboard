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
#include "Mcu.h"
#include "Port.h"
#include "Platform.h"
#include "Can_GeneralTypes.h"
#include "Can_43_FLEXCAN.h"
#include "CanIf.h"
#include "SchM_Can_43_FLEXCAN.h"
#include "CDD_Uart.h"
#include "Dio.h"
#include "Mcl.h"
#include "UartMessaging.h"
#include "Messaging_Types.h"

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

InvertersMonitoredValues_t invertoareUart;
PedalsMonitoredValues_t pedaleUart;
TsacMonitoredValues_t baterieUart;
DashboardMonitoredValues_t bordUart;

uint8_t bufferUart[10];

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

void UartMessaging_Init(void){
	Uart_Init(NULL_PTR);
}

/*void UartMessaging_Test(void){
	int cnt = 0;
	volatile int i;
	while(1){
		UartMessaging_SetValue(UART_TSAC_MEDIAN_CELL_TEMP, cnt);
		UartMessaging_SetValue(UART_TSAC_HIGHEST_CELL_TEMP, cnt);
		UartMessaging_SetValue(UART_TSAC_LOWEST_CELL_TEMP, cnt);
		UartMessaging_SetValue(UART_TSAC_MEDIAN_CELL_VOLT, cnt);
		UartMessaging_SetValue(UART_TSAC_HIGHEST_CELL_VOLT, cnt);
		UartMessaging_SetValue(UART_TSAC_LOWEST_CELL_VOLT, cnt);
		UartMessaging_SetValue(UART_TSAC_OVERALL_VOLT, cnt);
		UartMessaging_SetValue(UART_TSAC_OVERALL_AMPS, cnt);
		//baterieUart.CellVoltage[CELLS_NUM];
		//baterieUart.ThermistorTemperature[THERMISTOR_NUM];
		UartMessaging_SetValue(UART_TSAC_IS_AMS_SAFE, 1);
		UartMessaging_SetValue(UART_TSAC_IS_AMS_SAFE, 1);
		UartMessaging_SetValue(UART_TSAC_IS_SHUNT_WORKING, 1);
		UartMessaging_SetValue(UART_TSAC_IS_BMS_0_WORKING, 1);
		UartMessaging_SetValue(UART_TSAC_IS_BMS_1_WORKING, 1);

		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_1_VOLTAGE, cnt);
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_2_VOLTAGE, cnt);
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_1_TRAVEL_PERCENT, cnt%101);
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_2_TRAVEL_PERCENT, cnt%101);
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_1_VOLT, cnt);
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_2_VOLT, cnt);
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_1_TRAVEL_PERCENT, cnt%101);
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_2_TRAVEL_PERCENT, cnt%101);
		UartMessaging_SetValue(UART_PEDALS_PRESSURE_SENS_VOLT, cnt%501);
		UartMessaging_SetValue(UART_PEDALS_PRESSURE_SENS_BARS, cnt);
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_1_SHORT_TO_GND, cnt & 1);
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_1_SHORT_TO_VCC, cnt & 1);
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_1_OUT_OF_RANGE, cnt & 1);
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_2_SHORT_TO_GND, cnt & 1);
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_2_SHORT_TO_VCC, cnt & 1);
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_2_OUT_OF_RANGE, cnt & 1);
		UartMessaging_SetValue(UART_PEDALS_ACCEL_IMPLAUSIBILITY, cnt & 1);
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_1_SHORT_TO_GND, cnt & 1);
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_1_SHORT_TO_VCC, cnt & 1);
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_1_OUT_OF_RANGE, cnt & 1);
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_2_SHORT_TO_GND, cnt & 1);
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_2_SHORT_TO_VCC, cnt & 1);
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_2_OUT_OF_RANGE, cnt & 1);
		UartMessaging_SetValue(UART_PEDALS_BRAKE_IMPLAUSIBILITY, cnt & 1);

		UartMessaging_SetValue(UART_INVERTERS_LEFT_INVERT_TEMP, cnt);
		UartMessaging_SetValue(UART_INVERTERS_LEFT_MOTOR_TEMP, cnt);
		UartMessaging_SetValue(UART_INVERTERS_LEFT_INVERTER_INPUT_VOLT, cnt%1801);
		UartMessaging_SetValue(UART_INVERTERS_LEFT_INVERTER_AMPS, cnt%4001);
		UartMessaging_SetValue(UART_INVERTERS_LEFT_MOTOR_RPM, cnt%6001);
		UartMessaging_SetValue(UART_INVERTERS_LEFT_MOTOR_KMH, cnt);
		UartMessaging_SetValue(UART_INVERTERS_LEFT_INVERTER_THROTTLE, cnt%251);
		UartMessaging_SetValue(UART_INVERTERS_LEFT_INVERTER_THROTTLE_FEEDBACK, cnt%251);
		UartMessaging_SetValue(UART_INVERTERS_RIGHT_INVERTER_TEMP, cnt);
		UartMessaging_SetValue(UART_INVERTERS_RIGHT_MOTOR_TEMP, cnt);
		UartMessaging_SetValue(UART_INVERTERS_RIGHT_INVERTER_INPUT_VOLT, cnt%1801);
		UartMessaging_SetValue(UART_INVERTERS_RIGHT_INVERTER_AMPS, cnt%4001);
		UartMessaging_SetValue(UART_INVERTERS_RIGHT_MOTOR_RPM, cnt%6001);
		UartMessaging_SetValue(UART_INVERTERS_RIGHT_MOTOR_KMH, cnt);
		UartMessaging_SetValue(UART_INVERTERS_RIGHT_INVERTER_THROTTLE, cnt%251);
		UartMessaging_SetValue(UART_INVERTERS_RIGHT_INVERTER_THROTTLE_FEEDBACK, cnt%251);
		UartMessaging_SetValue(UART_INVERTERS_IS_CAR_IN_REVERSE, cnt & 1);
		UartMessaging_SetValue(UART_INVERTERS_IS_CAR_RUNNING, cnt & 1);

		UartMessaging_SetValue(UART_DASHBOARD_ACTIVATION_COMMAND, cnt & 1);
		UartMessaging_SetValue(UART_DASHBOARD_CAR_REVERSE_COMMAND, cnt & 1);
		UartMessaging_SetValue(UART_DASHBOARD_IS_DISPLAY_WORKING, cnt & 1);
		UartMessaging_SetValue(UART_DASHBOARD_IS_SEGMENTS_DRIVER_WORKING, cnt & 1);

		cnt++;
		UartMessaging_Update();
		i=100000;
		while(i--);
	}
}*/

/*void UartMessaging_Update(void){
	volatile int i;
	UartMessaging_CreateBuffer(ID_UART_INVERTOR_STANGA);
	Uart_SyncSend(UART_Channel, bufferUart, 10, 10000000);
	i=100000;
	while(i--);
	UartMessaging_CreateBuffer(ID_UART_INVERTOR_DREAPTA);
	Uart_SyncSend(UART_Channel, bufferUart, 10, 10000000);
	i=100000;
	while(i--);
	UartMessaging_CreateBuffer(ID_UART_INVERTOARE);
	Uart_SyncSend(UART_Channel, bufferUart, 10, 10000000);
	i=100000;
	while(i--);
	UartMessaging_CreateBuffer(ID_UART_BORD);
	Uart_SyncSend(UART_Channel, bufferUart, 10, 10000000);
	i=100000;
	while(i--);
	UartMessaging_CreateBuffer(ID_UART_ACCELERATIE);
	Uart_SyncSend(UART_Channel, bufferUart, 10, 10000000);
	i=100000;
	while(i--);
	UartMessaging_CreateBuffer(ID_UART_FRANA);
	Uart_SyncSend(UART_Channel, bufferUart, 10, 10000000);
	i=100000;
	while(i--);
	UartMessaging_CreateBuffer(ID_UART_BATERIE);
	Uart_SyncSend(UART_Channel, bufferUart, 10, 10000000);
	i=100000;
	while(i--);
}
*/
void UartMessaging_SetValue(UartMonitoredValue_t DesiredValueType, uint32_t Value){
	/*
	switch(DesiredValueType){
		//TSAC
		case UART_TSAC_MEDIAN_CELL_TEMP:
			baterieUart.MedianCellTemperature = Value;
			break;
		case UART_TSAC_HIGHEST_CELL_TEMP:
			baterieUart.HighestCellTemperature = Value;
			break;
		case UART_TSAC_LOWEST_CELL_TEMP:
			baterieUart.LowestCellTemperature = Value;
			break;
		case UART_TSAC_MEDIAN_CELL_VOLT:
			baterieUart.MedianCellVoltage = Value;
			break;
		case UART_TSAC_HIGHEST_CELL_VOLT:
			baterieUart.HighestCellVoltage = Value;
			break;
		case UART_TSAC_LOWEST_CELL_VOLT:
			baterieUart.LowestCellVoltage = Value;
			break;
		case UART_TSAC_OVERALL_VOLT:
			baterieUart.OverallVoltage = Value;
			break;
		case UART_TSAC_OVERALL_AMPS:
			if(Value>8095)
				baterieUart.OverallCurrent = 0;
			else
				baterieUart.OverallCurrent = Value;
			break;
		case UART_TSAC_IS_AMS_SAFE:
			baterieUart.AmsError = Value;
			break;
		case UART_TSAC_IS_TRANSCEIVER_WORKING:
			baterieUart.TransceiverError = Value;
			break;
		case UART_TSAC_IS_SHUNT_WORKING:
			baterieUart.ShuntError = Value;
			break;
		case UART_TSAC_IS_BMS_0_WORKING:
			baterieUart.Bms0Error = Value;
			break;
		case UART_TSAC_IS_BMS_1_WORKING:
			baterieUart.Bms1Error = Value;
			break;
		//PEDALS
		case UART_PEDALS_ACCEL_SENS_1_VOLTAGE:
			pedaleUart.AcceleratorSensor1Voltage = Value;
			break;
		case UART_PEDALS_ACCEL_SENS_2_VOLTAGE:
			pedaleUart.AcceleratorSensor2Voltage = Value;
			break;
		case UART_PEDALS_ACCEL_SENS_1_TRAVEL_PERCENT:
			if(Value>100)
				pedaleUart.AcceleratorSensor1TravelPercentage = 0;
			else
				pedaleUart.AcceleratorSensor1TravelPercentage = Value;
			break;
		case UART_PEDALS_ACCEL_SENS_2_TRAVEL_PERCENT:
			if(Value>100)
				pedaleUart.AcceleratorSensor2TravelPercentage = 0;
			else
				pedaleUart.AcceleratorSensor2TravelPercentage = Value;
			break;
		case UART_PEDALS_BRAKE_SENS_1_VOLT:
			pedaleUart.BrakeSensor1Voltage = Value;
			break;
		case UART_PEDALS_BRAKE_SENS_2_VOLT:
			pedaleUart.BrakeSensor2Voltage = Value;
			break;
		case UART_PEDALS_BRAKE_SENS_1_TRAVEL_PERCENT:
			if(Value>100)
				pedaleUart.BrakeSensor1TravelPercentage = 0;
			else
				pedaleUart.BrakeSensor1TravelPercentage = Value;
			break;
		case UART_PEDALS_BRAKE_SENS_2_TRAVEL_PERCENT:
			if(Value>100)
				pedaleUart.BrakeSensor2TravelPercentage = 0;
			else
				pedaleUart.BrakeSensor2TravelPercentage = Value;
			break;
		case UART_PEDALS_PRESSURE_SENS_VOLT:
			if(Value>500)
				pedaleUart.PressureSensorVoltage = 0;
			else
				pedaleUart.PressureSensorVoltage = Value;
			break;
		case UART_PEDALS_PRESSURE_SENS_BARS:
			pedaleUart.PressureSensorBars = Value;
			break;
		case UART_PEDALS_ACCEL_SENS_1_SHORT_TO_GND:
			pedaleUart.Accel_Sensor1_ShortToGnd = Value;
			break;
		case UART_PEDALS_ACCEL_SENS_1_SHORT_TO_VCC:
			pedaleUart.Accel_Sensor1_ShortToVcc = Value;
			break;
		case UART_PEDALS_ACCEL_SENS_1_OUT_OF_RANGE:
			pedaleUart.Accel_Sensor1_OutOfRangeOutput = Value;
			break;
		case UART_PEDALS_ACCEL_SENS_2_SHORT_TO_GND:
			pedaleUart.Accel_Sensor2_ShortToGnd = Value;
			break;
		case UART_PEDALS_ACCEL_SENS_2_SHORT_TO_VCC:
			pedaleUart.Accel_Sensor2_ShortToVcc = Value;
			break;
		case UART_PEDALS_ACCEL_SENS_2_OUT_OF_RANGE:
			pedaleUart.Accel_Sensor2_OutOfRangeOutput = Value;
			break;
		case UART_PEDALS_ACCEL_IMPLAUSIBILITY:
			pedaleUart.Accel_Implausibility = Value;
			break;
		case UART_PEDALS_BRAKE_SENS_1_SHORT_TO_GND:
			pedaleUart.Brake_Sensor1_ShortToGnd = Value;
			break;
		case UART_PEDALS_BRAKE_SENS_1_SHORT_TO_VCC:
			pedaleUart.Brake_Sensor1_ShortToVcc = Value;
			break;
		case UART_PEDALS_BRAKE_SENS_1_OUT_OF_RANGE:
			pedaleUart.Brake_Sensor1_OutOfRangeOutput = Value;
			break;
		case UART_PEDALS_BRAKE_SENS_2_SHORT_TO_GND:
			pedaleUart.Brake_Sensor2_ShortToGnd = Value;
			break;
		case UART_PEDALS_BRAKE_SENS_2_SHORT_TO_VCC:
			pedaleUart.Brake_Sensor2_ShortToVcc = Value;
			break;
		case UART_PEDALS_BRAKE_SENS_2_OUT_OF_RANGE:
			pedaleUart.Brake_Sensor2_OutOfRangeOutput = Value;
			break;
		case UART_PEDALS_BRAKE_IMPLAUSIBILITY:
			pedaleUart.Brake_Implausibility = Value;
			break;
		//INVERTERS
		case UART_INVERTERS_LEFT_INVERT_TEMP:
			invertoareUart.LeftInverterTemperature = Value;
			break;
		case UART_INVERTERS_LEFT_MOTOR_TEMP:
			invertoareUart.LeftMotorTemperature = Value;
			break;
		case UART_INVERTERS_LEFT_INVERTER_INPUT_VOLT:
			if(Value>1800)
				invertoareUart.LeftInverterInputVoltage = 0;
			else
				invertoareUart.LeftInverterInputVoltage = Value;
			break;
		case UART_INVERTERS_LEFT_INVERTER_AMPS:
			if(Value>4000)
				invertoareUart.LeftInverterCurrent = 0;
			else
				invertoareUart.LeftInverterCurrent = Value;
			break;
		case UART_INVERTERS_LEFT_MOTOR_RPM:
			if(Value>6000)
				invertoareUart.LeftMotorRpm = 0;
			else
				invertoareUart.LeftMotorRpm = Value;
			break;
		case UART_INVERTERS_LEFT_MOTOR_KMH:
			invertoareUart.LeftMotorSpeedKmh = Value;
			break;
		case UART_INVERTERS_LEFT_INVERTER_THROTTLE:
			if(Value>250)
				invertoareUart.LeftInverterThrottle = 0;
			else
				invertoareUart.LeftInverterThrottle = Value;
			break;
		case UART_INVERTERS_LEFT_INVERTER_THROTTLE_FEEDBACK:
			if(Value>250)
				invertoareUart.LeftInverterThrottleFeedback = 0;
			else
				invertoareUart.LeftInverterThrottleFeedback = Value;
			break;
		case UART_INVERTERS_RIGHT_INVERTER_TEMP:
			invertoareUart.RightInverterTemperature = Value;
			break;
		case UART_INVERTERS_RIGHT_MOTOR_TEMP:
			invertoareUart.RightMotorTemperature = Value;
			break;
		case UART_INVERTERS_RIGHT_INVERTER_INPUT_VOLT:
			if(Value>1800)
				invertoareUart.RightInverterInputVoltage = 0;
			else
				invertoareUart.RightInverterInputVoltage = Value;
			break;
		case UART_INVERTERS_RIGHT_INVERTER_AMPS:
			if(Value>4000)
				invertoareUart.RightInverterCurrent = 0;
			else
				invertoareUart.RightInverterCurrent = Value;
			break;
		case UART_INVERTERS_RIGHT_MOTOR_RPM:
			if(Value>6000)
				invertoareUart.RightMotorRpm = 0;
			else
				invertoareUart.RightMotorRpm = Value;
			break;
		case UART_INVERTERS_RIGHT_MOTOR_KMH:
			invertoareUart.RightMotorSpeedKmh = Value;
			break;
		case UART_INVERTERS_RIGHT_INVERTER_THROTTLE:
			if(Value>250)
				invertoareUart.RightInverterSentThrottle = 0;
			else
				invertoareUart.RightInverterSentThrottle = Value;
			break;
		case UART_INVERTERS_RIGHT_INVERTER_THROTTLE_FEEDBACK:
			if(Value>250)
				invertoareUart.RightInverterThrottleFeedback = 0;
			else
				invertoareUart.RightInverterThrottleFeedback = Value;
			break;
		case UART_INVERTERS_IS_CAR_IN_REVERSE:
			invertoareUart.IsCarInReverse = Value;
			break;
		case UART_INVERTERS_IS_CAR_RUNNING:
			invertoareUart.IsCarRunning = Value;
			break;
		//DASHBOARD
		case UART_DASHBOARD_ACTIVATION_COMMAND:
			bordUart.ActivationButtonPressed = Value;
			break;
		case UART_DASHBOARD_CAR_REVERSE_COMMAND:
			bordUart.CarReverseCommandPressed = Value;
			break;
		case UART_DASHBOARD_IS_DISPLAY_WORKING:
			bordUart.IsDisplayWorking = Value;
			break;
		case UART_DASHBOARD_IS_SEGMENTS_DRIVER_WORKING:
			bordUart.IsSegmentsDriverWorking = Value;
			break;
	}*/
}

/*uint32_t UartMessaging_ReadValue(UartMonitoredValue_t DesiredValueType){
	switch(DesiredValueType){
		case UART_TSAC_MEDIAN_CELL_TEMP:
			return baterieUart.MedianCellTemperature;
		case UART_TSAC_HIGHEST_CELL_TEMP:
			return baterieUart.HighestCellTemperature;
		case UART_TSAC_LOWEST_CELL_TEMP:
			return baterieUart.LowestCellTemperature;
		case UART_TSAC_MEDIAN_CELL_VOLT:
			return baterieUart.MedianCellVoltage;
		case UART_TSAC_HIGHEST_CELL_VOLT:
			return baterieUart.HighestCellVoltage;
		case UART_TSAC_LOWEST_CELL_VOLT:
			return baterieUart.LowestCellVoltage;
		case UART_TSAC_OVERALL_VOLT:
			return baterieUart.OverallVoltage;
		case UART_TSAC_OVERALL_AMPS:
			return baterieUart.OverallCurrent;
		case UART_TSAC_IS_AMS_SAFE:
			return baterieUart.AmsError;
		case UART_TSAC_IS_TRANSCEIVER_WORKING:
			return baterieUart.TransceiverError;
		case UART_TSAC_IS_SHUNT_WORKING:
			return baterieUart.ShuntError;
		case UART_TSAC_IS_BMS_0_WORKING:
			return baterieUart.Bms0Error;
		case UART_TSAC_IS_BMS_1_WORKING:
			return baterieUart.Bms1Error;
		case UART_PEDALS_ACCEL_SENS_1_VOLTAGE:
			return pedaleUart.AcceleratorSensor1Voltage;
		case UART_PEDALS_ACCEL_SENS_2_VOLTAGE:
			return pedaleUart.AcceleratorSensor2Voltage;
		case UART_PEDALS_ACCEL_SENS_1_TRAVEL_PERCENT:
			return pedaleUart.AcceleratorSensor1TravelPercentage;
		case UART_PEDALS_ACCEL_SENS_2_TRAVEL_PERCENT:
			return pedaleUart.AcceleratorSensor2TravelPercentage;
		case UART_PEDALS_BRAKE_SENS_1_VOLT:
			return pedaleUart.BrakeSensor1Voltage;
		case UART_PEDALS_BRAKE_SENS_2_VOLT:
			return pedaleUart.BrakeSensor2Voltage;
		case UART_PEDALS_BRAKE_SENS_1_TRAVEL_PERCENT:
			return pedaleUart.BrakeSensor1TravelPercentage;
		case UART_PEDALS_BRAKE_SENS_2_TRAVEL_PERCENT:
			return pedaleUart.BrakeSensor2TravelPercentage;
		case UART_PEDALS_PRESSURE_SENS_VOLT:
			return pedaleUart.PressureSensorVoltage;
		case UART_PEDALS_PRESSURE_SENS_BARS:
			return pedaleUart.PressureSensorBars;
		case UART_PEDALS_ACCEL_SENS_1_SHORT_TO_GND:
			return pedaleUart.Accel_Sensor1_ShortToGnd;
		case UART_PEDALS_ACCEL_SENS_1_SHORT_TO_VCC:
			return pedaleUart.Accel_Sensor1_ShortToVcc;
		case UART_PEDALS_ACCEL_SENS_1_OUT_OF_RANGE:
			return pedaleUart.Accel_Sensor1_OutOfRangeOutput;
		case UART_PEDALS_ACCEL_SENS_2_SHORT_TO_GND:
			return pedaleUart.Accel_Sensor2_ShortToGnd;
		case UART_PEDALS_ACCEL_SENS_2_SHORT_TO_VCC:
			return pedaleUart.Accel_Sensor2_ShortToVcc;
		case UART_PEDALS_ACCEL_SENS_2_OUT_OF_RANGE:
			return pedaleUart.Accel_Sensor2_OutOfRangeOutput;
		case UART_PEDALS_ACCEL_IMPLAUSIBILITY:
			return pedaleUart.Accel_Implausibility;
		case UART_PEDALS_BRAKE_SENS_1_SHORT_TO_GND:
			return pedaleUart.Brake_Sensor1_ShortToGnd;
		case UART_PEDALS_BRAKE_SENS_1_SHORT_TO_VCC:
			return pedaleUart.Brake_Sensor1_ShortToVcc;
		case UART_PEDALS_BRAKE_SENS_1_OUT_OF_RANGE:
			return pedaleUart.Brake_Sensor1_OutOfRangeOutput;
		case UART_PEDALS_BRAKE_SENS_2_SHORT_TO_GND:
			return pedaleUart.Brake_Sensor2_ShortToGnd;
		case UART_PEDALS_BRAKE_SENS_2_SHORT_TO_VCC:
			return pedaleUart.Brake_Sensor2_ShortToVcc;
		case UART_PEDALS_BRAKE_SENS_2_OUT_OF_RANGE:
			return pedaleUart.Brake_Sensor2_OutOfRangeOutput;
		case UART_PEDALS_BRAKE_IMPLAUSIBILITY:
			return pedaleUart.Brake_Implausibility;
		case UART_INVERTERS_LEFT_INVERT_TEMP:
			return invertoareUart.LeftInverterTemperature;
		case UART_INVERTERS_LEFT_MOTOR_TEMP:
			return invertoareUart.LeftMotorTemperature;
		case UART_INVERTERS_LEFT_INVERTER_INPUT_VOLT:
			return invertoareUart.LeftInverterInputVoltage;
		case UART_INVERTERS_LEFT_INVERTER_AMPS:
			return invertoareUart.LeftInverterCurrent;
		case UART_INVERTERS_LEFT_MOTOR_RPM:
			return invertoareUart.LeftMotorRpm;
		case UART_INVERTERS_LEFT_MOTOR_KMH:
			return invertoareUart.LeftMotorSpeedKmh;
		case UART_INVERTERS_LEFT_INVERTER_THROTTLE:
			return invertoareUart.LeftInverterThrottle;
		case UART_INVERTERS_LEFT_INVERTER_THROTTLE_FEEDBACK:
			return invertoareUart.LeftInverterThrottleFeedback;
		case UART_INVERTERS_RIGHT_INVERTER_TEMP:
			return invertoareUart.RightInverterTemperature;
		case UART_INVERTERS_RIGHT_MOTOR_TEMP:
			return invertoareUart.RightMotorTemperature;
		case UART_INVERTERS_RIGHT_INVERTER_INPUT_VOLT:
			return invertoareUart.RightInverterInputVoltage;
		case UART_INVERTERS_RIGHT_INVERTER_AMPS:
			return invertoareUart.RightInverterCurrent;
		case UART_INVERTERS_RIGHT_MOTOR_RPM:
			return invertoareUart.RightMotorRpm;
		case UART_INVERTERS_RIGHT_MOTOR_KMH:
			return invertoareUart.RightMotorSpeedKmh;
		case UART_INVERTERS_RIGHT_INVERTER_THROTTLE:
			return invertoareUart.RightInverterSentThrottle;
		case UART_INVERTERS_RIGHT_INVERTER_THROTTLE_FEEDBACK:
			return invertoareUart.RightInverterThrottleFeedback;
		case UART_INVERTERS_IS_CAR_IN_REVERSE:
			return invertoareUart.IsCarInReverse;
		case UART_INVERTERS_IS_CAR_RUNNING:
			return invertoareUart.IsCarRunning;
		case UART_DASHBOARD_ACTIVATION_COMMAND:
			return bordUart.ActivationButtonPressed;
		case UART_DASHBOARD_CAR_REVERSE_COMMAND:
			return bordUart.CarReverseCommandPressed;
		case UART_DASHBOARD_IS_DISPLAY_WORKING:
			return bordUart.IsDisplayWorking;
		case UART_DASHBOARD_IS_SEGMENTS_DRIVER_WORKING:
			return bordUart.IsSegmentsDriverWorking;
	}
	return 0;
}*/

/*void UartMessaging_CreateBuffer(idUart_t type){
	switch(type){
		case ID_UART_INVERTOR_STANGA:
			bufferUart[0] = ID_UART_INVERTOR_STANGA;
			bufferUart[1] = UartMessaging_ReadValue(UART_INVERTERS_LEFT_MOTOR_RPM) >> 5;
			bufferUart[2] = (((UartMessaging_ReadValue(UART_INVERTERS_LEFT_MOTOR_RPM) & (0x001F) )) << 3) | ((UartMessaging_ReadValue(UART_INVERTERS_LEFT_INVERTER_INPUT_VOLT) & (0x0700)) >> 8);
			bufferUart[3] = ((uint8_t) UartMessaging_ReadValue(UART_INVERTERS_LEFT_INVERTER_INPUT_VOLT) & (0x00FF));
			bufferUart[4] = UartMessaging_ReadValue(UART_INVERTERS_LEFT_INVERTER_THROTTLE_FEEDBACK);
			bufferUart[5] = UartMessaging_ReadValue(UART_INVERTERS_LEFT_MOTOR_KMH);
			bufferUart[6] = UartMessaging_ReadValue(UART_INVERTERS_LEFT_INVERTER_THROTTLE);
			bufferUart[7] = UartMessaging_ReadValue(UART_INVERTERS_LEFT_INVERT_TEMP);
			bufferUart[8] = UartMessaging_ReadValue(UART_INVERTERS_LEFT_MOTOR_TEMP);
			bufferUart[9] = CRC_calculate(10);
			break;
		case ID_UART_INVERTOR_DREAPTA:
			bufferUart[0] = ID_UART_INVERTOR_DREAPTA;
			bufferUart[1] = UartMessaging_ReadValue(UART_INVERTERS_RIGHT_MOTOR_RPM) >> 5;
			bufferUart[2] = (((UartMessaging_ReadValue(UART_INVERTERS_RIGHT_MOTOR_RPM) & (0x001F) )) << 3) | ((UartMessaging_ReadValue(UART_INVERTERS_RIGHT_INVERTER_INPUT_VOLT) & (0x0700)) >> 8);
			bufferUart[3] = ((uint8_t) UartMessaging_ReadValue(UART_INVERTERS_RIGHT_INVERTER_INPUT_VOLT) & (0x7FF));
			bufferUart[4] = UartMessaging_ReadValue(UART_INVERTERS_RIGHT_INVERTER_THROTTLE_FEEDBACK);
			bufferUart[5] = UartMessaging_ReadValue(UART_INVERTERS_RIGHT_MOTOR_KMH);
			bufferUart[6] = UartMessaging_ReadValue(UART_INVERTERS_RIGHT_INVERTER_THROTTLE);
			bufferUart[7] = UartMessaging_ReadValue(UART_INVERTERS_RIGHT_INVERTER_TEMP);
			bufferUart[8] = UartMessaging_ReadValue(UART_INVERTERS_RIGHT_MOTOR_TEMP);
			bufferUart[9] = CRC_calculate(10);
			break;
		case ID_UART_INVERTOARE:
			bufferUart[0] = ID_UART_INVERTOARE;
			bufferUart[1] = (UartMessaging_ReadValue(UART_INVERTERS_IS_CAR_RUNNING) << 7) | (UartMessaging_ReadValue(UART_INVERTERS_IS_CAR_IN_REVERSE) << 6);
			bufferUart[2] = 0;
			bufferUart[3] = 0;
			bufferUart[4] = 0;
			bufferUart[5] = 0;
			bufferUart[6] = (UartMessaging_ReadValue(UART_INVERTERS_RIGHT_INVERTER_AMPS) & (0x0FF0)) >> 4;
			bufferUart[7] = ((UartMessaging_ReadValue(UART_INVERTERS_RIGHT_INVERTER_AMPS) & (0x000F)) << 4) | ((UartMessaging_ReadValue(UART_INVERTERS_LEFT_INVERTER_AMPS) & (0x0F00)) >> 8);
			bufferUart[8] = UartMessaging_ReadValue(UART_INVERTERS_LEFT_INVERTER_AMPS) & (0x00FF);
			bufferUart[9] = CRC_calculate(10);
			break;
		case ID_UART_BORD:
			bufferUart[0] = ID_UART_BORD;
			bufferUart[1] = (UartMessaging_ReadValue(UART_DASHBOARD_ACTIVATION_COMMAND) << 7) | (UartMessaging_ReadValue(UART_DASHBOARD_CAR_REVERSE_COMMAND) << 6) | (UartMessaging_ReadValue(UART_DASHBOARD_IS_DISPLAY_WORKING) << 5) | (UartMessaging_ReadValue(UART_DASHBOARD_IS_SEGMENTS_DRIVER_WORKING) << 4);
			bufferUart[2] = 0;
			bufferUart[3] = 0;
			bufferUart[4] = 0;
			bufferUart[5] = 0;
			bufferUart[6] = 0;
			bufferUart[7] = 0;
			bufferUart[8] = 0;
			bufferUart[9] = CRC_calculate(10);
			break;
		case ID_UART_ACCELERATIE:
			bufferUart[0] = ID_UART_ACCELERATIE;
			bufferUart[1] = (UartMessaging_ReadValue(UART_PEDALS_ACCEL_SENS_1_SHORT_TO_GND) << 7) | (UartMessaging_ReadValue(UART_PEDALS_ACCEL_SENS_1_SHORT_TO_VCC) << 6) | (UartMessaging_ReadValue(UART_PEDALS_ACCEL_SENS_1_OUT_OF_RANGE) << 5) | (UartMessaging_ReadValue(UART_PEDALS_ACCEL_SENS_2_SHORT_TO_GND) << 4) | (UartMessaging_ReadValue(UART_PEDALS_ACCEL_SENS_2_SHORT_TO_VCC) << 3) | (UartMessaging_ReadValue(UART_PEDALS_ACCEL_SENS_2_OUT_OF_RANGE) << 2) | (UartMessaging_ReadValue(UART_PEDALS_ACCEL_IMPLAUSIBILITY) << 1);
			bufferUart[2] = (UartMessaging_ReadValue(UART_PEDALS_PRESSURE_SENS_VOLT) & (0x01C0)) >> 6;
			bufferUart[3] = ((UartMessaging_ReadValue(UART_PEDALS_PRESSURE_SENS_VOLT) & (0x003F)) << 2) | ((UartMessaging_ReadValue(UART_PEDALS_ACCEL_SENS_2_TRAVEL_PERCENT) & (0x60)) >> 5);
			bufferUart[4] = ((UartMessaging_ReadValue(UART_PEDALS_ACCEL_SENS_2_TRAVEL_PERCENT) & (0x1F)) << 3) | ((UartMessaging_ReadValue(UART_PEDALS_ACCEL_SENS_1_TRAVEL_PERCENT) & (0x70)) >> 4);
			bufferUart[5] = ((UartMessaging_ReadValue(UART_PEDALS_ACCEL_SENS_1_TRAVEL_PERCENT) & (0x0F)) << 4) | ((UartMessaging_ReadValue(UART_PEDALS_ACCEL_SENS_2_VOLTAGE) & (0x3C00)) >> 10);
			bufferUart[6] = (UartMessaging_ReadValue(UART_PEDALS_ACCEL_SENS_2_VOLTAGE) & (0x03FC)) >> 2;
			bufferUart[7] = ((UartMessaging_ReadValue(UART_PEDALS_ACCEL_SENS_1_VOLTAGE) & (0x3F00)) >>8) | ((UartMessaging_ReadValue(UART_PEDALS_ACCEL_SENS_2_VOLTAGE) & (0x0003)) << 6);
			bufferUart[8] = UartMessaging_ReadValue(UART_PEDALS_ACCEL_SENS_1_VOLTAGE) & (0x00FF);
			bufferUart[9] = CRC_calculate(10);
			break;
		case ID_UART_FRANA:
			bufferUart[0] = ID_UART_FRANA;
			bufferUart[1] = (UartMessaging_ReadValue(UART_PEDALS_BRAKE_SENS_1_SHORT_TO_GND) << 7) | (UartMessaging_ReadValue(UART_PEDALS_BRAKE_SENS_1_SHORT_TO_VCC) << 6) | (UartMessaging_ReadValue(UART_PEDALS_BRAKE_SENS_1_OUT_OF_RANGE) << 5) | (UartMessaging_ReadValue(UART_PEDALS_BRAKE_SENS_2_SHORT_TO_GND) << 4) | (UartMessaging_ReadValue(UART_PEDALS_BRAKE_SENS_2_SHORT_TO_VCC) << 3) | (UartMessaging_ReadValue(UART_PEDALS_BRAKE_SENS_2_OUT_OF_RANGE) << 2) | (UartMessaging_ReadValue(UART_PEDALS_BRAKE_IMPLAUSIBILITY) << 1);
			bufferUart[2] = (UartMessaging_ReadValue(UART_PEDALS_PRESSURE_SENS_BARS) & (0xC0)) >> 6;
			bufferUart[3] = ((UartMessaging_ReadValue(UART_PEDALS_PRESSURE_SENS_BARS) & (0x3F)) << 2) | ((UartMessaging_ReadValue(UART_PEDALS_BRAKE_SENS_2_TRAVEL_PERCENT) & (0x60)) >> 5);
			bufferUart[4] = ((UartMessaging_ReadValue(UART_PEDALS_BRAKE_SENS_2_TRAVEL_PERCENT) & (0x1F)) << 3) | ((UartMessaging_ReadValue(UART_PEDALS_BRAKE_SENS_1_TRAVEL_PERCENT) & (0x70)) >> 4);
			bufferUart[5] = ((UartMessaging_ReadValue(UART_PEDALS_BRAKE_SENS_1_TRAVEL_PERCENT) & (0x0F)) << 4) | ((UartMessaging_ReadValue(UART_PEDALS_BRAKE_SENS_2_VOLT) & (0x3C00)) >> 10);
			bufferUart[6] = (UartMessaging_ReadValue(UART_PEDALS_BRAKE_SENS_2_VOLT) & (0x03FC)) >> 2;
			bufferUart[7] = ((UartMessaging_ReadValue(UART_PEDALS_BRAKE_SENS_1_VOLT) & (0x3F00)) >>8) | ((UartMessaging_ReadValue(UART_PEDALS_BRAKE_SENS_2_VOLT) & (0x0003)) << 6);
			bufferUart[8] = UartMessaging_ReadValue(UART_PEDALS_BRAKE_SENS_1_VOLT) & (0x00FF);
			bufferUart[9] = CRC_calculate(10);
			break;
		case ID_UART_BATERIE:
			bufferUart[0] = ID_UART_BATERIE;
			bufferUart[1] = 0;
			bufferUart[2] = 0;
			bufferUart[3] = (UartMessaging_ReadValue(UART_TSAC_HIGHEST_CELL_VOLT) & (0x03C0)) >> 6;
			bufferUart[4] = ((UartMessaging_ReadValue(UART_TSAC_HIGHEST_CELL_TEMP) & (0x0300)) >> 8) | ((UartMessaging_ReadValue(UART_TSAC_HIGHEST_CELL_VOLT) & (0x003F)) << 2);
			bufferUart[5] = UartMessaging_ReadValue(UART_TSAC_HIGHEST_CELL_TEMP) & (0x00FF);
			bufferUart[6] = (UartMessaging_ReadValue(UART_TSAC_OVERALL_VOLT) & (0x07F8)) >> 3;
			bufferUart[7] = ((UartMessaging_ReadValue(UART_TSAC_OVERALL_VOLT) & (0x0007)) << 5) | ((UartMessaging_ReadValue(UART_TSAC_OVERALL_AMPS) & (0x1F00)) >> 8);
			bufferUart[8] = UartMessaging_ReadValue(UART_TSAC_OVERALL_AMPS) & (0x00FF);
			bufferUart[9] = CRC_calculate(10);
			break;
		case ID_UART_BATERIE_TENSIUNI_CELULE:
			break;
		case ID_UART_BATERIE_TEMPERATURI_CELULE:
			break;
		case ID_UART_BATERIE_2:
			break;
		case ID_UART_BATERIE_CHARGER:
			break;
		case ID_UART_COMUNICATII:
			break;
		default:
			break;
	}
}*/

uint8_t CRC_calculate(uint8_t length){
	uint8_t crc=0, message[length];
	uint16_t divisor = 0x8D, dividend;
	int i, j;

	for(i=0; i<length-1; i++)
	{
		message[i] = bufferUart[i];
	}

	message[length-1]=0;

	dividend = (message[0] << 8) | message[1];
	for(j=15; j>=8; j--)
		if(dividend & (1 << j))
			dividend ^= divisor << (j-8);

	for(i=2; i<length; i++)
		{
			dividend = (dividend << 8) | message[i];

			for(j=15; j>=8; j--)
				if(dividend & (1 << j))
					dividend ^= divisor << (j-8);
		}

	crc = (dividend % 256);

	return crc;
}



#ifdef __cplusplus
}
#endif
