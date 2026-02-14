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

typedef enum{
    Brake,
    Accel
}Pedal_t;

typedef enum{
    Sensor1,
    Sensor2
}Sensor_t;

typedef enum{
    Raw_Voltage,
    Percentage
}PedalValue_t;

typedef enum{
    Raw_Voltage,
    Bars
}BrakePressure_t;

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
}PedalsErrors_t;

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
void Pedals_GetErrors(void);
uint32_t Pedals_GetData(Pedal_t PedalSelect, Sensor_t SensorSelect, PedalValue_t DesiredValueType);
uint32_t Pedals_GetPressure(BrakePressure_t ValueType);

#ifdef __cplusplus
}
#endif

#endif

/** @} */
