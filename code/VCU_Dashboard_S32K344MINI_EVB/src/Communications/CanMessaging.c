
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
#include "CanMessaging.h"
#include "Messaging.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
#define ID_MASK 			0x3FFFFFFF
#define SEND_MASK 			0x80000000
#define CAN_HTH_HANDLE  	0x00000001
#define CAN_CONTROLLER_ID_1	0U
#define CAN_CONTROLLER_ID_2	1U

#define CAN_CHANNEL_1_EN 	88U
#define CAN_CHANNEL_1_STB_N 85U
#define CAN_CHANNEL_2_EN 	119U
#define CAN_CHANNEL_2_STB_N 98U

/*Takes a uint64_t argument and any xMonitoredValue_t type of argument.*/
#define ReadDataFromAddressAndWriteInRawBufferCan(rawBufferU64, xMonitoredValue_t_Address) \
		(rawBufferU64) |= (((xMonitoredValue_t_Address)->valueCan & (~(0xFFFFFFFFFFFFFFFF << (xMonitoredValue_t_Address)->nrOfBits))) << (xMonitoredValue_t_Address)->shift)
/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/
static uint8_t bufferCan[8];

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
boolean CanMessaging_ReceiveData(Can_HwHandleType handle, Can_IdType id, PduLengthType length, uint8_t* data){
	(void)(handle);	/*This is here to suppress warnings about unused parameter*/
	(void)(length);	/*This is here to suppress warnings about unused parameter*/
	uint64_t data_merged;
	data_merged = (((uint64_t)data[0]) << 56) + (((uint64_t)data[1]) << 48) + (((uint64_t)data[2]) << 40) + (((uint64_t)data[3]) << 32) + (((uint64_t)data[4]) << 24) + (((uint64_t)data[5]) << 16) + (((uint64_t)data[6]) << 8) + (uint64_t)data[7];
	switch((id&ID_MASK)){
		case ID_CAN_FRANA:
			//extragere date
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.BrakeSensor1Voltage);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.BrakeSensor2Voltage);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.BrakeSensor1TravelPercentage);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.BrakeSensor2TravelPercentage);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.PressureSensorBars);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Implausibility);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_OutOfRangeOutput);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToVcc);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToGnd);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_OutOfRangeOutput);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToVcc);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToGnd);
			break;

		case ID_CAN_ACCELERATIE:
			//extragere date
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor1Voltage);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor2Voltage);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor1TravelPercentage);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor2TravelPercentage);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.PressureSensorVoltage);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Implausibility);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_OutOfRangeOutput);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToVcc);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToGnd);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_OutOfRangeOutput);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToVcc);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToGnd);
			break;

		case ID_CAN_INVERTOR_STANGA:
			//extragere date
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.LeftMotorTemperature);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.LeftInverterTemperature);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.LeftInverterThrottle);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.LeftMotorSpeedKmh);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.LeftInverterThrottleFeedback);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.LeftInverterInputVoltage);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.LeftMotorRpm);
			break;

		case ID_CAN_INVERTOR_DREAPTA:
			//extragere date
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.RightMotorTemperature);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.RightInverterTemperature);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.RightInverterThrottle);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.RightMotorSpeedKmh);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.RightInverterThrottleFeedback);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.RightInverterInputVoltage);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.RightMotorRpm);
			break;

		case ID_CAN_INVERTOARE:
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.IsCarRunning);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.IsCarInReverse);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.LeftInverterCurrent);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.RightInverterCurrent);
			break;

		case ID_CAN_BATERIE:
			//extragere date
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.OverallCurrent);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.OverallVoltage);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.HighestCellTemperature);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.HighestCellVoltage);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.LowestCellVoltage);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.LowestCellTemperature);
			break;
		case ID_CAN_BATERIE_2:
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.MedianCellTemperature);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.MedianCellVoltage);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.ShuntError);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.TransceiverError);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.Bms0Error);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.Bms1Error);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.ThermistorsError);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.AmsError);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.DesiredChargingCurrent);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.DesiredChargingVoltage);
			break;
		case ID_CAN_BORD:
			//extragere date
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.DashboardMonitoredValues.ActivationButtonPressed);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.DashboardMonitoredValues.CarReverseCommandPressed);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.DashboardMonitoredValues.IsDisplayWorking);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.DashboardMonitoredValues.IsSegmentsDriverWorking);
			break;
		case ID_CAN_COMUNICATII:
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.CommunicationsMonitoredValues.IsInvertersVCUSimulated);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.CommunicationsMonitoredValues.IsTsacVCUSimulated);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.CommunicationsMonitoredValues.IsDashboardVCUSimulated);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.CommunicationsMonitoredValues.IsPedalsVCUSimulated);
			break;
		case ID_CAN_BATERIE_CHARGER:
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.ReportedChargingCurrent);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.ReportedChargingVolts);
			WriteDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.ChargerCommand);
			break;
		default:
			return FALSE;
	}
	return TRUE;
}

