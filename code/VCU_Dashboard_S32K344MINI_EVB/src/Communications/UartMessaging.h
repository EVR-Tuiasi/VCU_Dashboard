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
	ID_UART_INVERTOR_STANGA = 				0x10,
	ID_UART_INVERTOR_DREAPTA = 				0x11,
	ID_UART_INVERTOARE = 					0x12,

	ID_UART_BORD = 							0x13,

	ID_UART_ACCELERATIE = 					0x30,
	ID_UART_FRANA = 						0x31,

	ID_UART_BATERIE = 						0x14,
	ID_UART_BATERIE_TENSIUNI_CELULE = 		0x15,
	ID_UART_BATERIE_TEMPERATURI_CELULE = 	0x16,
	ID_UART_BATERIE_2 = 					0x17,
	ID_UART_BATERIE_CHARGER = 				0x19,

	ID_UART_COMUNICATII = 					0x18
}idUart_t;

typedef enum{
    /* TSAC */
    UART_TSAC_MEDIAN_CELL_TEMP,
    UART_TSAC_HIGHEST_CELL_TEMP,
    UART_TSAC_LOWEST_CELL_TEMP,
    UART_TSAC_MEDIAN_CELL_VOLT,
    UART_TSAC_HIGHEST_CELL_VOLT,
    UART_TSAC_LOWEST_CELL_VOLT,
    UART_TSAC_OVERALL_VOLT,
    UART_TSAC_OVERALL_AMPS,
	UART_TSAC_IS_AMS_SAFE,
	UART_TSAC_IS_TRANSCEIVER_WORKING,
	UART_TSAC_IS_SHUNT_WORKING,
	UART_TSAC_IS_BMS_0_WORKING,
	UART_TSAC_IS_BMS_1_WORKING,
    /* PEDALS */
	UART_PEDALS_ACCEL_SENS_1_VOLTAGE,
	UART_PEDALS_ACCEL_SENS_2_VOLTAGE,
	UART_PEDALS_ACCEL_SENS_1_TRAVEL_PERCENT,
	UART_PEDALS_ACCEL_SENS_2_TRAVEL_PERCENT,
	UART_PEDALS_BRAKE_SENS_1_VOLT,
	UART_PEDALS_BRAKE_SENS_2_VOLT,
	UART_PEDALS_BRAKE_SENS_1_TRAVEL_PERCENT,
	UART_PEDALS_BRAKE_SENS_2_TRAVEL_PERCENT,
	UART_PEDALS_PRESSURE_SENS_VOLT,
	UART_PEDALS_PRESSURE_SENS_BARS,
	UART_PEDALS_ACCEL_SENS_1_SHORT_TO_GND,
	UART_PEDALS_ACCEL_SENS_1_SHORT_TO_VCC,
	UART_PEDALS_ACCEL_SENS_1_OUT_OF_RANGE,
	UART_PEDALS_ACCEL_SENS_2_SHORT_TO_GND,
	UART_PEDALS_ACCEL_SENS_2_SHORT_TO_VCC,
	UART_PEDALS_ACCEL_SENS_2_OUT_OF_RANGE,
	UART_PEDALS_ACCEL_IMPLAUSIBILITY,
	UART_PEDALS_BRAKE_SENS_1_SHORT_TO_GND,
	UART_PEDALS_BRAKE_SENS_1_SHORT_TO_VCC,
	UART_PEDALS_BRAKE_SENS_1_OUT_OF_RANGE,
	UART_PEDALS_BRAKE_SENS_2_SHORT_TO_GND,
	UART_PEDALS_BRAKE_SENS_2_SHORT_TO_VCC,
	UART_PEDALS_BRAKE_SENS_2_OUT_OF_RANGE,
	UART_PEDALS_BRAKE_IMPLAUSIBILITY,
    /* INVERTERS */
	UART_INVERTERS_LEFT_INVERT_TEMP,
	UART_INVERTERS_LEFT_MOTOR_TEMP,
	UART_INVERTERS_LEFT_INVERTER_INPUT_VOLT,
	UART_INVERTERS_LEFT_INVERTER_AMPS,
	UART_INVERTERS_LEFT_MOTOR_RPM,
	UART_INVERTERS_LEFT_MOTOR_KMH,
	UART_INVERTERS_LEFT_INVERTER_THROTTLE,
	UART_INVERTERS_LEFT_INVERTER_THROTTLE_FEEDBACK,
	UART_INVERTERS_RIGHT_INVERTER_TEMP,
	UART_INVERTERS_RIGHT_MOTOR_TEMP,
	UART_INVERTERS_RIGHT_INVERTER_INPUT_VOLT,
	UART_INVERTERS_RIGHT_INVERTER_AMPS,
	UART_INVERTERS_RIGHT_MOTOR_RPM,
	UART_INVERTERS_RIGHT_MOTOR_KMH,
	UART_INVERTERS_RIGHT_INVERTER_THROTTLE,
	UART_INVERTERS_RIGHT_INVERTER_THROTTLE_FEEDBACK,
	UART_INVERTERS_IS_CAR_IN_REVERSE,
	UART_INVERTERS_IS_CAR_RUNNING,
    /* DASHBOARD */
	UART_DASHBOARD_ACTIVATION_COMMAND,
	UART_DASHBOARD_CAR_REVERSE_COMMAND,
	UART_DASHBOARD_IS_DISPLAY_WORKING,
    UART_DASHBOARD_IS_SEGMENTS_DRIVER_WORKING
}UartMonitoredValue_t;

#define UART_Channel 0x00000000

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
void UartMessaging_SetValue(UartMonitoredValue_t DesiredValueType, uint32_t Value);
uint32_t UartMessaging_ReadValue(UartMonitoredValue_t DesiredValueType);
void UartMessaging_CreateBuffer(idUart_t type);
uint8_t CRC_calculate(uint8_t length);

#ifdef __cplusplus
}
#endif

#endif
