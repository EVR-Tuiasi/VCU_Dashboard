#ifndef DISPLAY_H
#define DISPLAY_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
 *                                        INCLUDE FILES
 * 1) system and project includes
 * 2) needed interfaces from external units
 * 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Spi.h"
#include "stdint.h"
#include "stdbool.h"
/*==================================================================================================
 *                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/*==================================================================================================
 *                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
 *                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
 *                                      DEFINES AND MACROS
==================================================================================================*/

//NEW VALUES

//Battery Inner Filling
#define BATTERY_FILL_HEIGHT 429
#define BATTERY_FILL_MAX_HEIGHT 67

//Battery Outer Border
#define BORDER_THICKNESS 					5
#define VERTICAL_BATTERY_BORDER				763
#define VERTICAL_BATTERY_BORDER_ORIGIN		455
#define VERTICAL_BATTERY_BORDER_END			65
#define HORIZONTAL_BATTERY_BORDER_HEIGHT	60
#define HORIZONTAL_BATTERY_BORDER_ORIGIN	763
#define HORIZONTAL_BATTER_BORDER_END		800

//Motor Temperature
#define MOTOR_LIMITED_TEMP					60U
#define MOTOR_TEMP_WIDTH					800

//Lower Borders
#define INVERTER_HORIZONTAL_BORDER_START		  0
#define INVERTER_HORIZONTAL_BORDER_END			150
#define LOWER_HORIZONTAL_BORDER_HEIGHT			455
#define MIDDLE_HORIZONTAL_BORDER_START			210
#define MIDDLE_HORIZONTAL_BORDER_END			585
#define	MOTOR_HORIZONTAL_BORDER_START			645
#define	MOTOR_HORIZONTAL_BORDER_END				800

#define LOWER_HORIZONTAL_BORDER				430
#define LOWER_INVERTER_DELIMITER			300
#define LOWER_MOTOR_DELIMITER				500

//Data Underlines

#define TEMPERATURE_DIAGONAL_LINE_START		767
#define TEMPERATURE_DIAGONAL_LINE_END		700
#define TEMPERATURE_DIAGONAL_HEIGHT			340
#define TEMPERATURE_UNDERLINE				480
#define TEMPERATURE_UNDERLINE_HEIGHT		290

#define VOLTAGE_DIAGONAL_LINE_START			767
#define VOLTAGE_DIAGONAL_LINE_END			720
#define VOLTAGE_DIAGONAL_HEIGHT				228
#define VOLTAGE_UNDERLINE					450
#define VOLTAGE_UNDERLINE_HEIGHT			190

//Warning lights Space

#define WARNING_LIGHTS_BORDER_START		200
#define WARNING_LIGHTS_BORDER_END		600
#define WARNING_LIGHTS_BORDER_HEIGHT	81
#define WARNING_VERTICAL_BORDER_START	84
#define WARNING_VERTICAL_BORDER_END		50

//Warning lights boxes

#define TOP_LEFT_INVERTER_CORNER		210
#define BOTTOM_RIGHT_INVERTER_CORNER	299

#define TOP_LEFT_BATTERY_CORNER			304
#define BOTTOM_RIGHT_BATTERY_CORNER		400

#define TOP_LEFT_ACCEL_CORNER			405
#define BOTTOM_RIGHT_ACCEL_CORNER		495

#define TOP_LEFT_BRAKE_CORNER			500
#define BOTTOM_RIGHT_BRAKE_CORNER		590

#define BOX_HEIGHT						55
#define BOX_HEIGHT_OFFSET				21

//Upper Borders
#define UPPER_BORDER_START					100
#define UPPER_BORDER_END					700
#define UPPER_BORDER_HEIGHT					45
#define UPPER_BORDER_DIAGONAL				50
#define UPPER_VERTICAL_LEFT_LINE			255
#define UPPER_VERTICAL_MIDDLE_LINE			400
#define UPPER_VERTICAL_RIGHT_LINE			540

//Speedometer

#define SPEEDOMETER_MAX_VALUE				150
#define SPEEDOMETER_MIN_VALUE				  0

#define LOWER_BARS_HEIGHT					437
#define LOWER_BARS_ENDS						480

//Speedometer's Cursor

#define INNER_RADIUS						130
#define OUTER_RADIUS						195
#define CENTER_X							220
#define CENTER_Y							300
#define PI									3.1415926535

#define HASH1_X 48
#define HASH1_Y 377
#define HASH1_END_X 58
#define HASH1_END_Y 372

#define HASH2_X 29
#define HASH2_Y 305
#define HASH2_END_X 42
#define HASH2_END_Y 305

#define HASH3_X 39
#define HASH3_Y 234
#define HASH3_END_X 50
#define HASH3_END_Y 238

#define HASH4_X 71
#define HASH4_Y 172
#define HASH4_END_X 81
#define HASH4_END_Y 179

#define HASH5_X 131
#define HASH5_Y 121
#define HASH5_END_X 138
#define HASH5_END_Y 132

#define HASH6_X 221
#define HASH6_Y 99
#define HASH6_END_X 221
#define HASH6_END_Y 113

#define HASH7_X 310
#define HASH7_Y 123
#define HASH7_END_X 303
#define HASH7_END_Y 133

#define HASH8_X 367
#define HASH8_Y 171
#define HASH8_END_X 359
#define HASH8_END_Y 178

#define HASH9_X 400
#define HASH9_Y 235
#define HASH9_END_X 390
#define HASH9_END_Y 240

#define HASH10_X 412
#define HASH10_Y 305
#define HASH10_END_X 397
#define HASH10_END_Y 305

#define HASH11_X 391
#define HASH11_Y 378
#define HASH11_END_X 381
#define HASH11_END_Y 372






/*==================================================================================================
 *                                             ENUMS
==================================================================================================*/

/*==================================================================================================
 *                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
typedef struct{
	Spi_ChannelType Spi_Channel;
}FT81;

/*==================================================================================================
 *                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
 *                                    FUNCTION PROTOTYPES
==================================================================================================*/
void Display_Init(void);
void ImageTest(void);
void SoundTest(void);
void Display_Test(uint8_t Address, uint8_t Minutes, uint8_t Seconds, uint32_t Miliseconds);
void Display_Update(uint8_t Acceleration, uint8_t Brake, uint8_t Battery_Percentage, uint16_t Motor_Temperature, uint16_t Inverter_Temperature, uint8_t Speed, uint16_t Cell_Voltage, uint16_t Cell_Temperature, uint16_t Total_Current, uint16_t Total_Voltage, uint8_t witness, uint8_t Minutes, uint8_t Seconds, uint32_t Miliseconds);
void trailingArray(void);
void newDisplayUpdate(uint8_t Acceleration, uint8_t Brake, uint8_t Battery_Percentage, uint16_t Motor_Temperature, uint16_t Inverter_Temperature, uint8_t Speed, uint16_t Cell_Voltage, uint16_t Cell_Temperature, uint16_t Total_Current, uint16_t Total_Voltage, uint8_t witness, uint8_t Minutes, uint8_t Seconds, uint32_t Miliseconds);

#ifdef __cplusplus
}
#endif

#endif
