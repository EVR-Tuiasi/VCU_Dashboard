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

//
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
	AS1115_Write(GLOBAL_INTENSITY, 0x0F);

	// -- Schimba Feature Register pentru modul de decodificare al 7 Segment Display
	AS1115_Write(FEATURE, 0x00);

	// -- Seteaza ca toate Segmentele de pe display sa fie stinse
	for(uint8_t i = 0; i < 4; i++){//aici era 8
		AS1115_Write((AS1115Registers_t)(DIGIT0 + i), 0x0F);
	}

	// -- Seteaza cati pini folosim de la dig0 pana la dig7 [ex: 0x00 - dig0 | 0x03 - dig0 -> dig3]
	AS1115_Write(SCAN_LIMIT, 0x03);//aici era 7

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

	//variabila de test pentru simularea vitezei
	static uint16_t test_speed = 0;
	//variabila de test pentru simularea bateriei
	static uint16_t test_battery = 1100;
	//variabila de test pentru simularea temperaturii
	static uint16_t test_temperature = 0;
	//counter pentru controlul refresh
	static uint32_t loop_counter = 0;
	//pas de scadere al bateriei
	static uint16_t step = 10;

	while(1){
		// -- Actualizam valorile de test
		test_speed = (test_speed + 1) % 10000; //viteza urca pana la 999 km/h
		test_temperature = (loop_counter % 1000); //temperatura variaza intre 20-60 grade

		// -- La fiecare 10 cicluri, consumam o unitate din baterie
		if(loop_counter % 10 == 0){
			if(test_battery > 1000){
				step = 10;
			} else {
				step = 1;
			}
			if(test_battery >= step){
				test_battery -= step;
			} else {
				test_battery = 10000;
			}
		}

		// -- Mapam pe grupurile de digituri valorile de test
		//Segments_Set(SPEED_KMH, test_speed);
		Segments_Set(BATTERY_PERCENTAGE, test_battery);
		//Segments_Set(TEMPERATURE, test_temperature);


		// -- Trimitem tot bufferul catre driverul AS1115 prin I2C
		Segments_Update();

		// -- Controlul vitezei de refresh
		for(volatile uint32_t delay = 0; delay < 50000UL; delay++);
	    loop_counter++;
	}
}

void Segments_Set(SegmentsMonitoredValue_t SelectedMonitor, int16_t Value){
	// -- SPEED_KMH pentru digiti 0-2
	// -- BATTERY_PERCENTAGE pentru digiti 3-5
	// -- TEMPERATURE pentru digiti 6-7

	switch(SelectedMonitor) {
		case SPEED_KMH:
			//limite de 0-999 kmh
			if(Value < 0) Value = 0;
			if(Value > 9999) Value = 9999;

			//valoarea va iesi de forma XYZ
			displayBuffer[0] = (uint8_t)((Value / 10) % 10);
			displayBuffer[1] = (uint8_t)((Value / 100) % 10);
			displayBuffer[2] = (uint8_t)((Value / 1000) % 10);

			//stingem secventa de digituri din fata egale cu 0
			if(displayBuffer[2] == 0){
				displayBuffer[2] |= 0x0F;
				if(displayBuffer[1] == 0){
					displayBuffer[1] |= 0x0F;
				}
			}
			break;
		case BATTERY_PERCENTAGE:
		    if(Value < 0) Value = 0;
		    if(Value > 10000) Value = 10000;

		    if (Value == 10000) {
		        //baterie plina 100
		        displayBuffer[3] = 0;
		        displayBuffer[4] = 0;
		        displayBuffer[5] = 1;
		    } else if (Value > 1000) {
		        //valori de forma XY.Z
		    	uint16_t temp = Value / 10;
	            displayBuffer[3] = (uint8_t)(temp % 10);
	            displayBuffer[4] = ((uint8_t)((temp / 10) % 10)) | 0x80;
	            displayBuffer[5] = (uint8_t)(temp / 100);
		    } else {
		    	//valori de forma XY.Z
		  	    displayBuffer[3] = (uint8_t)(Value % 10);
		  	    displayBuffer[4] = ((uint8_t)(Value / 10) % 10);
		  	    displayBuffer[5] = ((uint8_t)(Value / 100)) | 0x80;
		    }
		    break;
		case TEMPERATURE:
			//limite de 0-60 grade Celsius
			if(Value < 0) Value = 0;
			if(Value > 999) Value = 60;

			//valoarea va iesi de forma XY
			displayBuffer[6] = (uint8_t)((Value / 10) % 10);
			displayBuffer[7] = (uint8_t)((Value / 100) % 10);

			//stingem primul digit daca e 0
			if(displayBuffer[6] == 0){
				displayBuffer[6] |= 0x0F;
			}
	        break;
	    default:
		    break;
	}
}

void Segments_Update(void){
    // -- Actualizeaza digitii din bufferul local
	for(uint8_t i = 0; i < 4; i++){//aici e 8
		AS1115_Write((AS1115Registers_t)(DIGIT0 + i), displayBuffer[i]);
	}
}

#ifdef __cplusplus
}
#endif

/** @} */