static void CanMessaging_CreateBuffer(MessageId_t type, uint8_t *buffer){
	uint64_t buffer_merged = 0;
	switch(type){
		case ID_CAN_INVERTOR_STANGA:
		case ID_UART_INVERTOR_STANGA:
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.InvertersMonitoredValues.LeftMotorTemperature);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.InvertersMonitoredValues.LeftInverterTemperature);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.InvertersMonitoredValues.LeftInverterThrottle);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.InvertersMonitoredValues.LeftMotorSpeedKmh);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.InvertersMonitoredValues.LeftInverterThrottleFeedback);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.InvertersMonitoredValues.LeftInverterInputVoltage);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.InvertersMonitoredValues.LeftMotorRpm);
			break;
		case ID_CAN_INVERTOR_DREAPTA:
		case ID_UART_INVERTOR_DREAPTA:
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.InvertersMonitoredValues.RightMotorTemperature);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.InvertersMonitoredValues.RightInverterTemperature);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.InvertersMonitoredValues.RightInverterThrottle);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.InvertersMonitoredValues.RightMotorSpeedKmh);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.InvertersMonitoredValues.RightInverterThrottleFeedback);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.InvertersMonitoredValues.RightInverterInputVoltage);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.InvertersMonitoredValues.RightMotorRpm);
			break;
		case ID_CAN_INVERTOARE:
		case ID_UART_INVERTOARE:
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.InvertersMonitoredValues.IsCarRunning);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.InvertersMonitoredValues.IsCarInReverse);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.InvertersMonitoredValues.LeftInverterCurrent);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.InvertersMonitoredValues.RightInverterCurrent);
			break;
		case ID_CAN_BORD:
		case ID_UART_BORD:
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.DashboardMonitoredValues.ActivationButtonPressed);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.DashboardMonitoredValues.CarReverseCommandPressed);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.DashboardMonitoredValues.IsDisplayWorking);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.DashboardMonitoredValues.IsSegmentsDriverWorking);
			break;
		case ID_CAN_ACCELERATIE:
		case ID_UART_ACCELERATIE:
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor1Voltage);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor2Voltage);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor1TravelPercentage);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor2TravelPercentage);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.PedalsMonitoredValues.PressureSensorVoltage);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Implausibility);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_OutOfRangeOutput);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToVcc);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToGnd);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_OutOfRangeOutput);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToVcc);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToGnd);
			break;
		case ID_CAN_FRANA:
		case ID_UART_FRANA:
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.PedalsMonitoredValues.BrakeSensor1Voltage);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.PedalsMonitoredValues.BrakeSensor2Voltage);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.PedalsMonitoredValues.BrakeSensor1TravelPercentage);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.PedalsMonitoredValues.BrakeSensor2TravelPercentage);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.PedalsMonitoredValues.PressureSensorBars);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Implausibility);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_OutOfRangeOutput);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToVcc);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToGnd);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_OutOfRangeOutput);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToVcc);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToGnd);
			break;
		case ID_CAN_BATERIE:
		case ID_UART_BATERIE:
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.TsacMonitoredValues.OverallCurrent);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.TsacMonitoredValues.OverallVoltage);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.TsacMonitoredValues.HighestCellTemperature);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.TsacMonitoredValues.HighestCellVoltage);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.TsacMonitoredValues.LowestCellVoltage);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.TsacMonitoredValues.LowestCellTemperature);
			break;
		case ID_CAN_BATERIE_2:
		case ID_UART_BATERIE_2:
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.TsacMonitoredValues.MedianCellTemperature);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.TsacMonitoredValues.MedianCellVoltage);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.TsacMonitoredValues.ShuntError);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.TsacMonitoredValues.TransceiverError);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.TsacMonitoredValues.Bms0Error);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.TsacMonitoredValues.Bms1Error);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.TsacMonitoredValues.ThermistorsError);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.TsacMonitoredValues.AmsError);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.TsacMonitoredValues.DesiredChargingCurrent);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.TsacMonitoredValues.DesiredChargingVoltage);
			break;
		case ID_CAN_BATERIE_CHARGER:
		case ID_UART_BATERIE_CHARGER:
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.TsacMonitoredValues.ReportedChargingCurrent);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.TsacMonitoredValues.ReportedChargingVolts);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.TsacMonitoredValues.ChargerCommand);
			break;
		case ID_CAN_COMUNICATII:
		case ID_UART_COMUNICATII:
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.CommunicationsMonitoredValues.IsDashboardVCUSimulated);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.CommunicationsMonitoredValues.IsInvertersVCUSimulated);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.CommunicationsMonitoredValues.IsPedalsVCUSimulated);
			ReadDataFromAddressAndWriteInRawBufferCan(buffer_merged, &MonitoredValues.CommunicationsMonitoredValues.IsTsacVCUSimulated);
			break;
		case ID_CAN_BATERIE_TENSIUNI_CELULE:
		case ID_UART_BATERIE_TENSIUNI_CELULE:
		case ID_CAN_BATERIE_TEMPERATURI_CELULE:
		case ID_UART_BATERIE_TEMPERATURI_CELULE:
		default:
			break;
	}
	buffer[0] = (uint8_t)(buffer_merged << 56U);
	buffer[1] = (uint8_t)(buffer_merged << 48U);
	buffer[2] = (uint8_t)(buffer_merged << 40U);
	buffer[3] = (uint8_t)(buffer_merged << 32U);
	buffer[4] = (uint8_t)(buffer_merged << 24U);
	buffer[5] = (uint8_t)(buffer_merged << 16U);
	buffer[6] = (uint8_t)(buffer_merged << 8U);
	buffer[7] = (uint8_t)buffer_merged;
}
/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

