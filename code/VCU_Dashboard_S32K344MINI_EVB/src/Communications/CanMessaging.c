
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
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.BrakeSensor1Voltage);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.BrakeSensor2Voltage);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.BrakeSensor2Voltage);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.BrakeSensor2Voltage);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.BrakeSensor1TravelPercentage);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.BrakeSensor2TravelPercentage);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.PressureSensorBars);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Implausibility);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_OutOfRangeOutput);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToVcc);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToGnd);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_OutOfRangeOutput);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToVcc);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToGnd);
			break;

		case ID_CAN_ACCELERATIE:
			//extragere date
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor1Voltage);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor2Voltage);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor1TravelPercentage);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor2TravelPercentage);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.PressureSensorVoltage);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Implausibility);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_OutOfRangeOutput);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToVcc);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToGnd);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_OutOfRangeOutput);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToVcc);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToGnd);
			break;

		case ID_CAN_INVERTOR_STANGA:
			//extragere date
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.LeftMotorTemperature);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.LeftInverterTemperature);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.LeftInverterThrottle);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.LeftMotorSpeedKmh);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.LeftInverterThrottleFeedback);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.LeftInverterInputVoltage);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.LeftMotorRpm);
			break;

		case ID_CAN_INVERTOR_DREAPTA:
			//extragere date
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.RightMotorTemperature);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.RightInverterTemperature);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.RightInverterThrottle);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.RightMotorSpeedKmh);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.RightInverterThrottleFeedback);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.RightInverterInputVoltage);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.RightMotorRpm);
			break;

		case ID_CAN_INVERTOARE:
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.IsCarRunning);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.IsCarInReverse);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.LeftInverterCurrent);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.InvertersMonitoredValues.RightInverterCurrent);
			break;

		case ID_CAN_BATERIE:
			//extragere date
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.OverallCurrent);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.OverallVoltage);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.HighestCellTemperature);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.HighestCellVoltage);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.LowestCellVoltage);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.LowestCellTemperature);
			break;
		case ID_CAN_BATERIE_2:
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.MedianCellTemperature);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.MedianCellVoltage);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.ShuntError);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.TransceiverError);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.Bms0Error);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.Bms1Error);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.ThermistorsError);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.AmsError);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.DesiredChargingCurrent);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.DesiredChargingVoltage);
			break;
		case ID_CAN_BORD:
			//extragere date
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.DashboardMonitoredValues.ActivationButtonPressed);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.DashboardMonitoredValues.CarReverseCommandPressed);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.DashboardMonitoredValues.IsDisplayWorking);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.DashboardMonitoredValues.IsSegmentsDriverWorking);
			break;
		case ID_CAN_COMUNICATII:
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.CommunicationsMonitoredValues.IsInvertersVCUSimulated);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.CommunicationsMonitoredValues.IsTsacVCUSimulated);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.CommunicationsMonitoredValues.IsDashboardVCUSimulated);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.CommunicationsMonitoredValues.IsPedalsVCUSimulated);
			break;
		case ID_CAN_BATERIE_CHARGER:
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.ReportedChargingCurrent);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.ReportedChargingVolts);
			WriteCanDataFromRawBufferAtAddress(data_merged, &MonitoredValues.TsacMonitoredValues.ChargerCommand);
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
		WriteCanDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.MedianCellTemperature);
		WriteCanDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.HighestCellTemperature);
		WriteCanDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.LowestCellTemperature);
		WriteCanDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.MedianCellVoltage);
		WriteCanDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.HighestCellVoltage);
		WriteCanDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.LowestCellVoltage);
		WriteCanDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.OverallVoltage);
		WriteCanDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.OverallCurrent);

		WriteCanDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.AmsError);
		WriteCanDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.TransceiverError);
		WriteCanDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.ShuntError);
		WriteCanDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.Bms0Error);
		WriteCanDataAtAddress(cnt, &MonitoredValues.TsacMonitoredValues.Bms1Error);

		WriteCanDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor1Voltage);
		WriteCanDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor2Voltage);
		WriteCanDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor1TravelPercentage);
		WriteCanDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor2TravelPercentage);
		WriteCanDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.BrakeSensor1Voltage);
		WriteCanDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.BrakeSensor2Voltage);
		WriteCanDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.BrakeSensor1TravelPercentage);
		WriteCanDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.BrakeSensor2TravelPercentage);
		WriteCanDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.PressureSensorVoltage);
		WriteCanDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.PressureSensorBars);
		WriteCanDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToGnd);
		WriteCanDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToVcc);
		WriteCanDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_OutOfRangeOutput);
		WriteCanDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToGnd);
		WriteCanDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToVcc);
		WriteCanDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_OutOfRangeOutput);
		WriteCanDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Accel_Implausibility);
		WriteCanDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToGnd);
		WriteCanDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToVcc);
		WriteCanDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_OutOfRangeOutput);
		WriteCanDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToGnd);
		WriteCanDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToVcc);
		WriteCanDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_OutOfRangeOutput);
		WriteCanDataAtAddress(cnt, &MonitoredValues.PedalsMonitoredValues.Brake_Implausibility);

		WriteCanDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.LeftInverterTemperature);
		WriteCanDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.LeftMotorTemperature);
		WriteCanDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.LeftInverterInputVoltage);
		WriteCanDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.LeftInverterCurrent);
		WriteCanDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.LeftMotorRpm);
		WriteCanDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.LeftMotorSpeedKmh);
		WriteCanDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.LeftInverterThrottle);
		WriteCanDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.LeftInverterThrottleFeedback);
		WriteCanDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.RightInverterTemperature);
		WriteCanDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.RightMotorTemperature);
		WriteCanDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.RightInverterInputVoltage);
		WriteCanDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.RightInverterCurrent);
		WriteCanDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.RightMotorRpm);
		WriteCanDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.RightMotorSpeedKmh);
		WriteCanDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.RightInverterThrottle);
		WriteCanDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.RightInverterThrottleFeedback);
		WriteCanDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.IsCarInReverse);
		WriteCanDataAtAddress(cnt, &MonitoredValues.InvertersMonitoredValues.IsCarRunning);

		WriteCanDataAtAddress(cnt, &MonitoredValues.DashboardMonitoredValues.ActivationButtonPressed);
		WriteCanDataAtAddress(cnt, &MonitoredValues.DashboardMonitoredValues.CarReverseCommandPressed);
		WriteCanDataAtAddress(cnt, &MonitoredValues.DashboardMonitoredValues.IsDisplayWorking);
		WriteCanDataAtAddress(cnt, &MonitoredValues.DashboardMonitoredValues.IsSegmentsDriverWorking);

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


