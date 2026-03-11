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
#include "CDD_I2c.h"
#include "SevenSegments.h"
#include "AS1115.h"

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

//variabila pentru setarea luminozitatii
static uint8_t luminozitateGlobala = 0x0F;
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

	// -- Seteaza modul Shutdown cu Reset Feature Register
	AS1115_Write(SHUTDOWN, 0x00);

	// -- Seteaza Luminozitatea Globala la 7 Segment Display-uri
	AS1115_Write(GLOBAL_INTENSITY, luminozitateGlobala);

	// -- Schimba Feature Register pentru modul de decodificare al 7 Segment Display
	AS1115_Write(FEATURE, 0x00);

	// -- Seteaza ca toate Segmentele de pe display sa fie stinse
	for(uint8_t i = 0; i < 8; i++){
		AS1115_Write((AS1115Registers_t)(DIGIT0 + i), 0x0F);
	}

	// -- Seteaza cati pini folosim de la dig0 pana la dig7 [ex: 0x00 - dig0 | 0x03 - dig0 -> dig3]
	AS1115_Write(SCAN_LIMIT, 0x07);

	// -- Seteaza pana la ce pin folosim decodificare pe digits [ex: 0x03 - 00000011 - Decodifica pe dig0 si dig1, ne luam dupa pozitia bitilor de la LSB la MSB]
	AS1115_Write(DECODE_MODE, 0xFF);

	// -- Seteaza Normal Mode fara modificari la Feature Register
	AS1115_Write(SHUTDOWN, 0x81);
}

void Segments_Test(void){
	// -- Activam un test hardware
	AS1115_Write(DISPLAY_TEST_MODE, 0x01);
	for(volatile uint32_t i = 0; i <= 200000UL; i++){}
	AS1115_Write(DISPLAY_TEST_MODE, 0x00);

	//initializari
	uint16_t rpm = 0, tensiune = 0, temperatura = 0, procentaj = 0, viteza = 0;
	volatile uint32_t delay;
	while(1){
		delay = 2000000;
		while(delay--);

		//actualizari
		rpm += 5;
		tensiune++;
		temperatura++;

		//limitari
		rpm %= 6000;
		tensiune %= 150;
		temperatura %= 99;

		//calcul procent baterie
		if (tensiune < 60U){
			procentaj = 0; //capatul de 0%
		} else if (tensiune > 100){
			procentaj = 1000U; //capatul de 100%
		} else {
			procentaj = (uint16_t)(tensiune - 60U) * 25U;
		}

		//calcul viteza
		if (rpm != 0){
			viteza = (uint16_t)((uint32_t)rpm * 84807UL / 312500UL);
		}

		//afisare baterie
		if (procentaj < 1000U) {
			Segments_Set(BATTERY_PERCENTAGE, (int16_t)procentaj, 1);
		} else {
			Segments_Set(BATTERY_PERCENTAGE, (int16_t)(procentaj/10), 0);
		}

		//afisare temperatura
		Segments_Set(TEMPERATURE, (int16_t)temperatura, 0);

		//afisare viteza
		if (viteza < 1000U){
			Segments_Set(SPEED_KMH, (int16_t)viteza, 1);
		} else {
			Segments_Set(SPEED_KMH, (int16_t)(viteza/10), 0);
		}

		//trimitem bufferul cu cei 8 digiti
		Segments_Update();
	}
}

void Segments_Set(SegmentsMonitoredValue_t SelectedMonitor, int16_t Value, uint8_t PrecisionFloatPoint){
	// -- SPEED_KMH pentru digiti 0-2
	// -- BATTERY_PERCENTAGE pentru digiti 3-5
    // -- TEMPERATURE pentru digiti 6-7

	uint8_t startDigit = 0;
	uint8_t numDigits = 0;

	//identificam tipul pe care lucram
	switch(SelectedMonitor){
		case SPEED_KMH:
			startDigit = 0;
			numDigits = 3;
			break;
		case BATTERY_PERCENTAGE:
			startDigit = 3;
			numDigits = 3;
			break;
		case TEMPERATURE:
			startDigit = 6;
			numDigits = 2;
			break;
		default:
			return; //nu stim pe ce lucram, am iesit
	}

	//reglare numar negativ
	bool isNegative = false;
	if (Value < 0){
		isNegative = true;
		Value *= -1;
	}

	//extragere cifre si salvare in buffer
	for (uint8_t i = 0; i < numDigits; i++){
		uint8_t indexCurrent = startDigit + i;

		if (Value == 0 && i > 0 && i > PrecisionFloatPoint) {
			//verificam daca punem semnul minus, daca am terminat numarul completam cu blank
			if (isNegative) {
				displayBuffer[indexCurrent] = 0x0A; //punem semnul minus
				isNegative = false;
			} else {
				displayBuffer[indexCurrent] = 0x0F; //blank
			}
		} else {
			uint8_t digit = (uint8_t)(Value % 10);

			//adaugam virgula
			if (i == PrecisionFloatPoint && PrecisionFloatPoint > 0){
				displayBuffer[indexCurrent] = digit | 0x80; //punem virgula
			} else {
				displayBuffer[indexCurrent] = digit;
			}
			Value /= 10;
		}
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