void CanMessaging_Init(void){
	Dio_WriteChannel(88, STD_HIGH); //CAN0_EN
	volatile uint64 i = 1000000;
	while(i--);
	Dio_WriteChannel(85, STD_HIGH); //CAN0_STB_N
	i = 1000000;
	while(i--);
	Dio_WriteChannel(119, STD_HIGH); //CAN1_EN
	i = 1000000;
	while(i--);
	Dio_WriteChannel(98, STD_HIGH); //CAN1_STB_N
	i = 1000000;
	while(i--);

	Can_43_FLEXCAN_SetControllerMode(CAN_CONTROLLER_ID_1, CAN_CS_STARTED);
	//Can_43_FLEXCAN_SetControllerMode(CAN_CONTROLLER_ID_2, CAN_CS_STARTED);
	Can_43_FLEXCAN_EnableControllerInterrupts(CAN_CONTROLLER_ID_1);
	//Can_43_FLEXCAN_EnableControllerInterrupts(CAN_CONTROLLER_ID_2);
}

void CanMessaging_Test(void){
	uint64_t cnt = 0;
	volatile int i;
	while(1){
		WriteDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.MedianCellTemperature);
		WriteDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.HighestCellTemperature);
		WriteDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.LowestCellTemperature);
		WriteDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.MedianCellVoltage);
		WriteDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.HighestCellVoltage);
		WriteDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.LowestCellVoltage);
		WriteDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.OverallVoltage);
		WriteDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.OverallCurrent);

		WriteDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.AmsError);
		WriteDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.TransceiverError);
		WriteDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.ShuntError);
		WriteDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.Bms0Error);
		WriteDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.Bms1Error);

		WriteDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor1Voltage);
		WriteDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor2Voltage);
		WriteDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor1TravelPercentage);
		WriteDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor2TravelPercentage);
		WriteDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.BrakeSensor1Voltage);
		WriteDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.BrakeSensor2Voltage);
		WriteDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.BrakeSensor1TravelPercentage);
		WriteDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.BrakeSensor2TravelPercentage);
		WriteDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.PressureSensorVoltage);
		WriteDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.PressureSensorBars);
		WriteDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToGnd);
		WriteDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToVcc);
		WriteDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_OutOfRangeOutput);
		WriteDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToGnd);
		WriteDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToVcc);
		WriteDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_OutOfRangeOutput);
		WriteDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Accel_Implausibility);
		WriteDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToGnd);
		WriteDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToVcc);
		WriteDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_OutOfRangeOutput);
		WriteDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToGnd);
		WriteDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToVcc);
		WriteDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_OutOfRangeOutput);
		WriteDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Brake_Implausibility);

		WriteDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.LeftInverterTemperature);
		WriteDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.LeftMotorTemperature);
		WriteDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.LeftInverterInputVoltage);
		WriteDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.LeftInverterCurrent);
		WriteDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.LeftMotorRpm);
		WriteDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.LeftMotorSpeedKmh);
		WriteDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.LeftInverterThrottle);
		WriteDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.LeftInverterThrottleFeedback);
		WriteDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.RightInverterTemperature);
		WriteDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.RightMotorTemperature);
		WriteDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.RightInverterInputVoltage);
		WriteDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.RightInverterCurrent);
		WriteDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.RightMotorRpm);
		WriteDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.RightMotorSpeedKmh);
		WriteDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.RightInverterThrottle);
		WriteDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.RightInverterThrottleFeedback);
		WriteDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.IsCarInReverse);
		WriteDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.IsCarRunning);

		WriteDataAtAddress(cnt, &MonitoredValues.DashboardMonitoredValues.ActivationButtonPressed);
		WriteDataAtAddress(cnt, &MonitoredValues.DashboardMonitoredValues.CarReverseCommandPressed);
		WriteDataAtAddress(cnt, &MonitoredValues.DashboardMonitoredValues.IsDisplayWorking);
		WriteDataAtAddress(cnt, &MonitoredValues.DashboardMonitoredValues.IsSegmentsDriverWorking);

		cnt++;
		CanMessaging_Update();
		i=100000;
		while(i--);
	}
}

