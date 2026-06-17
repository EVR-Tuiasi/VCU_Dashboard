
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
#include "Messaging.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
/*Takes a uint64_t argument and any xMonitoredValue_t type of argument.*/
#define ReadDataFromAddressAndWriteInRawBufferUart(rawBufferU64, xMonitoredValue_t_Address) \
		(rawBufferU64) |= (((xMonitoredValue_t_Address)->valueUart & (~(0xFFFFFFFFFFFFFFFF << (xMonitoredValue_t_Address)->nrOfBits))) << (xMonitoredValue_t_Address)->shift)

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/
static uint8_t bufferUart[10];

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
static uint8_t CRC_calculate(uint8_t length){
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

static void UartMessaging_CreateBuffer(MessageId_t type, uint8_t *buffer){
	uint64_t buffer_merged = 0;
	switch(type){
		case ID_CAN_INVERTOR_STANGA:
		case ID_UART_INVERTOR_STANGA:
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.InvertersMonitoredValues.LeftMotorTemperature);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.InvertersMonitoredValues.LeftInverterTemperature);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.InvertersMonitoredValues.LeftInverterThrottle);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.InvertersMonitoredValues.LeftMotorSpeedKmh);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.InvertersMonitoredValues.LeftInverterThrottleFeedback);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.InvertersMonitoredValues.LeftInverterInputVoltage);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.InvertersMonitoredValues.LeftMotorRpm);
			break;
		case ID_CAN_INVERTOR_DREAPTA:
		case ID_UART_INVERTOR_DREAPTA:
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.InvertersMonitoredValues.RightMotorTemperature);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.InvertersMonitoredValues.RightInverterTemperature);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.InvertersMonitoredValues.RightInverterThrottle);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.InvertersMonitoredValues.RightMotorSpeedKmh);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.InvertersMonitoredValues.RightInverterThrottleFeedback);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.InvertersMonitoredValues.RightInverterInputVoltage);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.InvertersMonitoredValues.RightMotorRpm);
			break;
		case ID_CAN_INVERTOARE:
		case ID_UART_INVERTOARE:
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.InvertersMonitoredValues.IsCarRunning);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.InvertersMonitoredValues.IsCarInReverse);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.InvertersMonitoredValues.LeftInverterCurrent);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.InvertersMonitoredValues.RightInverterCurrent);
			break;
		case ID_CAN_BORD:
		case ID_UART_BORD:
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.DashboardMonitoredValues.ActivationButtonPressed);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.DashboardMonitoredValues.CarReverseCommandPressed);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.DashboardMonitoredValues.IsDisplayWorking);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.DashboardMonitoredValues.IsSegmentsDriverWorking);
			break;
		case ID_CAN_ACCELERATIE:
		case ID_UART_ACCELERATIE:
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor1Voltage);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor2Voltage);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor1TravelPercentage);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor2TravelPercentage);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.PedalsMonitoredValues.PressureSensorVoltage);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Implausibility);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_OutOfRangeOutput);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToVcc);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToGnd);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_OutOfRangeOutput);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToVcc);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToGnd);
			break;
		case ID_CAN_FRANA:
		case ID_UART_FRANA:
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.PedalsMonitoredValues.BrakeSensor1Voltage);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.PedalsMonitoredValues.BrakeSensor2Voltage);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.PedalsMonitoredValues.BrakeSensor1TravelPercentage);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.PedalsMonitoredValues.BrakeSensor2TravelPercentage);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.PedalsMonitoredValues.PressureSensorBars);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Implausibility);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_OutOfRangeOutput);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToVcc);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToGnd);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_OutOfRangeOutput);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToVcc);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToGnd);
			break;
		case ID_CAN_BATERIE:
		case ID_UART_BATERIE:
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.TsacMonitoredValues.OverallCurrent);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.TsacMonitoredValues.OverallVoltage);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.TsacMonitoredValues.HighestCellTemperature);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.TsacMonitoredValues.HighestCellVoltage);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.TsacMonitoredValues.LowestCellVoltage);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.TsacMonitoredValues.LowestCellTemperature);
			break;
		case ID_CAN_BATERIE_2:
		case ID_UART_BATERIE_2:
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.TsacMonitoredValues.MedianCellTemperature);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.TsacMonitoredValues.MedianCellVoltage);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.TsacMonitoredValues.ShuntError);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.TsacMonitoredValues.TransceiverError);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.TsacMonitoredValues.Bms0Error);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.TsacMonitoredValues.Bms1Error);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.TsacMonitoredValues.ThermistorsError);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.TsacMonitoredValues.AmsError);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.TsacMonitoredValues.DesiredChargingCurrent);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.TsacMonitoredValues.DesiredChargingVoltage);
			break;
		case ID_CAN_BATERIE_CHARGER:
		case ID_UART_BATERIE_CHARGER:
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.TsacMonitoredValues.ReportedChargingCurrent);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.TsacMonitoredValues.ReportedChargingVolts);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.TsacMonitoredValues.ChargerCommand);
			break;
		case ID_CAN_COMUNICATII:
		case ID_UART_COMUNICATII:
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.CommunicationsMonitoredValues.IsDashboardVCUSimulated);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.CommunicationsMonitoredValues.IsInvertersVCUSimulated);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.CommunicationsMonitoredValues.IsPedalsVCUSimulated);
			ReadDataFromAddressAndWriteInRawBufferUart(buffer_merged, &MonitoredValues.CommunicationsMonitoredValues.IsTsacVCUSimulated);
			break;
		case ID_CAN_BATERIE_TENSIUNI_CELULE:
		case ID_UART_BATERIE_TENSIUNI_CELULE:
		case ID_CAN_BATERIE_TEMPERATURI_CELULE:
		case ID_UART_BATERIE_TEMPERATURI_CELULE:
		default:
			break;
	}
	buffer[0] = type;
	buffer[1] = (uint8_t)(buffer_merged << 56U);
	buffer[2] = (uint8_t)(buffer_merged << 48U);
	buffer[3] = (uint8_t)(buffer_merged << 40U);
	buffer[4] = (uint8_t)(buffer_merged << 32U);
	buffer[5] = (uint8_t)(buffer_merged << 24U);
	buffer[6] = (uint8_t)(buffer_merged << 16U);
	buffer[7] = (uint8_t)(buffer_merged << 8U);
	buffer[8] = (uint8_t)buffer_merged;
	buffer[9] = CRC_calculate(10);
}
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

