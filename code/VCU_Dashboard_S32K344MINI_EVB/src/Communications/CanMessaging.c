
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
/*Takes a uint64_t argument and any xMonitoredValue_t type of argument.*/
#define WriteDataFromRawBufferAtAddress(rawBufferU64, xMonitoredValue_t_Address) \
	(xMonitoredValue_t_Address)->valueCan = ((rawBufferU64) >> (xMonitoredValue_t_Address)->shift) & (~(0xFFFFFFFFFFFFFFFF << (xMonitoredValue_t_Address)->nrOfBits))

/*Takes a uint64_t argument and any xMonitoredValue_t type of argument.*/
#define ReadDataFromAddressAndWriteInRawBuffer(rawBufferU64, xMonitoredValue_t_Address) \
		(rawBufferU64) |= (((xMonitoredValue_t_Address)->valueCan & (~(0xFFFFFFFFFFFFFFFF << (xMonitoredValue_t_Address)->nrOfBits))) << (xMonitoredValue_t_Address)->shift)




/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

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
extern MonitoredValues_t CanMonitoredValues;

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/


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

	Can_43_FLEXCAN_SetControllerMode(Can_43_FLEXCANConf_CanController_CanController_0, CAN_CS_STARTED);
	//Can_43_FLEXCAN_SetControllerMode(Can_43_FLEXCANConf_CanController_CanController_1, CAN_CS_STARTED);
	Can_43_FLEXCAN_EnableControllerInterrupts(0);
	//Can_43_FLEXCAN_EnableControllerInterrupts(1);
}