void CanMessaging_Update(void){

	Can_PduType pduInfo;
	pduInfo.swPduHandle=0;
	pduInfo.length=8;

	CanMessaging_CreateBuffer(ID_CAN_INVERTOR_STANGA, bufferCan);
	pduInfo.sdu=bufferCan;
	pduInfo.id=ID_CAN_INVERTOR_STANGA | SEND_MASK;
	Can_43_FLEXCAN_Write(CAN_HTH_HANDLE, &pduInfo);

	CanMessaging_CreateBuffer(ID_CAN_INVERTOR_DREAPTA, bufferCan);
	pduInfo.sdu=bufferCan;
	pduInfo.id=ID_CAN_INVERTOR_DREAPTA | SEND_MASK;
	Can_43_FLEXCAN_Write(CAN_HTH_HANDLE, &pduInfo);

	CanMessaging_CreateBuffer(ID_CAN_INVERTOARE, bufferCan);
	pduInfo.sdu=bufferCan;
	pduInfo.id=ID_CAN_INVERTOARE | SEND_MASK;
	Can_43_FLEXCAN_Write(CAN_HTH_HANDLE, &pduInfo);

	CanMessaging_CreateBuffer(ID_CAN_BORD, bufferCan);
	pduInfo.sdu=bufferCan;
	pduInfo.id=ID_CAN_BORD | SEND_MASK;
	Can_43_FLEXCAN_Write(CAN_HTH_HANDLE, &pduInfo);

	CanMessaging_CreateBuffer(ID_CAN_ACCELERATIE, bufferCan);
	pduInfo.sdu=bufferCan;
	pduInfo.id=ID_CAN_ACCELERATIE | SEND_MASK;
	Can_43_FLEXCAN_Write(CAN_HTH_HANDLE, &pduInfo);

	CanMessaging_CreateBuffer(ID_CAN_FRANA, bufferCan);
	pduInfo.sdu=bufferCan;
	pduInfo.id=ID_CAN_FRANA | SEND_MASK;
	Can_43_FLEXCAN_Write(CAN_HTH_HANDLE, &pduInfo);

	CanMessaging_CreateBuffer(ID_CAN_BATERIE, bufferCan);
	pduInfo.sdu=bufferCan;
	pduInfo.id=ID_CAN_BATERIE | SEND_MASK;
	Can_43_FLEXCAN_Write(CAN_HTH_HANDLE, &pduInfo);
}


