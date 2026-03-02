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
#include "CDD_I2c.h"


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
// -- SPEED_KMH pentru digiti 0-2
// -- BATTERY_PERCENTAGE pentru digiti 3-5
// -- TEMPERATURE pentru digiti 6-7
static uint8_t displayBuffer[8] = {0};

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

void Segments_Init(void){
	// -- Iesire din modul Shutdown si trecere in Normal Mode Operation
	AS1115_Write(SHUTDOWN, 0x01);

	// -- Activare mod decodificare "Code B" pentru toti digitii (permite afisarea cifrelor 0-9)
	AS1115_Write(DECODE_MODE, 0xFF);

	// -- Scan limit: activare digitii 0 - 7
	AS1115_Write(SCAN_LIMIT, 0x07);

	// -- Seteaza intensitatea luminii globala a segmentelor
	AS1115_Write(GLOBAL_INTENSITY, 0x0F);

	//Vlad (ma intreb daca ne mai ajuta)
	// -- Seteaza ca toate Segmentele de pe display sa fie stinse pe modul decode
	for(uint8_t i = 0; i < 8; i++){
		AS1115_Write((AS1115Registers_t)(DIGIT0 + i), 0x0F);
	}
}

void Segments_Test(void){
	// -- Activam modul test hardware (aprinde toate segmentele)
	AS1115_Write(DISPLAY_TEST_MODE, 0x01);

    // -- Delay pentru a observa testul hardware
    for(volatile uint32_t i = 0; i < 500000; i++);

    // -- Dezactivam modul test hardware pentru a prelua controlul
    AS1115_Write(DISPLAY_TEST_MODE, 0x00);

    // -- Scriem cifra 8 pe fiecare digit
    for (uint8_t i = 0; i < 8; i++) {
        AS1115_Write((AS1115Registers_t)(DIGIT0 + i), 0x08);
    }
}

void Segments_Set(SegmentsMonitoredValue_t SelectedMonitor, int16_t Value){
	// -- SPEED_KMH pentru digiti 0-2
	// -- BATTERY_PERCENTAGE pentru digiti 3-5
    // -- TEMPERATURE pentru digiti 6-7

	switch(SelectedMonitor) {
		case SPEED_KMH:
			displayBuffer[0] = (uint8_t)(Value % 10);
	        displayBuffer[1] = (uint8_t)((Value / 10) % 10);
	        displayBuffer[2] = (uint8_t)((Value / 100) % 10);
	        break;
		case BATTERY_PERCENTAGE:
	        displayBuffer[3] = (uint8_t)(Value % 10);
	        displayBuffer[4] = (uint8_t)((Value / 10) % 10);
	        displayBuffer[5] = (uint8_t)((Value / 100) % 10);
	        break;
	    case TEMPERATURE:
	    	displayBuffer[6] = (uint8_t)(Value % 10);
	        displayBuffer[7] = (uint8_t)((Value / 10) % 10);
	        break;
	    default:
	    	break;
	    }
}

void Segments_Update(void){
    // -- Actualizeaza digitii din bufferul local
	for(uint8_t i = 0; i < 8; i++){
		AS1115_Write((AS1115Registers_t)(DIGIT0 + i), displayBuffer[i]);
	}
}

#ifdef __cplusplus
}
#endif

/** @} */