void CanMessaging_Test(void){
	uint64_t cnt = 0;
	volatile int i;
	while(1){
		WriteDataAtAddress(cnt, &CanMonitoredValues.TsacMonitoredValues.MedianCellTemperature);
		WriteDataAtAddress(cnt, &CanMonitoredValues.TsacMonitoredValues.HighestCellTemperature);
		WriteDataAtAddress(cnt, &CanMonitoredValues.TsacMonitoredValues.LowestCellTemperature);
		WriteDataAtAddress(cnt, &CanMonitoredValues.TsacMonitoredValues.MedianCellVoltage);
		WriteDataAtAddress(cnt, &CanMonitoredValues.TsacMonitoredValues.HighestCellVoltage);
		WriteDataAtAddress(cnt, &CanMonitoredValues.TsacMonitoredValues.LowestCellVoltage);
		WriteDataAtAddress(cnt, &CanMonitoredValues.TsacMonitoredValues.OverallVoltage);
		WriteDataAtAddress(cnt, &CanMonitoredValues.TsacMonitoredValues.OverallCurrent);

		WriteDataAtAddress(cnt, &CanMonitoredValues.TsacMonitoredValues.AmsError);
		WriteDataAtAddress(cnt, &CanMonitoredValues.TsacMonitoredValues.TransceiverError);
		WriteDataAtAddress(cnt, &CanMonitoredValues.TsacMonitoredValues.ShuntError);
		WriteDataAtAddress(cnt, &CanMonitoredValues.TsacMonitoredValues.Bms0Error);
		WriteDataAtAddress(cnt, &CanMonitoredValues.TsacMonitoredValues.Bms1Error);

		WriteDataAtAddress(cnt, &CanMonitoredValues.PedalsMonitoredValues.AcceleratorSensor1Voltage);
		WriteDataAtAddress(cnt, &CanMonitoredValues.PedalsMonitoredValues.AcceleratorSensor2Voltage);
		WriteDataAtAddress(cnt, &CanMonitoredValues.PedalsMonitoredValues.AcceleratorSensor1TravelPercentage);
		WriteDataAtAddress(cnt, &CanMonitoredValues.PedalsMonitoredValues.AcceleratorSensor2TravelPercentage);
		WriteDataAtAddress(cnt, &CanMonitoredValues.PedalsMonitoredValues.BrakeSensor1Voltage);
		WriteDataAtAddress(cnt, &CanMonitoredValues.PedalsMonitoredValues.BrakeSensor2Voltage);
		WriteDataAtAddress(cnt, &CanMonitoredValues.PedalsMonitoredValues.BrakeSensor1TravelPercentage);
		WriteDataAtAddress(cnt, &CanMonitoredValues.PedalsMonitoredValues.BrakeSensor2TravelPercentage);
		WriteDataAtAddress(cnt, &CanMonitoredValues.PedalsMonitoredValues.PressureSensorVoltage);
		WriteDataAtAddress(cnt, &CanMonitoredValues.PedalsMonitoredValues.PressureSensorBars);
		WriteDataAtAddress(cnt, &CanMonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToGnd);
		WriteDataAtAddress(cnt, &CanMonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToVcc);
		WriteDataAtAddress(cnt, &CanMonitoredValues.PedalsMonitoredValues.Accel_Sensor1_OutOfRangeOutput);
		WriteDataAtAddress(cnt, &CanMonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToGnd);
		WriteDataAtAddress(cnt, &CanMonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToVcc);
		WriteDataAtAddress(cnt, &CanMonitoredValues.PedalsMonitoredValues.Accel_Sensor2_OutOfRangeOutput);
		WriteDataAtAddress(cnt, &CanMonitoredValues.PedalsMonitoredValues.Accel_Implausibility);
		WriteDataAtAddress(cnt, &CanMonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToGnd);
		WriteDataAtAddress(cnt, &CanMonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToVcc);
		WriteDataAtAddress(cnt, &CanMonitoredValues.PedalsMonitoredValues.Brake_Sensor1_OutOfRangeOutput);
		WriteDataAtAddress(cnt, &CanMonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToGnd);
		WriteDataAtAddress(cnt, &CanMonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToVcc);
		WriteDataAtAddress(cnt, &CanMonitoredValues.PedalsMonitoredValues.Brake_Sensor2_OutOfRangeOutput);
		WriteDataAtAddress(cnt, &CanMonitoredValues.PedalsMonitoredValues.Brake_Implausibility);

		WriteDataAtAddress(cnt, &CanMonitoredValues.InvertersMonitoredValues.LeftInverterTemperature);
		WriteDataAtAddress(cnt, &CanMonitoredValues.InvertersMonitoredValues.LeftMotorTemperature);
		WriteDataAtAddress(cnt, &CanMonitoredValues.InvertersMonitoredValues.LeftInverterInputVoltage);
		WriteDataAtAddress(cnt, &CanMonitoredValues.InvertersMonitoredValues.LeftInverterCurrent);
		WriteDataAtAddress(cnt, &CanMonitoredValues.InvertersMonitoredValues.LeftMotorRpm);
		WriteDataAtAddress(cnt, &CanMonitoredValues.InvertersMonitoredValues.LeftMotorSpeedKmh);
		WriteDataAtAddress(cnt, &CanMonitoredValues.InvertersMonitoredValues.LeftInverterThrottle);
		WriteDataAtAddress(cnt, &CanMonitoredValues.InvertersMonitoredValues.LeftInverterThrottleFeedback);
		WriteDataAtAddress(cnt, &CanMonitoredValues.InvertersMonitoredValues.RightInverterTemperature);
		WriteDataAtAddress(cnt, &CanMonitoredValues.InvertersMonitoredValues.RightMotorTemperature);
		WriteDataAtAddress(cnt, &CanMonitoredValues.InvertersMonitoredValues.RightInverterInputVoltage);
		WriteDataAtAddress(cnt, &CanMonitoredValues.InvertersMonitoredValues.RightInverterCurrent);
		WriteDataAtAddress(cnt, &CanMonitoredValues.InvertersMonitoredValues.RightMotorRpm);
		WriteDataAtAddress(cnt, &CanMonitoredValues.InvertersMonitoredValues.RightMotorSpeedKmh);
		WriteDataAtAddress(cnt, &CanMonitoredValues.InvertersMonitoredValues.RightInverterThrottle);
		WriteDataAtAddress(cnt, &CanMonitoredValues.InvertersMonitoredValues.RightInverterThrottleFeedback);
		WriteDataAtAddress(cnt, &CanMonitoredValues.InvertersMonitoredValues.IsCarInReverse);
		WriteDataAtAddress(cnt, &CanMonitoredValues.InvertersMonitoredValues.IsCarRunning);

		WriteDataAtAddress(cnt, &CanMonitoredValues.DashboardMonitoredValues.ActivationButtonPressed);
		WriteDataAtAddress(cnt, &CanMonitoredValues.DashboardMonitoredValues.CarReverseCommandPressed);
		WriteDataAtAddress(cnt, &CanMonitoredValues.DashboardMonitoredValues.IsDisplayWorking);
		WriteDataAtAddress(cnt, &CanMonitoredValues.DashboardMonitoredValues.IsSegmentsDriverWorking);

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

	CanMessaging_CreateBuffer(ID_CAN_INVERTOR_STANGA);
	pduInfo.sdu=bufferCan;
	pduInfo.id=ID_CAN_INVERTOR_STANGA | 0x80000000U;
	Can_43_FLEXCAN_Write(CAN_HTH_HANDLE, &pduInfo);

	CanMessaging_CreateBuffer(ID_CAN_INVERTOR_DREAPTA);
	pduInfo.sdu=bufferCan;
	pduInfo.id=ID_CAN_INVERTOR_DREAPTA | 0x80000000U;
	Can_43_FLEXCAN_Write(CAN_HTH_HANDLE, &pduInfo);

	CanMessaging_CreateBuffer(ID_CAN_INVERTOARE);
	pduInfo.sdu=bufferCan;
	pduInfo.id=ID_CAN_INVERTOARE | 0x80000000U;
	Can_43_FLEXCAN_Write(CAN_HTH_HANDLE, &pduInfo);

	CanMessaging_CreateBuffer(ID_CAN_BORD);
	pduInfo.sdu=bufferCan;
	pduInfo.id=ID_CAN_BORD | 0x80000000U;
	Can_43_FLEXCAN_Write(CAN_HTH_HANDLE, &pduInfo);

	CanMessaging_CreateBuffer(ID_CAN_ACCELERATIE);
	pduInfo.sdu=bufferCan;
	pduInfo.id=ID_CAN_ACCELERATIE | 0x80000000U;
	Can_43_FLEXCAN_Write(CAN_HTH_HANDLE, &pduInfo);

	CanMessaging_CreateBuffer(ID_CAN_FRANA);
	pduInfo.sdu=bufferCan;
	pduInfo.id=ID_CAN_FRANA | 0x80000000U;
	Can_43_FLEXCAN_Write(CAN_HTH_HANDLE, &pduInfo);

	CanMessaging_CreateBuffer(ID_CAN_BATERIE);
	pduInfo.sdu=bufferCan;
	pduInfo.id=ID_CAN_BATERIE | 0x80000000U;
	Can_43_FLEXCAN_Write(CAN_HTH_HANDLE, &pduInfo);
}

boolean CanMessaging_ReceiveData(Can_HwHandleType handle, Can_IdType id, PduLengthType length, uint8_t* data){
	(void)(handle);	/*This is here to suppress warnings about unused parameter*/
	(void)(length);	/*This is here to suppress warnings about unused parameter*/
	uint64_t data_merged;
	data_merged = (((uint64_t)data[0]) << 56) + (((uint64_t)data[1]) << 48) + (((uint64_t)data[2]) << 40) + (((uint64_t)data[3]) << 32) + (((uint64_t)data[4]) << 24) + (((uint64_t)data[5]) << 16) + (((uint64_t)data[6]) << 8) + (uint64_t)data[7];
	switch((id&MASK)){
		case ID_CAN_FRANA:
			//extragere date
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.PedalsMonitoredValues.BrakeSensor1Voltage);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.PedalsMonitoredValues.BrakeSensor2Voltage);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.PedalsMonitoredValues.BrakeSensor1TravelPercentage);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.PedalsMonitoredValues.BrakeSensor2TravelPercentage);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.PedalsMonitoredValues.PressureSensorBars);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.PedalsMonitoredValues.Brake_Implausibility);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.PedalsMonitoredValues.Brake_Sensor1_OutOfRangeOutput);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToVcc);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToGnd);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.PedalsMonitoredValues.Brake_Sensor2_OutOfRangeOutput);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToVcc);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToGnd);
			break;

		case ID_CAN_ACCELERATIE:
			//extragere date
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.PedalsMonitoredValues.AcceleratorSensor1Voltage);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.PedalsMonitoredValues.AcceleratorSensor2Voltage);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.PedalsMonitoredValues.AcceleratorSensor1TravelPercentage);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.PedalsMonitoredValues.AcceleratorSensor2TravelPercentage);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.PedalsMonitoredValues.PressureSensorVoltage);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.PedalsMonitoredValues.Accel_Implausibility);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.PedalsMonitoredValues.Accel_Sensor1_OutOfRangeOutput);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToVcc);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToGnd);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.PedalsMonitoredValues.Accel_Sensor2_OutOfRangeOutput);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToVcc);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToGnd);
			break;

		case ID_CAN_INVERTOR_STANGA:
			//extragere date
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.InvertersMonitoredValues.LeftMotorTemperature);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.InvertersMonitoredValues.LeftInverterTemperature);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.InvertersMonitoredValues.LeftInverterThrottle);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.InvertersMonitoredValues.LeftMotorSpeedKmh);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.InvertersMonitoredValues.LeftInverterThrottleFeedback);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.InvertersMonitoredValues.LeftInverterInputVoltage);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.InvertersMonitoredValues.LeftMotorRpm);
			break;

		case ID_CAN_INVERTOR_DREAPTA:
			//extragere date
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.InvertersMonitoredValues.RightMotorTemperature);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.InvertersMonitoredValues.RightInverterTemperature);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.InvertersMonitoredValues.RightInverterThrottle);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.InvertersMonitoredValues.RightMotorSpeedKmh);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.InvertersMonitoredValues.RightInverterThrottleFeedback);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.InvertersMonitoredValues.RightInverterInputVoltage);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.InvertersMonitoredValues.RightMotorRpm);
			break;

		case ID_CAN_INVERTOARE:
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.InvertersMonitoredValues.IsCarRunning);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.InvertersMonitoredValues.IsCarInReverse);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.InvertersMonitoredValues.LeftInverterCurrent);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.InvertersMonitoredValues.RightInverterCurrent);
			break;

		case ID_CAN_BATERIE:
			//extragere date
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.TsacMonitoredValues.OverallCurrent);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.TsacMonitoredValues.OverallVoltage);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.TsacMonitoredValues.HighestCellTemperature);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.TsacMonitoredValues.HighestCellVoltage);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.TsacMonitoredValues.LowestCellVoltage);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.TsacMonitoredValues.LowestCellTemperature);
			break;
		case ID_CAN_BATERIE_2:
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.TsacMonitoredValues.MedianCellTemperature);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.TsacMonitoredValues.MedianCellVoltage);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.TsacMonitoredValues.ShuntError);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.TsacMonitoredValues.TransceiverError);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.TsacMonitoredValues.Bms0Error);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.TsacMonitoredValues.Bms1Error);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.TsacMonitoredValues.ThermistorsError);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.TsacMonitoredValues.AmsError);
			break;
		case ID_CAN_BORD:
			//extragere date
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.DashboardMonitoredValues.ActivationButtonPressed);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.DashboardMonitoredValues.CarReverseCommandPressed);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.DashboardMonitoredValues.IsDisplayWorking);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.DashboardMonitoredValues.IsSegmentsDriverWorking);
			break;
		case ID_CAN_COMUNICATII:
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.CommunicationsMonitoredValues.IsInvertersVCUSimulated);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.CommunicationsMonitoredValues.IsTsacVCUSimulated);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.CommunicationsMonitoredValues.IsDashboardVCUSimulated);
			WriteDataFromRawBufferAtAddress(data_merged, &CanMonitoredValues.CommunicationsMonitoredValues.IsPedalsVCUSimulated);
			break;
		case ID_CAN_BATERIE_CHARGER: /* This is only written to CAN, never read*/
			break;
		default:
			return FALSE;
	}
	return TRUE;
}