void UartMessaging_Update(void){
	volatile int i;
	UartMessaging_CreateBuffer(ID_UART_INVERTOR_STANGA, bufferUart);
	Uart_SyncSend(UART_Channel, bufferUart, 10, 10000000);
	i=100000;
	while(i--);
	UartMessaging_CreateBuffer(ID_UART_INVERTOR_DREAPTA, bufferUart);
	Uart_SyncSend(UART_Channel, bufferUart, 10, 10000000);
	i=100000;
	while(i--);
	UartMessaging_CreateBuffer(ID_UART_INVERTOARE, bufferUart);
	Uart_SyncSend(UART_Channel, bufferUart, 10, 10000000);
	i=100000;
	while(i--);
	UartMessaging_CreateBuffer(ID_UART_BORD, bufferUart);
	Uart_SyncSend(UART_Channel, bufferUart, 10, 10000000);
	i=100000;
	while(i--);
	UartMessaging_CreateBuffer(ID_UART_ACCELERATIE, bufferUart);
	Uart_SyncSend(UART_Channel, bufferUart, 10, 10000000);
	i=100000;
	while(i--);
	UartMessaging_CreateBuffer(ID_UART_FRANA, bufferUart);
	Uart_SyncSend(UART_Channel, bufferUart, 10, 10000000);
	i=100000;
	while(i--);
	UartMessaging_CreateBuffer(ID_UART_BATERIE, bufferUart);
	Uart_SyncSend(UART_Channel, bufferUart, 10, 10000000);
	i=100000;
	while(i--);
}

#ifdef __cplusplus
}
#endif