/*
void CanMessaging_AppTest(void){
	while(1){
		//Brake
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_1_VOLT, ReadDataFromAddress(&MonitoredValues.PedalsMonitoredValues.BrakeSensor1Voltage));
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_2_VOLT, ReadDataFromAddress(&MonitoredValues.PedalsMonitoredValues.BrakeSensor2Voltage));
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_1_TRAVEL_PERCENT, ReadDataFromAddress(&MonitoredValues.PedalsMonitoredValues.BrakeSensor1TravelPercentage));
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_2_TRAVEL_PERCENT, ReadDataFromAddress(&MonitoredValues.PedalsMonitoredValues.BrakeSensor2TravelPercentage));
		UartMessaging_SetValue(UART_PEDALS_PRESSURE_SENS_BARS, ReadDataFromAddress(&MonitoredValues.PedalsMonitoredValues.PressureSensorBars));
		UartMessaging_SetValue(UART_PEDALS_BRAKE_IMPLAUSIBILITY, ReadDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Brake_Implausibility));
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_1_OUT_OF_RANGE, ReadDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_OutOfRangeOutput));
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_1_SHORT_TO_VCC, ReadDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToVcc));
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_1_SHORT_TO_GND, ReadDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToGnd));
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_2_OUT_OF_RANGE, ReadDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_OutOfRangeOutput));
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_2_SHORT_TO_VCC, ReadDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToVcc));
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_2_SHORT_TO_GND, ReadDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToGnd));

		//Acclelerator
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_1_VOLTAGE, ReadDataFromAddress(&MonitoredValues.PedalsMonitoredValues.AcceleratorSensor1Voltage));
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_2_VOLTAGE, ReadDataFromAddress(&MonitoredValues.PedalsMonitoredValues.AcceleratorSensor2Voltage));
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_1_TRAVEL_PERCENT, ReadDataFromAddress(&MonitoredValues.PedalsMonitoredValues.AcceleratorSensor1TravelPercentage));
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_2_TRAVEL_PERCENT, ReadDataFromAddress(&MonitoredValues.PedalsMonitoredValues.AcceleratorSensor2TravelPercentage));
		UartMessaging_SetValue(UART_PEDALS_PRESSURE_SENS_VOLT, ReadDataFromAddress(&MonitoredValues.PedalsMonitoredValues.PressureSensorVoltage));
		UartMessaging_SetValue(UART_PEDALS_ACCEL_IMPLAUSIBILITY, ReadDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Accel_Implausibility));
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_1_OUT_OF_RANGE, ReadDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_OutOfRangeOutput));
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_1_SHORT_TO_VCC, ReadDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToVcc));
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_1_SHORT_TO_GND, ReadDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToGnd));
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_2_OUT_OF_RANGE, ReadDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_OutOfRangeOutput));
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_2_SHORT_TO_VCC, ReadDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToVcc));
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_2_SHORT_TO_GND, ReadDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToGnd));

		//Left Inverters
		UartMessaging_SetValue(UART_INVERTERS_LEFT_MOTOR_TEMP, ReadDataFromAddress(&MonitoredValues.InvertersMonitoredValues.LeftMotorTemperature));
		UartMessaging_SetValue(UART_INVERTERS_LEFT_INVERT_TEMP, ReadDataFromAddress(&MonitoredValues.InvertersMonitoredValues.LeftInverterTemperature));
		UartMessaging_SetValue(UART_INVERTERS_LEFT_INVERTER_THROTTLE, ReadDataFromAddress(&MonitoredValues.InvertersMonitoredValues.LeftInverterThrottle));
		UartMessaging_SetValue(UART_INVERTERS_LEFT_MOTOR_KMH, ReadDataFromAddress(&MonitoredValues.InvertersMonitoredValues.LeftMotorSpeedKmh));
		UartMessaging_SetValue(UART_INVERTERS_LEFT_INVERTER_THROTTLE_FEEDBACK, ReadDataFromAddress(&MonitoredValues.InvertersMonitoredValues.LeftInverterThrottleFeedback));
		UartMessaging_SetValue(UART_INVERTERS_LEFT_INVERTER_INPUT_VOLT, ReadDataFromAddress(&MonitoredValues.InvertersMonitoredValues.LeftInverterInputVoltage));
		UartMessaging_SetValue(UART_INVERTERS_LEFT_MOTOR_RPM, ReadDataFromAddress(&MonitoredValues.InvertersMonitoredValues.LeftMotorRpm));

		//Right Inverters
		UartMessaging_SetValue(UART_INVERTERS_RIGHT_MOTOR_TEMP, ReadDataFromAddress(&MonitoredValues.InvertersMonitoredValues.RightMotorTemperature));
		UartMessaging_SetValue(UART_INVERTERS_RIGHT_INVERTER_TEMP, ReadDataFromAddress(&MonitoredValues.InvertersMonitoredValues.RightInverterTemperature));
		UartMessaging_SetValue(UART_INVERTERS_RIGHT_INVERTER_THROTTLE, ReadDataFromAddress(&MonitoredValues.InvertersMonitoredValues.RightInverterThrottle));
		UartMessaging_SetValue(UART_INVERTERS_RIGHT_MOTOR_KMH, ReadDataFromAddress(&MonitoredValues.InvertersMonitoredValues.RightMotorSpeedKmh));
		UartMessaging_SetValue(UART_INVERTERS_RIGHT_INVERTER_THROTTLE_FEEDBACK, ReadDataFromAddress(&MonitoredValues.InvertersMonitoredValues.RightInverterThrottleFeedback));
		UartMessaging_SetValue(UART_INVERTERS_RIGHT_INVERTER_INPUT_VOLT, ReadDataFromAddress(&MonitoredValues.InvertersMonitoredValues.RightInverterInputVoltage));
		UartMessaging_SetValue(UART_INVERTERS_RIGHT_MOTOR_RPM, ReadDataFromAddress(&MonitoredValues.InvertersMonitoredValues.RightMotorRpm));

		//Inverters
		UartMessaging_SetValue(UART_INVERTERS_IS_CAR_RUNNING, ReadDataFromAddress(&MonitoredValues.InvertersMonitoredValues.IsCarRunning));
		UartMessaging_SetValue(UART_INVERTERS_IS_CAR_IN_REVERSE, ReadDataFromAddress(&MonitoredValues.InvertersMonitoredValues.IsCarInReverse));
		UartMessaging_SetValue(UART_INVERTERS_LEFT_INVERTER_AMPS, ReadDataFromAddress(&MonitoredValues.InvertersMonitoredValues.LeftInverterCurrent));
		UartMessaging_SetValue(UART_INVERTERS_RIGHT_INVERTER_AMPS, ReadDataFromAddress(&MonitoredValues.InvertersMonitoredValues.RightInverterCurrent));

		//TSAC
		UartMessaging_SetValue(UART_TSAC_OVERALL_AMPS, ReadDataFromAddress(&MonitoredValues.TsacMonitoredValues.OverallCurrent));
		UartMessaging_SetValue(UART_TSAC_OVERALL_VOLT, ReadDataFromAddress(&MonitoredValues.TsacMonitoredValues.OverallVoltage));
		UartMessaging_SetValue(UART_TSAC_HIGHEST_CELL_TEMP, ReadDataFromAddress(&MonitoredValues.TsacMonitoredValues.HighestCellTemperature));
		UartMessaging_SetValue(UART_TSAC_HIGHEST_CELL_VOLT, ReadDataFromAddress(&MonitoredValues.TsacMonitoredValues.HighestCellVoltage));

		//Dashboard
		UartMessaging_SetValue(UART_DASHBOARD_ACTIVATION_COMMAND, ReadDataFromAddress(&MonitoredValues.DashboardMonitoredValues.ActivationButtonPressed));
		UartMessaging_SetValue(UART_DASHBOARD_CAR_REVERSE_COMMAND, ReadDataFromAddress(&MonitoredValues.DashboardMonitoredValues.CarReverseCommandPressed));
		UartMessaging_SetValue(UART_DASHBOARD_IS_DISPLAY_WORKING, ReadDataFromAddress(&MonitoredValues.DashboardMonitoredValues.IsDisplayWorking));
		UartMessaging_SetValue(UART_DASHBOARD_IS_SEGMENTS_DRIVER_WORKING, ReadDataFromAddress(&MonitoredValues.DashboardMonitoredValues.IsSegmentsDriverWorking));

		//Send data
		//UartMessaging_Update();
	}
}*/

#ifdef __cplusplus
}
#endif