void CanMessaging_CreateBuffer(idCan_t type){
	uint64_t buffer_merged = 0;
	switch(type){
		case ID_CAN_INVERTOR_STANGA:
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.InvertersMonitoredValues.LeftMotorTemperature);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.InvertersMonitoredValues.LeftInverterTemperature);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.InvertersMonitoredValues.LeftInverterThrottle);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.InvertersMonitoredValues.LeftMotorSpeedKmh);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.InvertersMonitoredValues.LeftInverterThrottleFeedback);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.InvertersMonitoredValues.LeftInverterInputVoltage);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.InvertersMonitoredValues.LeftMotorRpm);
			break;
		case ID_CAN_INVERTOR_DREAPTA:
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.InvertersMonitoredValues.RightMotorTemperature);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.InvertersMonitoredValues.RightInverterTemperature);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.InvertersMonitoredValues.RightInverterThrottle);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.InvertersMonitoredValues.RightMotorSpeedKmh);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.InvertersMonitoredValues.RightInverterThrottleFeedback);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.InvertersMonitoredValues.RightInverterInputVoltage);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.InvertersMonitoredValues.RightMotorRpm);
			break;
		case ID_CAN_INVERTOARE:
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.InvertersMonitoredValues.IsCarRunning);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.InvertersMonitoredValues.IsCarInReverse);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.InvertersMonitoredValues.LeftInverterCurrent);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.InvertersMonitoredValues.RightInverterCurrent);
			break;
		case ID_CAN_BORD:
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.DashboardMonitoredValues.ActivationButtonPressed);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.DashboardMonitoredValues.CarReverseCommandPressed);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.DashboardMonitoredValues.IsDisplayWorking);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.DashboardMonitoredValues.IsSegmentsDriverWorking);
			break;
		case ID_CAN_ACCELERATIE:
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.PedalsMonitoredValues.AcceleratorSensor1Voltage);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.PedalsMonitoredValues.AcceleratorSensor2Voltage);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.PedalsMonitoredValues.AcceleratorSensor1TravelPercentage);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.PedalsMonitoredValues.AcceleratorSensor2TravelPercentage);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.PedalsMonitoredValues.PressureSensorVoltage);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.PedalsMonitoredValues.Accel_Implausibility);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.PedalsMonitoredValues.Accel_Sensor1_OutOfRangeOutput);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToVcc);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToGnd);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.PedalsMonitoredValues.Accel_Sensor2_OutOfRangeOutput);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToVcc);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToGnd);
			break;
		case ID_CAN_FRANA:
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.PedalsMonitoredValues.BrakeSensor1Voltage);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.PedalsMonitoredValues.BrakeSensor2Voltage);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.PedalsMonitoredValues.BrakeSensor1TravelPercentage);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.PedalsMonitoredValues.BrakeSensor2TravelPercentage);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.PedalsMonitoredValues.PressureSensorBars);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.PedalsMonitoredValues.Brake_Implausibility);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.PedalsMonitoredValues.Brake_Sensor1_OutOfRangeOutput);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToVcc);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToGnd);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.PedalsMonitoredValues.Brake_Sensor2_OutOfRangeOutput);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToVcc);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToGnd);
			break;
		case ID_CAN_BATERIE:
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.TsacMonitoredValues.OverallCurrent);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.TsacMonitoredValues.OverallVoltage);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.TsacMonitoredValues.HighestCellTemperature);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.TsacMonitoredValues.HighestCellVoltage);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.TsacMonitoredValues.LowestCellVoltage);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.TsacMonitoredValues.LowestCellTemperature);
			break;
		case ID_CAN_BATERIE_2:
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.TsacMonitoredValues.MedianCellTemperature);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.TsacMonitoredValues.MedianCellVoltage);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.TsacMonitoredValues.ShuntError);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.TsacMonitoredValues.TransceiverError);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.TsacMonitoredValues.Bms0Error);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.TsacMonitoredValues.Bms1Error);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.TsacMonitoredValues.ThermistorsError);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.TsacMonitoredValues.AmsError);
			break;
		case ID_CAN_BATERIE_CHARGER:
			break;
		case ID_CAN_COMUNICATII:
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.CommunicationsMonitoredValues.IsDashboardVCUSimulated);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.CommunicationsMonitoredValues.IsInvertersVCUSimulated);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.CommunicationsMonitoredValues.IsPedalsVCUSimulated);
			ReadDataFromAddressAndWriteInRawBuffer(buffer_merged, &CanMonitoredValues.CommunicationsMonitoredValues.IsTsacVCUSimulated);
			break;
	}
	bufferCan[0] = (uint8_t)(buffer_merged << 56U);
	bufferCan[1] = (uint8_t)(buffer_merged << 48U);
	bufferCan[2] = (uint8_t)(buffer_merged << 40U);
	bufferCan[3] = (uint8_t)(buffer_merged << 32U);
	bufferCan[4] = (uint8_t)(buffer_merged << 24U);
	bufferCan[5] = (uint8_t)(buffer_merged << 16U);
	bufferCan[6] = (uint8_t)(buffer_merged << 8U);
	bufferCan[7] = (uint8_t)buffer_merged;
}

