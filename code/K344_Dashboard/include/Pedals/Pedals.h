/*
*   (c) Copyright 2020 NXP
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be used strictly
*   in accordance with the applicable license terms.  By expressly accepting
*   such terms or by downloading, installing, activating and/or otherwise using
*   the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms.  If you do not agree to
*   be bound by the applicable license terms, then you may not retain,
*   install, activate or otherwise use the software.
*
*   This file contains sample code only. It is not part of the production code deliverables.
*/

#ifndef PEDALS_H
#define PEDALS_H

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Mcu.h"
#include "stdint.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

typedef struct{
	/*Status and Errors*/
	bool Accel_Sensor1_ShortToGnd;                      /* 1 bit, 0 means safe, 1 means errors */
    bool Accel_Sensor1_ShortToVcc;                      /* 1 bit, 0 means safe, 1 means errors */
    bool Accel_Sensor1_OutOfRangeOutput;                /* 1 bit, 0 means safe, 1 means errors */
    bool Accel_Sensor2_ShortToGnd;                      /* 1 bit, 0 means safe, 1 means errors */
    bool Accel_Sensor2_ShortToVcc;                      /* 1 bit, 0 means safe, 1 means errors */
    bool Accel_Sensor2_OutOfRangeOutput;                /* 1 bit, 0 means safe, 1 means errors */
    bool Accel_Implausibility;                          /* 1 bit, 0 means safe, 1 means errors */
    bool Brake_Sensor1_ShortToGnd;                      /* 1 bit, 0 means safe, 1 means errors */
    bool Brake_Sensor1_ShortToVcc;                      /* 1 bit, 0 means safe, 1 means errors */
    bool Brake_Sensor1_OutOfRangeOutput;                /* 1 bit, 0 means safe, 1 means errors */
    bool Brake_Sensor2_ShortToGnd;                      /* 1 bit, 0 means safe, 1 means errors */
    bool Brake_Sensor2_ShortToVcc;                      /* 1 bit, 0 means safe, 1 means errors */
    bool Brake_Sensor2_OutOfRangeOutput;                /* 1 bit, 0 means safe, 1 means errors */
    bool Brake_Implausibility;                          /* 1 bit, 0 means safe, 1 means errors */
}Error_Status;

typedef struct{
    uint16_t PressureSensorVoltage;                     /* 9 bits, 0-500, 0 to 5.00 Volts, 0.1 Volts per bit */
    uint8_t PressureSensorBars;                         /* 8 bits, 0-255, 0 to 255 Bars, 1 Bar per bit */
}Pressure;

typedef struct{
    uint16_t AcceleratorSensor1Voltage;                 /* 9 bits, 0-500, 0 to 5.00 Volts, 0.1 Volts per bit */
    uint16_t AcceleratorSensor2Voltage;                 /* 9 bits, 0-500, 0 to 5.00 Volts, 0.1 Volts per bit */
    uint8_t AcceleratorSensor1TravelPercentage;         /* 7 bits, 0-100, 0 to 100 Percent, 1 Percent per bit */
    uint8_t AcceleratorSensor2TravelPercentage;         /* 7 bits, 0-100, 0 to 100 Percent, 1 Percent per bit */
}Accelerator_Status;

typedef struct{
    uint16_t BrakeSensor1Voltage;                       /* 9 bits, 0-500, 0 to 5.00 Volts, 0.1 Volts per bit */
    uint16_t BrakeSensor2Voltage;                       /* 9 bits, 0-500, 0 to 5.00 Volts, 0.1 Volts per bit */
    uint8_t BrakeSensor1TravelPercentage;               /* 7 bits, 0-100, 0 to 100 Percent, 1 Percent per bit */
    uint8_t BrakeSensor2TravelPercentage;               /* 7 bits, 0-100, 0 to 100 Percent, 1 Percent per bit */
}Brake_Status;

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

void Pedals_Init(void);
void Pedals_Test(void);
void Get_Pedals_Status(Get_Error_Status Pedals_Status);																				//TO PROCESS: Boolean values for the Pedals Status
void Get_Brake_Data(uint8_t Select_Sensor, Get_Brake_Status Voltage, Get_Brake_Status Travel_Percentage);							//RECEIVE: 9-bit ADC for Voltage, 7-bit ADC for Travel Percentage
void Get_Accelerator_Data(uint8_t Select_Sensor, Get_Accelerator_Status Voltage, Get_Accelerator_Status Travel_Percentage);			//RECEIVE: 9-bit ADC for Voltage, 7-bit ADC for Travel Percentage
void Get_Pressure_Data(Pressure Voltage, Pressure Travel_Percentage);

#ifdef __cplusplus
}
#endif

#endif

/** @} */