void CanMessaging_AppTest(void){
	while(1){
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.TsacMonitoredValues.MedianCellTemperature), &MonitoredValues.TsacMonitoredValues.MedianCellTemperature);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.TsacMonitoredValues.HighestCellTemperature), &MonitoredValues.TsacMonitoredValues.HighestCellTemperature);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.TsacMonitoredValues.LowestCellTemperature), &MonitoredValues.TsacMonitoredValues.LowestCellTemperature);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.TsacMonitoredValues.MedianCellVoltage), &MonitoredValues.TsacMonitoredValues.MedianCellVoltage);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.TsacMonitoredValues.HighestCellVoltage), &MonitoredValues.TsacMonitoredValues.HighestCellVoltage);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.TsacMonitoredValues.LowestCellVoltage), &MonitoredValues.TsacMonitoredValues.LowestCellVoltage);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.TsacMonitoredValues.OverallVoltage), &MonitoredValues.TsacMonitoredValues.OverallVoltage);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.TsacMonitoredValues.OverallCurrent), &MonitoredValues.TsacMonitoredValues.OverallCurrent);

		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.TsacMonitoredValues.AmsError), &MonitoredValues.TsacMonitoredValues.AmsError);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.TsacMonitoredValues.TransceiverError), &MonitoredValues.TsacMonitoredValues.TransceiverError);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.TsacMonitoredValues.ShuntError), &MonitoredValues.TsacMonitoredValues.ShuntError);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.TsacMonitoredValues.Bms0Error), &MonitoredValues.TsacMonitoredValues.Bms0Error);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.TsacMonitoredValues.Bms1Error), &MonitoredValues.TsacMonitoredValues.Bms1Error);

		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.PedalsMonitoredValues.AcceleratorSensor1Voltage), &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor1Voltage);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.PedalsMonitoredValues.AcceleratorSensor2Voltage), &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor2Voltage);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.PedalsMonitoredValues.AcceleratorSensor1TravelPercentage), &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor1TravelPercentage);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.PedalsMonitoredValues.AcceleratorSensor2TravelPercentage), &MonitoredValues.PedalsMonitoredValues.AcceleratorSensor2TravelPercentage);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.PedalsMonitoredValues.BrakeSensor1Voltage), &MonitoredValues.PedalsMonitoredValues.BrakeSensor1Voltage);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.PedalsMonitoredValues.BrakeSensor2Voltage), &MonitoredValues.PedalsMonitoredValues.BrakeSensor2Voltage);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.PedalsMonitoredValues.BrakeSensor1TravelPercentage), &MonitoredValues.PedalsMonitoredValues.BrakeSensor1TravelPercentage);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.PedalsMonitoredValues.BrakeSensor2TravelPercentage), &MonitoredValues.PedalsMonitoredValues.BrakeSensor2TravelPercentage);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.PedalsMonitoredValues.PressureSensorVoltage), &MonitoredValues.PedalsMonitoredValues.PressureSensorVoltage);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.PedalsMonitoredValues.PressureSensorBars), &MonitoredValues.PedalsMonitoredValues.PressureSensorBars);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToGnd), &MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToGnd);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToVcc), &MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToVcc);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_OutOfRangeOutput), &MonitoredValues.PedalsMonitoredValues.Accel_Sensor1_OutOfRangeOutput);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToGnd), &MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToGnd);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToVcc), &MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToVcc);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_OutOfRangeOutput), &MonitoredValues.PedalsMonitoredValues.Accel_Sensor2_OutOfRangeOutput);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Accel_Implausibility), &MonitoredValues.PedalsMonitoredValues.Accel_Implausibility);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToGnd), &MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToGnd);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToVcc), &MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToVcc);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_OutOfRangeOutput), &MonitoredValues.PedalsMonitoredValues.Brake_Sensor1_OutOfRangeOutput);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToGnd), &MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToGnd);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToVcc), &MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToVcc);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_OutOfRangeOutput), &MonitoredValues.PedalsMonitoredValues.Brake_Sensor2_OutOfRangeOutput);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.PedalsMonitoredValues.Brake_Implausibility), &MonitoredValues.PedalsMonitoredValues.Brake_Implausibility);

		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.InvertersMonitoredValues.LeftInverterTemperature), &MonitoredValues.InvertersMonitoredValues.LeftInverterTemperature);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.InvertersMonitoredValues.LeftMotorTemperature), &MonitoredValues.InvertersMonitoredValues.LeftMotorTemperature);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.InvertersMonitoredValues.LeftInverterInputVoltage), &MonitoredValues.InvertersMonitoredValues.LeftInverterInputVoltage);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.InvertersMonitoredValues.LeftInverterCurrent), &MonitoredValues.InvertersMonitoredValues.LeftInverterCurrent);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.InvertersMonitoredValues.LeftMotorRpm), &MonitoredValues.InvertersMonitoredValues.LeftMotorRpm);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.InvertersMonitoredValues.LeftMotorSpeedKmh), &MonitoredValues.InvertersMonitoredValues.LeftMotorSpeedKmh);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.InvertersMonitoredValues.LeftInverterThrottle), &MonitoredValues.InvertersMonitoredValues.LeftInverterThrottle);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.InvertersMonitoredValues.LeftInverterThrottleFeedback), &MonitoredValues.InvertersMonitoredValues.LeftInverterThrottleFeedback);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.InvertersMonitoredValues.LeftInverterThrottleFeedback), &MonitoredValues.InvertersMonitoredValues.RightInverterTemperature);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.InvertersMonitoredValues.RightMotorTemperature), &MonitoredValues.InvertersMonitoredValues.RightMotorTemperature);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.InvertersMonitoredValues.RightInverterInputVoltage), &MonitoredValues.InvertersMonitoredValues.RightInverterInputVoltage);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.InvertersMonitoredValues.RightInverterCurrent), &MonitoredValues.InvertersMonitoredValues.RightInverterCurrent);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.InvertersMonitoredValues.RightMotorRpm), &MonitoredValues.InvertersMonitoredValues.RightMotorRpm);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.InvertersMonitoredValues.RightMotorSpeedKmh), &MonitoredValues.InvertersMonitoredValues.RightMotorSpeedKmh);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.InvertersMonitoredValues.RightInverterThrottle), &MonitoredValues.InvertersMonitoredValues.RightInverterThrottle);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.InvertersMonitoredValues.RightInverterThrottleFeedback), &MonitoredValues.InvertersMonitoredValues.RightInverterThrottleFeedback);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.InvertersMonitoredValues.IsCarInReverse), &MonitoredValues.InvertersMonitoredValues.IsCarInReverse);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.InvertersMonitoredValues.IsCarRunning), &MonitoredValues.InvertersMonitoredValues.IsCarRunning);

		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.DashboardMonitoredValues.ActivationButtonPressed), &MonitoredValues.DashboardMonitoredValues.ActivationButtonPressed);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.DashboardMonitoredValues.CarReverseCommandPressed), &MonitoredValues.DashboardMonitoredValues.CarReverseCommandPressed);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.DashboardMonitoredValues.IsDisplayWorking), &MonitoredValues.DashboardMonitoredValues.IsDisplayWorking);
		WriteUartDataAtAddress(ReadCanDataFromAddress(&MonitoredValues.DashboardMonitoredValues.IsSegmentsDriverWorking), &MonitoredValues.DashboardMonitoredValues.IsSegmentsDriverWorking);

		//Send data
		UartMessaging_Update();
	}
}

#ifdef __cplusplus
}
#endif