void CanMessaging_AppTest(void){
	while(1){
		//Brake
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_1_VOLT, ReadDataFromAddress(&CanMonitoredValues.PedalsMonitoredValues.BrakeSensor1Voltage));
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_2_VOLT, ReadDataFromAddress(&CanMonitoredValues.PedalsMonitoredValues.BrakeSensor2Voltage));
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_1_TRAVEL_PERCENT, ReadDataFromAddress(&CanMonitoredValues.PedalsMonitoredValues.BrakeSensor1TravelPercentage));
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_2_TRAVEL_PERCENT, ReadDataFromAddress(&CanMonitoredValues.PedalsMonitoredValues.BrakeSensor2TravelPercentage));
		UartMessaging_SetValue(UART_PEDALS_PRESSURE_SENS_BARS, ReadDataFromAddress(&CanMonitoredValues.PedalsMonitoredValues.PressureSensorBars));
		UartMessaging_SetValue(UART_PEDALS_BRAKE_IMPLAUSIBILITY, ReadDataFromAddress(&CanMonitoredValues.PedalsMonitoredValues.Brake_Implausibility));
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_1_OUT_OF_RANGE, ReadDataFromAddress(&CanMonitoredValues.PedalsMonitoredValues.Brake_Sensor1_OutOfRangeOutput));
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_1_SHORT_TO_VCC, ReadDataFromAddress(&CanMonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToVcc));
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_1_SHORT_TO_GND, ReadDataFromAddress(&CanMonitoredValues.PedalsMonitoredValues.Brake_Sensor1_ShortToGnd));
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_2_OUT_OF_RANGE, ReadDataFromAddress(&CanMonitoredValues.PedalsMonitoredValues.Brake_Sensor2_OutOfRangeOutput));
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_2_SHORT_TO_VCC, ReadDataFromAddress(&CanMonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToVcc));
		UartMessaging_SetValue(UART_PEDALS_BRAKE_SENS_2_SHORT_TO_GND, ReadDataFromAddress(&CanMonitoredValues.PedalsMonitoredValues.Brake_Sensor2_ShortToGnd));

		//Acclelerator
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_1_VOLTAGE, ReadDataFromAddress(&CanMonitoredValues.PedalsMonitoredValues.AcceleratorSensor1Voltage));
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_2_VOLTAGE, ReadDataFromAddress(&CanMonitoredValues.PedalsMonitoredValues.AcceleratorSensor2Voltage));
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_1_TRAVEL_PERCENT, ReadDataFromAddress(&CanMonitoredValues.PedalsMonitoredValues.AcceleratorSensor1TravelPercentage));
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_2_TRAVEL_PERCENT, ReadDataFromAddress(&CanMonitoredValues.PedalsMonitoredValues.AcceleratorSensor2TravelPercentage));
		UartMessaging_SetValue(UART_PEDALS_PRESSURE_SENS_VOLT, ReadDataFromAddress(&CanMonitoredValues.PedalsMonitoredValues.PressureSensorVoltage));
		UartMessaging_SetValue(UART_PEDALS_ACCEL_IMPLAUSIBILITY, ReadDataFromAddress(&CanMonitoredValues.PedalsMonitoredValues.Accel_Implausibility));
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_1_OUT_OF_RANGE, ReadDataFromAddress(&CanMonitoredValues.PedalsMonitoredValues.Accel_Sensor1_OutOfRangeOutput));
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_1_SHORT_TO_VCC, ReadDataFromAddress(&CanMonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToVcc));
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_1_SHORT_TO_GND, ReadDataFromAddress(&CanMonitoredValues.PedalsMonitoredValues.Accel_Sensor1_ShortToGnd));
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_2_OUT_OF_RANGE, ReadDataFromAddress(&CanMonitoredValues.PedalsMonitoredValues.Accel_Sensor2_OutOfRangeOutput));
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_2_SHORT_TO_VCC, ReadDataFromAddress(&CanMonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToVcc));
		UartMessaging_SetValue(UART_PEDALS_ACCEL_SENS_2_SHORT_TO_GND, ReadDataFromAddress(&CanMonitoredValues.PedalsMonitoredValues.Accel_Sensor2_ShortToGnd));

		//Left Inverters
		UartMessaging_SetValue(UART_INVERTERS_LEFT_MOTOR_TEMP, ReadDataFromAddress(&CanMonitoredValues.InvertersMonitoredValues.LeftMotorTemperature));
		UartMessaging_SetValue(UART_INVERTERS_LEFT_INVERT_TEMP, ReadDataFromAddress(&CanMonitoredValues.InvertersMonitoredValues.LeftInverterTemperature));
		UartMessaging_SetValue(UART_INVERTERS_LEFT_INVERTER_THROTTLE, ReadDataFromAddress(&CanMonitoredValues.InvertersMonitoredValues.LeftInverterThrottle));
		UartMessaging_SetValue(UART_INVERTERS_LEFT_MOTOR_KMH, ReadDataFromAddress(&CanMonitoredValues.InvertersMonitoredValues.LeftMotorSpeedKmh));
		UartMessaging_SetValue(UART_INVERTERS_LEFT_INVERTER_THROTTLE_FEEDBACK, ReadDataFromAddress(&CanMonitoredValues.InvertersMonitoredValues.LeftInverterThrottleFeedback));
		UartMessaging_SetValue(UART_INVERTERS_LEFT_INVERTER_INPUT_VOLT, ReadDataFromAddress(&CanMonitoredValues.InvertersMonitoredValues.LeftInverterInputVoltage));
		UartMessaging_SetValue(UART_INVERTERS_LEFT_MOTOR_RPM, ReadDataFromAddress(&CanMonitoredValues.InvertersMonitoredValues.LeftMotorRpm));

		//Right Inverters
		UartMessaging_SetValue(UART_INVERTERS_RIGHT_MOTOR_TEMP, ReadDataFromAddress(&CanMonitoredValues.InvertersMonitoredValues.RightMotorTemperature));
		UartMessaging_SetValue(UART_INVERTERS_RIGHT_INVERTER_TEMP, ReadDataFromAddress(&CanMonitoredValues.InvertersMonitoredValues.RightInverterTemperature));
		UartMessaging_SetValue(UART_INVERTERS_RIGHT_INVERTER_THROTTLE, ReadDataFromAddress(&CanMonitoredValues.InvertersMonitoredValues.RightInverterThrottle));
		UartMessaging_SetValue(UART_INVERTERS_RIGHT_MOTOR_KMH, ReadDataFromAddress(&CanMonitoredValues.InvertersMonitoredValues.RightMotorSpeedKmh));
		UartMessaging_SetValue(UART_INVERTERS_RIGHT_INVERTER_THROTTLE_FEEDBACK, ReadDataFromAddress(&CanMonitoredValues.InvertersMonitoredValues.RightInverterThrottleFeedback));
		UartMessaging_SetValue(UART_INVERTERS_RIGHT_INVERTER_INPUT_VOLT, ReadDataFromAddress(&CanMonitoredValues.InvertersMonitoredValues.RightInverterInputVoltage));
		UartMessaging_SetValue(UART_INVERTERS_RIGHT_MOTOR_RPM, ReadDataFromAddress(&CanMonitoredValues.InvertersMonitoredValues.RightMotorRpm));

		//Inverters
		UartMessaging_SetValue(UART_INVERTERS_IS_CAR_RUNNING, ReadDataFromAddress(&CanMonitoredValues.InvertersMonitoredValues.IsCarRunning));
		UartMessaging_SetValue(UART_INVERTERS_IS_CAR_IN_REVERSE, ReadDataFromAddress(&CanMonitoredValues.InvertersMonitoredValues.IsCarInReverse));
		UartMessaging_SetValue(UART_INVERTERS_LEFT_INVERTER_AMPS, ReadDataFromAddress(&CanMonitoredValues.InvertersMonitoredValues.LeftInverterCurrent));
		UartMessaging_SetValue(UART_INVERTERS_RIGHT_INVERTER_AMPS, ReadDataFromAddress(&CanMonitoredValues.InvertersMonitoredValues.RightInverterCurrent));

		//TSAC
		UartMessaging_SetValue(UART_TSAC_OVERALL_AMPS, ReadDataFromAddress(&CanMonitoredValues.TsacMonitoredValues.OverallCurrent));
		UartMessaging_SetValue(UART_TSAC_OVERALL_VOLT, ReadDataFromAddress(&CanMonitoredValues.TsacMonitoredValues.OverallVoltage));
		UartMessaging_SetValue(UART_TSAC_HIGHEST_CELL_TEMP, ReadDataFromAddress(&CanMonitoredValues.TsacMonitoredValues.HighestCellTemperature));
		UartMessaging_SetValue(UART_TSAC_HIGHEST_CELL_VOLT, ReadDataFromAddress(&CanMonitoredValues.TsacMonitoredValues.HighestCellVoltage));

		//Dashboard
		UartMessaging_SetValue(UART_DASHBOARD_ACTIVATION_COMMAND, ReadDataFromAddress(&CanMonitoredValues.DashboardMonitoredValues.ActivationButtonPressed));
		UartMessaging_SetValue(UART_DASHBOARD_CAR_REVERSE_COMMAND, ReadDataFromAddress(&CanMonitoredValues.DashboardMonitoredValues.CarReverseCommandPressed));
		UartMessaging_SetValue(UART_DASHBOARD_IS_DISPLAY_WORKING, ReadDataFromAddress(&CanMonitoredValues.DashboardMonitoredValues.IsDisplayWorking));
		UartMessaging_SetValue(UART_DASHBOARD_IS_SEGMENTS_DRIVER_WORKING, ReadDataFromAddress(&CanMonitoredValues.DashboardMonitoredValues.IsSegmentsDriverWorking));

		//Send data
		//UartMessaging_Update();
	}
}


#ifdef __cplusplus
}
#endif
