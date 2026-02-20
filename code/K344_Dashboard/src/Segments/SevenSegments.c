#ifdef __cplusplus
extern "C" {
#endif


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "stdint.h"
#include "SevenSegments.h"
#include "AS1115.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/
typedef struct {
	int16_t SPEED_KMH;
	int16_t BATTERY_PERCENTAGE;
	int16_t TEMPERATURE;
} SegmentsValues_t;

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/
//instantierea structurii pentru memorarea valorilor
static SegmentsValues_t SegmentsValues = {0, 0, 0};

//mapare pentru fiecare grup: gr 0 = temperatura (dig0-dig1), gr 1 = speed (dig2-dig4), gr 2 = battery (dig5-dig7)
static const uint8_t GroupTemp[] = {DIGIT0, DIGIT1}; 				// 2 segmente
static const uint8_t GroupSpeed[] = {DIGIT2, DIGIT3, DIGIT4}; 		// 3 segmente
static const uint8_t GroupBattery[] = {DIGIT5, DIGIT6, DIGIT7}; 	// 3 segmente

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
//functie auxiliara pentru scrierea unui numar pe un grup de digituri
static void DisplayWriteNumber(const uint8_t* GroupDigits, uint8_t size, int16_t value) {
	for(uint8_t i = 0; i < size; i++){
		//daca valoarea devine 0 stingem restul, apelam 0x0F
		if(value == 0 && i > 0){
			AS1115_Write((AS1115Registers_t)GroupDigits[i], 0x0F); //scriem BLANK
		} else {
			AS1115_Write((AS1115Registers_t)GroupDigits[i], (uint8_t)(value%10));
			value /= 10;
		}
	}
}


/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

void Segments_Init(void){
    /*initializare drive*/
	AS1115_Write(SHUTDOWN, 0x01);			//iesire din shutdown
	AS1115_Write(SCAN_LIMIT, 0x07);			//activeaza digitii 0-7
	AS1115_Write(DECODE_MODE, 0xFF);		//decodificare BCD pe digitii 0-7
	AS1115_Write(GLOBAL_INTENSITY, 0x08);	//intensitatea setata
}

void Segments_Test(void){
    //aprinde toate segmentele pentru testare
	AS1115_Write(DISPLAY_TEST_MODE, 0x01);
}

void Segments_Set(SegmentsMonitoredValue_t SelectedMonitor, int16_t Value){
    /*se seteaza in functie de valoarea monitorizata selectata*/
	switch(SelectedMonitor){
		case SPEED_KMH: 			SegmentsValues.SPEED_KMH = Value;
									break;
		case BATTERY_PERCENTAGE: 	SegmentsValues.BATTERY_PERCENTAGE = Value;
									break;
		case TEMPERATURE: 			SegmentsValues.TEMPERATURE = Value;
						  	  	  	break;
		default:					break;

	}
}

void Segments_Update(void){
    //afisare temperatura pe grupul de 2 segmente
	DisplayWriteNumber(GroupTemp, 2, SegmentsValues.TEMPERATURE);
	//afisare viteza pe grupul de 3 segmente
	DisplayWriteNumber(GroupSpeed, 3 SegmentsValues.SPEED_KMH);
	//afisare baterie pe grupul de 3 segmente
	DisplayWriteNumber(GroupBattery, 3, SegmentsValues.BATTERY_PERCENTAGE);
}

#ifdef __cplusplus
}
#endif

/** @} */

